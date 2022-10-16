#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){


	char *name_of_exe = argv[1];
	int num_of_children = atoi(argv[2]);
	char *ori_sentence = argv[3];
	char *args[] = {name_of_exe, "1","first",ori_sentence,NULL};
	int status;
	pid_t value;
	char *child_num;
	for(int i = 0; i < num_of_children;i++){
	
		value = fork();	
					
		if(value == 0){
			
				
			if(i == 0){
				printf("Am I ever in iter %d\n",i);
				execv(name_of_exe,args);	
				
				return 1;
				
				
			
				}
			if( i > 0 && i < num_of_children -1){
				printf("Am I ever in iter %d\n",i);	
				printf("Why I am not in here");
				sprintf(child_num,"%d",i);
				printf("child num : %s\n",child_num);
				args[1] = child_num;
				args[2] = "other";
				printf("What is the problem?\n");	
				execv(name_of_exe,args);
				
				return 1;

				

				
				
				}
			if( i ==  num_of_children -1){
			
				
				sprintf(child_num,"%d",i);
				args[1] = child_num;
				args[2] = "last";

				if(execv(name_of_exe,args) == -1){
				
					printf("Could not executre consumer-producer");
				}
				
				return 1;	
			}
			
			
			
		
			}		
		
		}

	
	
	for(int i = 0; i < num_of_children;i++)
		value = wait(&status);
		if(value == -1){
			perror("wait() failed");
		
		}

	printf("Parent terminating...\n");









	return 0;
}
