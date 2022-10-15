#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
int main(){

	struct timeval current_time;
	time_t t;
	struct tm *info;
	pid_t pid;
	int s;
	pid = fork();

			
	if(pid == 0){
		
		while(true){	
			gettimeofday(&current_time,NULL);
			t = current_time.tv_sec;
			info = localtime(&t);	
			printf("I am the child process and here is my pid %d\n", getpid());
			printf("The time is %s", asctime(info));
			sleep(1);
		}	

	}
	else{
		
		sleep(5);
		
		
					
 
     		kill(pid, SIGKILL);
 
				
		printf("I am the parent process and Child  <%d> killed.\n", pid);
	
	
		}	



	return 0;
}







