#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/errno.h>
#include <linux/slab.h>

asmlinkage int sys_set_mlimit(uid_t uid, long mem_max){

	printk(KERN_INFO "set_mlimit");
	return 0;
}
