#include<sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int main(){

        struct timeval current_time;
        time_t t;
        struct tm *info;
        pid_t first_pid,second_pid,third_pid,fourth_pid;
        int s;
        first_pid = fork();

	if(first_pid < 0){
	
		fprintf(stderr,"Fork failed\n");
		return 1;
	}
       
       
	if(first_pid == 0){

                while(true){
                        gettimeofday(&current_time,NULL);
                        t = current_time.tv_sec;
                        info = localtime(&t);
                       
                        printf("I'm the first process and here is  my pid %d and the time is %s\n",getpid() ,asctime(info));
                        sleep(1);
                }

        }
        else{
		
		second_pid = fork();

		if(second_pid < 0){
		
			fprintf(stderr,"Second fork failed");
			
		}

		if(second_pid == 0){
		
			while(true){
				gettimeofday(&current_time,NULL);
				t = current_time.tv_sec;
				info =  localtime(&t);
				printf("I am the second child process and here is my pid %d and the time is  %s\n",getpid(),asctime(info));
				
				sleep(1);
			
			
			}
		
		
		}
		
		else{
		
			third_pid = fork();
			if (third_pid < 0){
			
				fprintf(stderr,"Third fork failed");
			
			
			}

			if(third_pid == 0){
			
			
				while(true){
                               		gettimeofday(&current_time,NULL);
                                	t = current_time.tv_sec;
                                	info =  localtime(&t);
                                	printf("I am the third child process and here is my pid %d and the time is  %s\n",getpid(),asctime(info));
                                	sleep(1);
                        
                        
                        }
			}



			else{
			
				fourth_pid = fork();
                        	if (third_pid < 0){

                                	fprintf(stderr,"Third fork failed");
                        
                        
                       		}	

                        	if(fourth_pid == 0){


                                	while(true){
                                        	gettimeofday(&current_time,NULL);
                                        	t = current_time.tv_sec;
                                        	info =  localtime(&t);
                                        	printf("I am the fourth child process and here is my pid %d, and the time is %s\n",getpid(),asctime(info));
                                        	
                                        	sleep(1);
                

                        		}
				}

				else{
					sleep(5);
					kill(first_pid,SIGKILL);
					printf("First child <%d> killed\n",first_pid);
					kill(second_pid,SIGKILL);
					printf("Second child <%d> killed \n",second_pid);
					kill(third_pid,SIGKILL);
					printf("Third child <%d> killed \n", third_pid);
					kill(fourth_pid,SIGKILL);
					printf("Fourth child <%d> killed\n", fourth_pid);
		
					
					
				
				

				
				}


			
			
			
			
			
			
			
			
			}
                



			}
			
		}






  
}

