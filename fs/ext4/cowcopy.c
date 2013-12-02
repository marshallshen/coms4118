#include <linux/syscalls.h>

asmlinkage int sys_ext4_cowcopy(const char __user *src, const char __user *dest){
	
	printk(KERN_INFO "sys_ext4_cowcopy: success");
	return 0;
}
