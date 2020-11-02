#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

#include "mylib.h"

void main() 
{					//Process P3
	
	key_t shmKey;
	int shmId;
	struct mem_seg* shmPtr;

	//creting a shared memory key earlier used
	shmKey = ftok(".",'x');
	
	shmId = shmget(shmKey, sizeof(struct mem_seg), IPC_CREAT | 0666);

	if(shmId < 0) {
		printf("*** shmget() error ****\n");
		exit(1);
	}
	
	//attaching the shared memory to the memory space of current process
	shmPtr = (struct mem_seg*)shmat(shmId,NULL,0);

	if(shmPtr == (void*)-1) {
		printf("*** shmat() error \n");
		exit(1);
	}

	printf("Process P3 attached the shared memory.... \n");
	
	//waiting for process P2 to be completed
	while(shmPtr->status != P2_COMPLETED);
	
	printf("reading alphaNum and specialChar variables in shared memory...\n");
	
	printf("No of alphanumeric characters = %d\n",shmPtr->alphaNum);
	printf("No of special charaters = %d\n",shmPtr->specialChar);
	
	if(shmPtr->alphaNum >= shmPtr->specialChar)
		strcpy(shmPtr->buff,"Weak");
	else
		strcpy(shmPtr->buff,"Strong");
	
	//changing status variable to P3_COMPLETED, so that P1 can continue	
	shmPtr->status = P3_COMPLETED;
	
	printf("P3 completed\n");

	shmdt((void *)shmPtr);

	exit(0);

}
