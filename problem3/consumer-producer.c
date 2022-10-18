#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>
int main(int argc, char * argv[]){

	const char *name = "WHISPER";
	const int SIZE = 4096;
	int shm_fd;
	char *ptr;
	char *child_num = argv[1];
	char *order = argv[2];
	char *ori_sentence = argv[3];
	if(strcmp(order,"first") == 0){
	
		shm_fd = shm_open(name,O_CREAT | O_RDWR,0666);
		ftruncate(shm_fd,SIZE);
		ptr = (char *)mmap(0,SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);
		if(ptr == MAP_FAILED){
			printf("Map failed\n");
			return -1;
		
		
		}
		
		char buffer[SIZE];
		strcpy(buffer,ori_sentence);
		size_t buffer_size = strlen(buffer);
		
		srand(time(0));
		
		int n1 = (rand() + getpid()) % buffer_size;
		int n2 = (rand()+ getpid()) % buffer_size;
		char tmp = buffer[n1];
		buffer[n1] = buffer[n2];
		buffer[n2] = tmp;
		
		printf("Child %s: %s\n",child_num,ori_sentence);
		sprintf(ptr,"%s", buffer);
		ptr += strlen(buffer);
	
	}

	if(strcmp(order,"last") == 0){
	
	
	
	
	
	
	
	
		shm_fd = shm_open(name,O_RDONLY, 0666);
		if(shm_fd == -1){
			printf("shared memory failed\n");
			exit(-1);
		}
		ptr =(char *) mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);
		if(ptr == MAP_FAILED){
			printf("Map failed\n");
			exit(-1);
			
		}
		char *heard_sentence = (char *)ptr;
		


		printf("Child %s: %s\n",child_num,heard_sentence);
		if(shm_unlink(name) == -1){
			printf("Error removing %s\n",name);
			exit(-1);
		}
	
	}

	if(strcmp(order,"other") == 0){

		shm_fd = shm_open(name,O_RDWR,0666);
		ftruncate(shm_fd,SIZE);

		ptr =(char *) mmap(0,SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);
		if(ptr == MAP_FAILED){
			printf("Map failed\n");
			return -1;
			
		}
		char *heard_sentence = (char *) ptr;
		
		char buffer[SIZE];
		strcpy(buffer,heard_sentence);
		size_t buffer_size = strlen(buffer);
		srand(time(0));
		int n1 = (rand() + getpid()) % buffer_size;
		int n2 = (rand() + getpid()) % buffer_size;
		char tmp = buffer[n1];
		buffer[n1] = buffer[n2];
		buffer[n2] = tmp;
		
		
		
		
		
		printf("Child %s: %s\n",child_num ,heard_sentence);
		
		sprintf(ptr,"%s",buffer);
		ptr += strlen(heard_sentence);

	
	}
			
			
	
			
			
			
	










	return 0;
}
