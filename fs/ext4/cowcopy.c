#include <linux/syscalls.h>
#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/dcache.h>
#include <linux/stat.h>
#include <linux/string.h>


asmlinkage int sys_ext4_cowcopy(const char __user *src, const char __user *dest){
	
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

	kern_path(src, LOOKUP_FOLLOW, &s_p);
	s_d = s_p.dentry;
	s_mnt = s_p.mnt;
	if(s_d) {
		s_i = s_d->d_inode;
		s_sb = s_i->i_sb;
		s_type = s_sb->s_type;
		s_fsName = s_type->name;
		printk(KERN_INFO "COWS: fsName: %s\n", s_fsName);
	}
	printk(KERN_INFO "COWS: src: %s\n", src);
	printk(KERN_INFO "COWS: dest: %s\n", dest);
	
	kern_path(dest, LOOKUP_FOLLOW, &d_p);
	d_d = d_p.dentry;
	d_mnt = d_p.mnt;
	if(d_d) {
		d_i = d_d->d_inode;
	}

	//Checking if the file is actually a file and not a directory
	if(S_ISDIR(s_i->i_mode)) {
		printk(KERN_INFO "COWS: directory bitch\n");
		return -EPERM;
	}

	//Checking if the file is in the ext4 file system
	if(!strncmp(s_fsName, "ext4", 4)) {
		printk(KERN_INFO "COWS: not ext4 bitch\n");
		return -EOPNOTSUPP;
	}
	
	
	
	printk(KERN_INFO "sys_ext4_cowcopy: success");
	return 0;
}
