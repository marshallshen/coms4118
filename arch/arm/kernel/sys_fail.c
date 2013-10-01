#include <linux/export.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/sem.h>
#include <linux/msg.h>
#include <linux/shm.h>
#include <linux/stat.h>
#include <linux/syscalls.h>
#include <linux/mman.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/ipc.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/thread_info.h>

// task_struct defined in: msm/include/linux/sched.h (1266)
// fault, calls_left

asmlinkage int sys_fail(int N){

	struct thread_info *thread;
	struct task_struct *task;

	// record bookkeeping information in task_struct
	thread = current_thread_info();
	task = thread->task;

	// cases: n=0 w/ fault injection in progress
	if(N == 0 && task->fault == 1){
		task->fault = 0;
		return 0;
	}else if(N <= 0){ // n<0, n=0 w/o fault injection
		return (-EINVAL);
	}

	// initialize|renew fault injection session
	task->fault = 1;
	task->calls_left = N;

	return 0;
}

// checks whether a fault should be injected for the current system
long should_fail(void){
	
	struct thread_info *thread = current_thread_info();
	struct task_struct *task = thread->task;

	// only fails system call if fault injection session is active
	if(task->fault == 1 && --(task->calls_left) == 0){
		return 1;
	}

	return 0;
}

// injects fault by returning an error code
long fail_syscall(void){
	
	struct thread_info *thread = current_thread_info();
	struct task_struct *task = thread->task;

	task->fault = 0; // ends fault injection session
	return (-ERESTART);
}


