#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

#include "mylib.h"

void main() 
{				//process P1
	
	key_t shmKey;
	int shmId;
	struct mem_seg* shmPtr;

	//creting a shared memory key using ftok
	shmKey = ftok(".",'x');
	
	//created a shared memory segment
	shmId = shmget(shmKey, sizeof(struct mem_seg), IPC_CREAT | 0666);

	if(shmId < 0) {
		printf("*** shmget() error ****\n");
		exit(1);
	}
	
	//attaching the shared memory segment to the memory space of current process P1
	shmPtr = (struct mem_seg*)shmat(shmId,NULL,0);

	if(shmPtr == (void*)-1) {
		printf("*** shmat() error \n");
		exit(1);
	}

	printf("Process P1 created and attached the shared memory.... \n");
	
	//Taking user input
	while(1) {
	printf("Enter the password :  ");
	fgets(shmPtr->buff,sizeof(shmPtr->buff),stdin);
	char* str = shmPtr->buff;
	int n = strlen(str);
	str[n - 1] = '\0';
	if(n == 11)		//while taking the user input 11th character will be enter key.
		break;
	printf("Password length should be of length 10\n");
	}
		
	//changing status flag to CHAR_FILLED_BY_P1 which is defined in mylib.h
	shmPtr->status = CHAR_FILLED_BY_P1;

	//whenever Process P3 completed it's task Process P3 change the value of status variable in the shared memory to P3_COMPLETED,
	//upto that moment process P1 waits here
	while(shmPtr->status!=P3_COMPLETED);

	printf("reading what P3 written to shared memory... \n");

	printf("The password is %s\n",shmPtr->buff);
	
	//After detaching the shared memory, destroying the shared memory segment using shared memory control operation with command IPC_RMID
	shmdt((void *)shmPtr);
	shmctl(shmId, IPC_RMID, NULL);
	
	printf("Pocess P1 detached and deallocated the shared memory\n");
	exit(0);

}
