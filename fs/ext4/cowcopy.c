#include <linux/syscalls.h>
#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/dcache.h>
#include <linux/stat.h>
#include <linux/string.h>


asmlinkage int sys_ext4_cowcopy(const char __user *src, const char __user *dest){
	
	//Checking if the path is a directory of not.
	struct path s_p;
	struct dentry *s_d;
	struct vfsmount *s_mnt;
	struct inode *s_i;
	struct super_block *s_sb;
	struct file_system_type *s_type;
	char *s_fsName;
	struct path d_p;
	struct dentry *d_d;
	struct vfsmount *d_mnt;
	struct inode *d_i;

	//Might need to sanitize the src filename and check if its like a relative or absolute path.
	//Another thing to note is that for kern_path, it says it takes a char *name but we're giving it a path so idk if this will work
	kern_path(src, LOOKUP_FOLLOW, &s_p);
	s_d = s_p.dentry;
	s_mnt = s_p.mnt;
	s_i = s_d->d_inode;
	s_sb = s_i->i_sb;
	s_type = s_sb->s_type;
	s_fsName = s_type->name;
	
	kern_path(dest, LOOKUP_FOLLOW, &d_p);
	d_d = d_p.dentry;
	d_mnt = d_p.mnt;
	d_i = d_d->d_inode;

	//Checking if the file is actually a file and not a directory
	if(S_ISDIR(i->i_mode))
		return -EPERM;

	//Checking if the file is in the ext4 file system
	if(!strncmp(fsName, "ext4", 4)) 
		return -EOPNOTSUPP;
	

	
	printk(KERN_INFO "sys_ext4_cowcopy: success");
	return 0;
}
