#include <linux/sched.h> /* find_user, user_struct */
#include <linux/mm.h>
#include <linux/errno.h>
#include <linux/cred.h>

asmlinkage int sys_set_mlimit(uid_t uid, long mem_max){

	struct user_struct *usr;
	struct task_struct *g;
	struct mm_struct *temp_mm;
	int temp_rss_val;

	printk(KERN_INFO "sys_set_mlimit: args[%d, %lu]", (int) uid, mem_max);

	if(mem_max < 0)
		return (-EINVAL);

	// get struct user_struct corresponding to uid
	if((usr = find_user(uid)) == NULL){
		printk(KERN_ERR "sys_set_mlimit: user_struct not found");
		return (-EINVAL);	
	}

	// set that value of mem_max
	usr->mem_max = mem_max;	

	//Look through every process and try to find which processes have the same user id as the one given	
	for_each_process(g) {
		const struct cred *real = g->real_cred;
		//const struct cred *fake = g->cred;

		if(real->uid == uid) {
			printk(KERN_INFO "sys_set_mlimit: found process pid: %d with uid %d\n", (int) g->pid, uid);
			//Now onto the fun stuff like finding the RSS size for each process.
			temp_mm = g->mm;
			temp_rss_val = get_mm_rss(temp_mm);
			printk(KERN_INFO "sys_set_mlimit: pid: %d with RSS: %d\n", (int) g->pid, temp_rss_val);
		}
	}	

	printk(KERN_INFO "sys_set_mlimit: return");

	return 0;
}
