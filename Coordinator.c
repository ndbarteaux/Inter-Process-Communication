#include<sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define READ_END 0
#define WRITE_END 1


int main(int argc, char* argv[]) {
	
	int shm_id;
	char *shared_memory;
	int pid;
	int fd[2];
	char *result[5];
	int shmids[5];
	int pids[5];
	
	for(int i=2; i<argc; i++) {
		// Set up pipe
		pipe(fd);
		
		char passwrite[10];
		sprintf(passwrite, "%d", fd[READ_END]);
		
		// Fork Child
		pid = fork();
		if (pid < 0) {
			printf("fork error\n");
			return 1;
		}
		
		// Child specific
		if (pid == 0) {
			close(fd[WRITE_END]);
			execlp("./Checker", "./Checker", argv[1], argv[i], passwrite, (char*) NULL);
			break;
		}
		
		// Parent specific
		if (pid > 0) {
			pids[i] = pid;
			close(fd[READ_END]);
			// Set up shared memory
			shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0664);
			if (shm_id < 0) {
				printf("shmget error\n");
				return 1;
			}
			shmids[i] = shm_id;
			shared_memory = (char *) shmat(shm_id, NULL, 0);
			if (shared_memory < 0) {
				printf("shmat error\n");
				return 1;
			}
			result[i] = shared_memory;
			// Write ID to the pipe
			char shmString[10];
			sprintf(shmString, "%d", shm_id);
			write(fd[WRITE_END], shmString, 10);
			close(fd[WRITE_END]);
			
			printf("Coordinator: forked process with ID %d.\n", pid);
			printf("Coordinator: wrote shm ID %d to pipe (%lu bytes)\n", shm_id, sizeof(int));
		}
	}

	for(int k=2; k<argc; k++) {
		int childResult;
        //Wait for child processes
		printf("Coordinator: waiting on child process ID %d...\n", pids[k]);
        if(k==2) {
         for(int j=2; j<argc; j++)
             wait(NULL);
        }
        //Get result from shared memory
		sscanf(result[k], "%d", &childResult);
			
		if(childResult == 1) {
			printf("Coordinator: result 1 read from shared memory: %s is divisible by %s.\n", argv[k], argv[1]);
		}
		if(childResult == 0) {
			printf("Coordinator: result 0 read from shared memory: %s is not divisible by %s.\n", argv[k], argv[1]);
		}
        //Detach and delete shared memory
		shmdt(result[k]);
		shmctl(shmids[k], IPC_RMID, NULL);
	}
	
	printf("Coordinator: exiting.\n");
	return 0;
}
