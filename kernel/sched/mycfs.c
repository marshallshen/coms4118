/* mycfs_sched_class implementation */

/* Notes:
-fair scheduling algo
-runqueue = rb tree
-schedule latency = 10ms
-equally weighted processes
-lower than fair_sched_class; higher than idle_sched_classa (core.c line 3177)
-runqueue for each core; don't have to worry about load balancing

*/

#include <linux/sched.h>

unsigned int sysctl_sched_latency = 10000000ULL; // 10ms (in nanoseconds)

// todo: add to sched.h line 856
// see fair.c line 5538 for initialization of fair_sched_class
const struct sched_class mycfs_sched_class;

const struct sched_class mycfs_sched_class = {
	.next = &idle_sched_class

	// TODO: include the rest...
	/*

	.enqueue_task = 
	.dequeue_task =
	.yield_task = 
	.yield_to_task =
	.check_preempt_curr = 
	.pick_next_task = 
	.put_prev_task = 

#ifdef CONFIG_SMP // enables support for multiprocessor machines
	.select_tak_rq =
	.rq_online =
	.rq_offline = 
	.task_waking =
#endif

	.set_curr_task =
	.task_tick =
	.task_fork =
	.prio_changed =
	.switched_from =
	.switched_to =
	.get_rr_interval =
	.task_move_group =

	*/
};

// TODO: methods to implement

