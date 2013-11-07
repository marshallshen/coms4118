#include <linux/syscalls.h>
#include <linux/sched.h>

asmlinkage int sys_sched_setlimit(pid_t pid, int limit){

	int i;
	for(i = 0; i < 10; i++){
		printk(KERN_INFO "sys_sched_setlimit: pid[%d] limit[%d]", (int) pid, limit);
	}

	return 0;
}
