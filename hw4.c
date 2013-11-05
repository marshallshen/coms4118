#include <unistd.h>
#include <stdio.h>
#include <sched.h>

#define SCHED_MYCFS 6

int main() {

	struct sched_param param;
	param.sched_priority = 0;

	printf("pid: %d\n", (int) getpid());

	/*
	int pid;
	if((pid = fork()) == 0){ // child
		printf("child [%d]:\n", pid);
		;
	}else if(pid > 0){ // parent
		printf("parent[%d]:\n", pid);
		;
	}else{	// error
		perror("fork");
		exit(0);
	}
	*/

	int pid = (int) getpid();

	int ret;
	if((ret = sched_setscheduler(0, SCHED_MYCFS, &param)) == -1){
		perror("sched_setscheduler");
		return -1;
	}

	printf("[%d] sched_getscheduler: %d\n", pid, sched_getscheduler(0));

	int i = 0;
	while(++i < 1000){
		printf("[%d] %d\n", pid, i);
	}

	exit(0);
	return 0;
}
