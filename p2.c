#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<ctype.h>
#include "mylib.h"

void main() 
{					//process P2
	
	key_t shmKey;
	int shmId;
	struct mem_seg* shmPtr;
	char* c;

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

	printf("Process P2 attached the shared memory.... \n");
	
	//waiting for Process P1 to fill the password values into shared memory
	while(shmPtr->status != CHAR_FILLED_BY_P1);
	
	printf("reading password from shared memory...\n");
	
	c = shmPtr->buff;
	
	//counting no.of alphanumeric and special characters
	for(int i=0;c[i]!='\0';i++) {
		if(isalnum(c[i]))
			(shmPtr->alphaNum)++;
		else
			(shmPtr->specialChar)++;
	}
	
	printf("Password is : %s\n",shmPtr->buff);
	
	//changing status variable to P2_COMPLETED, So that process P3 can take this values
	shmPtr->status = P2_COMPLETED;
	printf("P2 Completed\n");
	shmdt((void *)shmPtr);

	exit(0);

}
