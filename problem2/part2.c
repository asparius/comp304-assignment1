#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>


#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void){

	char write_msg[BUFFER_SIZE];
	char read_msg1[BUFFER_SIZE];
	char read_msg2[BUFFER_SIZE];
	pid_t pid1,pid2;
	int pipe1[2],pipe2[2],pipe3[2],pipe4[2];
	int num;


	if (pipe(pipe1) == -1){
	
		fprintf(stderr,"Pipe failed");
	
	}

	if(pipe(pipe2) == -1){
	
		fprintf(stderr,"Pipe failed");
	}

	if(pipe(pipe3) == -1){
	
		fprintf(stderr,"Pipe failed");
	}

	if(pipe(pipe4) == -1){
	
		fprintf(stderr,"Pipe failed");
	}

	pid1 = fork();

	if(pid1 < 0){
	
		fprintf(stderr,"Fork failed");
	
	}

	if(pid1 > 0){
	
	
		pid2 = fork();

		if(pid2 < 0){
		
			fprintf(stderr, "Fork failed");
		
		}

		if(pid2 > 0){
			

			sleep(5);	
			close(pipe1[READ_END]);
			close(pipe2[READ_END]);

			close(pipe3[WRITE_END]);
			close(pipe4[WRITE_END]);
			scanf("%d",&num);
			sprintf(write_msg,"%d",num);
			write(pipe1[WRITE_END],write_msg,strlen(write_msg) + 1);
			write(pipe2[WRITE_END],write_msg,strlen(write_msg) + 1);
		       	
			
			read(pipe3[READ_END],read_msg1,BUFFER_SIZE);
			read(pipe4[READ_END],read_msg2,BUFFER_SIZE);

			int out1 = atoi(read_msg1);
			int out2 = atoi(read_msg2);
			int sum  = out1 + out2;
			printf("Final output = %d\n", sum);
			close(pipe1[WRITE_END]);
			close(pipe2[WRITE_END]);
			close(pipe3[READ_END]);
			close(pipe4[READ_END]);
			kill(pid1,SIGKILL);
			kill(pid2,SIGKILL);
			
		
		}


		else{	

			sleep(5);
			char read_msg[BUFFER_SIZE];
			close(pipe1[WRITE_END]);
			close(pipe3[READ_END]);
			
			read(pipe1[READ_END],read_msg,BUFFER_SIZE);
			int input = atoi(read_msg);
			int output = getpid() / input;
			printf("Second Child: Input =%d , Output= %d\n",input,output);
			sprintf(read_msg,"%d",output);
			write(pipe3[WRITE_END],read_msg,strlen(read_msg) + 1);
			close(pipe1[READ_END]);
			close(pipe3[WRITE_END]);
		
		
		}
	
	}


	else{
		sleep(5);
		char read_msg[BUFFER_SIZE];
		close(pipe2[WRITE_END]);
		close(pipe4[READ_END]);

		read(pipe2[READ_END],read_msg,BUFFER_SIZE);
		int input = atoi(read_msg);
		int output = getpid() / input;
		printf("First Child : Input = %d, Output = %d\n",input,output);
		sprintf(read_msg,"%d",output);
		write(pipe4[WRITE_END],read_msg,strlen(read_msg) + 1);
		close(pipe2[READ_END]);
		close(pipe4[READ_END]);
	
	
	
	
	
	
	
	
	
	
	}





	return 0;

}







































