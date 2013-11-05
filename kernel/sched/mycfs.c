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
static void enqueue_entity(struct mycfs_rq *mycfs, struct sched_mycfs_entity *se);
static void dequeue_entity(struct mycfs_rq *mycfs, struct sched_mycfs_entity *se);
static void yield_task_mycfs(struct rq *rq);
static void check_preempt_curr_mycfs(struct rq *rq, struct task_struct *p, int wake_flags);
static struct task_struct *pick_next_task_mycfs(struct rq *rq);
static void put_prev_task_mycfs(struct rq *rq, struct task_struct *prev);
static int select_task_rq_mycfs(struct task_struct *p, int sd_flag, int wake_flags);
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
	.check_preempt_curr = check_preempt_curr_mycfs,
	.pick_next_task = pick_next_task_mycfs,
	.put_prev_task = put_prev_task_mycfs,
	.select_task_rq = select_task_rq_mycfs, // select different rq based on processor
	.set_curr_task = set_curr_task_mycfs,
	.task_tick = task_tick_mycfs,
	.prio_changed = prio_changed_mycfs,
	.switched_to = switched_to_mycfs,
	.get_rr_interval = get_rr_interval_mycfs

	// we don't need:
	// .yield_to_task =
	// .rq_online = N
	// .rq_offline =  N
	// .task_waking = ?
	// .task_fork = yes
	// .switched_from = yes
	// .task_move_group =

};

/*
	Called when a task enters a runnable state.
	It puts the scheduling entity (task) into the red-black tree and
	increments the nr_running variable.
*/
static void enqueue_task_mycfs(struct rq *rq, struct task_struct *p, int flags){
	// get our runqueue
	struct mycfs_rq *mycfs = &rq->mycfs;
        struct sched_mycfs_entity *sme = &p->sme;	
	
	printk("first entering enqueue\n");
	// add the task to our runqueue - just one process for now
	printk("pid inserted:%d \n",p->pid);
	enqueue_entity(mycfs, sme);
	
	// increment nr_running
	flags = ENQUEUE_WAKEUP;
	inc_nr_running(rq);
	printk(KERN_INFO "enqueue_task_mycfs\n");
}

/*
	When a task is no longer runnable, this function is called to keep the
   	corresponding scheduling entity out of the red-black tree.  It decrements
   	the nr_running variable.
*/
static void dequeue_task_mycfs(struct rq *rq, struct task_struct *p, int flags){

	struct mycfs_rq *mycfs = &rq->mycfs;
	struct sched_mycfs_entity *sme = &p->sme;

	dequeue_entity(mycfs, sme);

	printk(KERN_INFO "dequeue_task_mycfs\n");

}

static inline int entity_before(struct sched_mycfs_entity *a, struct sched_mycfs_entity *b)
{
	return (s64)(a->vruntime - b->vruntime) < 0;
}

static void enqueue_entity(struct mycfs_rq *mycfs, struct sched_mycfs_entity *sme)
{
	struct rb_node **link = &mycfs->tasks_timeline.rb_node;
	struct rb_node *parent = NULL;
	struct sched_mycfs_entity *entry;

	while(*link){
		parent = *link;
		entry = rb_entry(parent, struct sched_mycfs_entity, run_node);
		if(entity_before(sme,entry)){
			link = &parent->rb_left;
		} else {
			link = &parent->rb_right;
		}
	}
	rb_link_node(&sme->run_node, parent, link);
	rb_insert_color(&sme->run_node, &mycfs->tasks_timeline);
}


static void dequeue_entity(struct mycfs_rq *mycfs, struct sched_mycfs_entity *sme)
{
	rb_erase(&sme->run_node, &mycfs->tasks_timeline);
}

/*
	This function is basically just a dequeue followed by an enqueue, unless the
   	compat_yield sysctl is turned on; in that case, it places the scheduling
   	entity at the right-most end of the red-black tree.
*/
static void yield_task_mycfs(struct rq *rq){
	printk(KERN_INFO "yield_task_mycfs\n");
}

/*
	This function checks if a task that entered the runnable state should
   	preempt the currently running task. (check_preempt_curr)
*/
static void check_preempt_curr_mycfs(struct rq *rq, struct task_struct *p, int wake_flags){
	printk(KERN_INFO "check_preempt_curr\n");
}

// This function chooses the most appropriate task eligible to run next.	
static struct task_struct *pick_next_task_mycfs(struct rq *rq){
/*
	struct mycfs_rq *mycfs = &rq->mycfs;
	struct task_struct *next = mycfs->waiting;

	if(next){
		printk(KERN_INFO "pick_next_task_mycfs: return next %d", (int) next->pid);
		return next;
	}
*/
	
	return NULL;
}

// do we need this - YES
static void put_prev_task_mycfs(struct rq *rq, struct task_struct *prev){
	printk(KERN_INFO "put_prev_task_mycfs\n");
}

static int select_task_rq_mycfs(struct task_struct *p, int sd_flag, int wake_flags){
	printk(KERN_INFO "select_task_rq_fair\n");
	return 0;
}

/*
	This function is called when a task changes its scheduling class or changes
   	its task group.
*/
static void set_curr_task_mycfs(struct rq *rq){
	printk(KERN_INFO "set_curr_task_mycfs\n");
}

/*
	This function is mostly called from time tick functions; it might lead to
   	process switch.  This drives the running preemption.
*/
static void task_tick_mycfs(struct rq *rq, struct task_struct *curr, int queued){
	printk(KERN_INFO "task_tick_mycfs\n");
}


static void prio_changed_mycfs(struct rq *rq, struct task_struct *p, int oldprio){
	printk(KERN_INFO "prio_changed_mycfs\n");
}

static void switched_to_mycfs(struct rq *rq, struct task_struct *p){
	printk(KERN_INFO "switched_to_mycfs\n");
}

static unsigned int get_rr_interval_mycfs(struct rq *rq, struct task_struct *task){
	printk(KERN_INFO "get_rr_interval_mycfs\n");
	return 0;
}
