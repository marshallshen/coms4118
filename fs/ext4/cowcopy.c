#include <linux/syscalls.h>
#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/dcache.h>
#include <linux/stat.h>
#include <linux/string.h>
#include <linux/mount.h>
#include <linux/atomic.h>
#include "ext4.h"
#include "ext4_jbd2.h"
#include "xattr.h"

asmlinkage int sys_ext4_cowcopy(const char __user *src, const char __user *dest){
	
	char *ext = "ext4";
	//Checking if the path is a directory of not.

	//For the src
	struct path s_p;
	struct dentry *s_d;
	struct vfsmount *s_mnt;
	struct inode *s_i;
	struct super_block *s_sb;
	struct file_system_type *s_type;
	const char *s_fsName;

	//for the destination
	struct path d_p;
	struct dentry *d_d;
	struct vfsmount *d_mnt;
	struct inode *d_i;

	//for new copy
	struct dentry *c_d;


	int cc_value = 0;
	int cc_xattr_result = -1;
	int cc_xattr_result_d = -1;
	int cc_success;

	//getting things for the src
	kern_path(src, LOOKUP_FOLLOW, &s_p);

	s_d = s_p.dentry;
	s_mnt = s_p.mnt;
	if(s_d) {
		s_i = s_d->d_inode;
		s_sb = s_i->i_sb;
		printk(KERN_INFO "before s_type");
		s_type = s_sb->s_type;
		s_fsName = s_type->name;
		printk(KERN_INFO "COWS: fsName: %s\n", s_fsName);
		printk(KERN_INFO "COWS: fslen: %d\n", strlen(s_fsName));
	} else
		return -EINVAL; //Temporary return statement

	printk(KERN_INFO "COWS: src: %s\n", src);
	printk(KERN_INFO "COWS: dest: %s\n", dest);

	//Getting things for the destination folder
	kern_path(dest, LOOKUP_FOLLOW, &d_p);
	d_d = d_p.dentry;
	d_mnt = d_p.mnt;
	if(d_d) {
		d_i = d_d->d_inode;
	} else
		return -EINVAL; //Temporary return statement
		

	//Checking if the file is actually a file and not a directory
	if(S_ISDIR(s_i->i_mode)) {
		printk(KERN_INFO "COWS: directory bitch\n");
		return -EPERM;
	}

	
	//Checking if the file is in the ext4 file system
	if(strncmp(s_fsName, ext, 4)) {
		printk(KERN_INFO "COWS: not ext4 bitch\n");
		return -EOPNOTSUPP;
	}

	//Checking if theyre in the same mount point
	if(s_mnt->mnt_root != d_mnt->mnt_root) {
		printk(KERN_INFO "COWS: not same device bitch\n");
		return -EXDEV;
	}

	// ======================
	// End checks
	// ======================

	// create dentry, set parent dentry to dest
	printk(KERN_INFO "sys_ext4_cowcopy: qstr[%p] name[%s]", &s_d->d_name, s_d->d_name.name);
	printk(KERN_INFO "sys_ext4_cowcopy: parent[%p] superblock[%p]", d_d, d_d->d_sb);

	if((c_d = d_alloc(d_d, &s_d->d_name)) == NULL)
		return -1;

	printk(KERN_INFO "sys_ext4_cowcopy: i_count[%d]", (int)s_i->i_nlink);
	//atomic_add(1, &s_i->i_nlink);

	printk(KERN_INFO "sys_ext4_cowcopy: d_alloc'd new dentry");
	ext4_dir_inode_operations.link(s_d, d_i, c_d);
	printk(KERN_INFO "sys_ext4_cowcopy: after link i_count[%d]", (int)s_i->i_nlink);
	// change permissions of both to read only - save permissions?
	// update type, so we know that the file is cow or not
	printk(KERN_INFO "sys_ext4_cowcopy: success");
	
	//testing xattr
	cc_success = ext4_xattr_set(s_i, 0, "cowcopy", &cc_value, sizeof(cc_value), 0);
	cc_xattr_result = ext4_xattr_get(s_i, 0, "cowcopy", &cc_value, sizeof(cc_value));
	cc_xattr_result_d = ext4_xattr_set(d_i, 0, "cowcopy", &cc_value, sizeof(cc_value), 0);
	printk(KERN_INFO "xattr_test success: %d cowcopy: %d length: %d\n ", cc_success, cc_value,cc_xattr_result);
	
	return 0;
}
