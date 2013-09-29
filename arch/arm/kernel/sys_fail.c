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
	// INFO: if N > 0, Nth system call will return an error
	// INFO: if N == 0, stop this process if there is already a fault injection in progress
	// INFO: if N < 0, 

	struct thread_info *thread;
	struct task_struct *task;

	// TODO: check that the argument is valid
	// Cases: n<0, n=0 w/ fault injection in progress
	if(N < 0)
		return (-EINVAL);

	// need to initialize the values in the struct

	// update/record bookkeeping information
	thread = current_thread_info();
	task = thread->task;

	//task->fault = 0;
	task->calls_left = N - 1;

	return 0;
}

// checks whether a fault should be injected for the current system
long should_fail(void){
	
	struct thread_info *thread = current_thread_info();
	struct task_struct *task = thread->task;

	if(task->calls_left-- == 0){
		task->fault = 1;
		return 1;
	}

	return 0;
}

// injects fault by returning an error code
long fail_syscall(void){
	// similar to other system call routines
	// pick appropriate error code to return

	return (-ERESTART);
}


