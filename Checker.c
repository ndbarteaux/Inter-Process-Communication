#include<sys/types.h>
#include <sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


int main(int argc, char* argv[]) {
	
	int pid = getpid();
	int divisor = atoi(argv[1]);
	int dividend = atoi(argv[2]);
	int readEnd = atoi(argv[3]);
	char* shared_memory;
	char msg[10];
	
    //Read shared memory ID from pipe, close read end of pipe
	read(readEnd, msg, 10);
	int shm_key = atoi(msg);
	close(readEnd);
	
	//Attach to shared memory
	shared_memory = (char *) shmat(shm_key, NULL, 0);
	if (shared_memory < 0) {
		printf("shmat error\n");
		return 1;
	}
	
	printf("Checker process [%d]: starting.\n", pid);
	printf("Checker process [%d]: read %lu bytes containing shm ID %d\n", pid, sizeof(int), shm_key);
	if(dividend % divisor == 0) {
		printf("Checker process [%d]: %d *IS* divisible by %d.\n", pid, dividend, divisor);
		printf("Checker process [%d]: wrote result (1) to shared memory.\n", pid);
		sprintf(shared_memory, "1");
	}
	
	if(dividend % divisor != 0) {
		printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", pid, dividend, divisor);
		printf("Checker process [%d]: wrote result (0) to shared memory.\n", pid);
		sprintf(shared_memory, "0");
	}
	
	//Detach from shared memory
	shmdt(shared_memory);
	
	exit(0);
	
	
}
