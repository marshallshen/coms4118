#include <linux/sched.h> /* find_user, user_struct */
#include <linux/mm.h>
#include <linux/errno.h>

asmlinkage int sys_set_mlimit(uid_t uid, long mem_max){

	struct user_struct *usr;

	printk(KERN_INFO "sys_set_mlimit: args[%d, %lu]", (int) uid, mem_max);

	if(mem_max < 0)
		return (-EINVAL);

	// get struct user_struct corresponding to uid
	if((usr = find_user(uid)) == NULL)
		return (-EINVAL);	

	// set that value of mem_max
	usr->mem_max = mem_max;	

	return 0;
}
