/* mycfs_sched_class implementation */

/* Notes:
-fair scheduling algo
-runqueue = rb tree
-equally weighted processes
-runqueue for each core; don't have to worry about load balancing
*/

#include <linux/sched.h>
#include "sched.h"

// todo: include in header file
static void enqueue_task_mycfs(struct rq *rq, struct task_struct *p, int flags);
static void dequeue_task_mycfs(struct rq *rq, struct task_struct *p, int flags);
static void yield_task_mycfs(struct rq *rq);
static void check_preempt_wakeup(struct rq *rq, struct task_struct *p, int wake_flags);
static struct task_struct *pick_next_task_mycfs(struct rq *rq);
static void put_prev_task_mycfs(struct rq *rq, struct task_struct *prev);
static int select_task_rq_fair(struct task_struct *p, int sd_flag, int wake_flags);
static void set_curr_task_mycfs(struct rq *rq);
static void task_tick_mycfs(struct rq *rq, struct task_struct *curr, int queued);
static void prio_changed_mycfs(struct rq *rq, struct task_struct *p, int oldprio);
static void switched_to_mycfs(struct rq *rq, struct task_struct *p);
static unsigned int get_rr_interval_mycfs(struct rq *rq, struct task_struct *task);

unsigned int sysctl_sched_latency_mycfs = 10000000ULL; // 10ms (in nanoseconds)

// see fair.c line 5538 for initialization of fair_sched_class
const struct sched_class mycfs_sched_class;

const struct sched_class mycfs_sched_class = {
	.next = &idle_sched_class,
	.enqueue_task = enqueue_task_mycfs,
	.dequeue_task = dequeue_task_mycfs,
	.yield_task = yield_task_mycfs,
	.check_preempt_curr = check_preempt_wakeup,
	.pick_next_task = pick_next_task_mycfs,
	.put_prev_task = put_prev_task_mycfs,
	.select_task_rq = select_task_rq_fair, // select different rq based on processor
	.set_curr_task = set_curr_task_mycfs,
	.task_tick = task_tick_mycfs,
	.prio_changed = prio_changed_mycfs,
	.switched_to = switched_to_mycfs,
	.get_rr_interval = get_rr_interval_mycfs

// shit we don't need:
// .yield_to_task =
// .rq_online = N
// .rq_offline =  N
// .task_waking = ?
// .task_fork = yes
// .switched_from = yes

/*
#ifdef CONFIG_FAIR_GROUP_SCHED
	.task_move_group =
#endif
*/

};


/*
	Called when a task enters a runnable state.
	It puts the scheduling entity (task) into the red-black tree and
	increments the nr_running variable.
*/
static void enqueue_task_mycfs(struct rq *rq, struct task_struct *p, int flags){
	printk("enqueue_task_mycfs");
}

/*
	When a task is no longer runnable, this function is called to keep the
   	corresponding scheduling entity out of the red-black tree.  It decrements
   	the nr_running variable.
*/
static void dequeue_task_mycfs(struct rq *rq, struct task_struct *p, int flags){
	printk("dequeue_task_mycfs");
}

/*
	This function is basically just a dequeue followed by an enqueue, unless the
   	compat_yield sysctl is turned on; in that case, it places the scheduling
   	entity at the right-most end of the red-black tree.
*/
static void yield_task_mycfs(struct rq *rq){
	printk("yield_task_mycfs");
}

/*
	This function checks if a task that entered the runnable state should
   	preempt the currently running task. (check_preempt_curr)
*/
static void check_preempt_wakeup(struct rq *rq, struct task_struct *p, int wake_flags){
	printk("check_preempt_curr");
}

// This function chooses the most appropriate task eligible to run next.
static struct task_struct *pick_next_task_mycfs(struct rq *rq){
	printk("pick_next_task_mycfs");
	// return pointer to task struct
	return NULL;
}

// do we need this?
static void put_prev_task_mycfs(struct rq *rq, struct task_struct *prev){
	printk("put_prev_task_mycfs");
}

static int select_task_rq_fair(struct task_struct *p, int sd_flag, int wake_flags){
	printk("select_task_rq_fair");
	return 0;
}

/*
	This function is called when a task changes its scheduling class or changes
   	its task group.
*/
static void set_curr_task_mycfs(struct rq *rq){
	printk("set_curr_task_mycfs");
}

/*
	This function is mostly called from time tick functions; it might lead to
   	process switch.  This drives the running preemption.
*/
static void task_tick_mycfs(struct rq *rq, struct task_struct *curr, int queued){
	printk("task_tick_mycfs");
}


static void prio_changed_mycfs(struct rq *rq, struct task_struct *p, int oldprio){
	printk("prio_changed_mycfs");
}

static void switched_to_mycfs(struct rq *rq, struct task_struct *p){
	printk("switched_to_mycfs");
}

static unsigned int get_rr_interval_mycfs(struct rq *rq, struct task_struct *task){
	printk("get_rr_interval_mycfs");
	return 0;
}