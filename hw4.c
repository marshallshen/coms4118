#include <stdio.h>
#include <sys/utsname.h>
#include <sched.h>
#include <sys/syscall.h>

int main() {
    struct sched_param param;
    param.sched_priority = 0;
    pid_t pid = getpid();
    printf("before setschedule 1, pid: %d", pid);
    syscall(156, pid,6,&param);
    int sch = -1;
    //int sch = syscall(157,pid);
    int number = 1;
    int i;
    printf("before first fork\n");
    if(fork()==0){
	pid = getpid();
    	printf("before setschedule 2, pid: %d\n", pid);
    	syscall(156, pid,6,&param);
	number++;
	if(fork()==0){
		pid = getpid();
    		printf("before setschedule 3, pid: %d\n", pid);
    		printf("before setschedule 3\n");
		syscall(156, pid, 6, &param);
		number++;
	}	
    }
    for(i = 0; i < 10;i++){
    	printf("\nnumber %d, process: %d\n", number,pid);
	wait(100);
    }
    return 0;
}
