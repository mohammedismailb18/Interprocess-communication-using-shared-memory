
*******************************************************************************************************
# PROBLEM STATEMENT					
_______________________________________________________________________________________________________

Consider three processes P1, P2, and P3 sharing a memory space. Process P1 receives a character array,
password, of length 10 (contains both special character as well as alphanumeric characters) from the user.
Process P1 stores the received character array in the shared memory. Process P2 calculates the number of
alphanumeric and special characters present. Process P3 then determines the strength of the password by the
following:
- If number of alphanumeric characters ≥ the number of special characters, the
Password is ‘Weak’
- If number of alphanumeric characters < the number of special characters, the
Password is ‘Strong’

Process P3 then communicates to Process P1 the strength of the password as ‘Strong’ or
‘Weak’.

*******************************************************************************************************
# HOW TO RUN THE PROGRAM					
_______________________________________________________________________________________________________


question 2 has three programs p1.c, p2.c and p3.c

-> open three terminals from the directory containing these three programs.

-> In first terminal enter the command for compiling p1.c and create an executable file named 'first' : gcc p1p2.c -o first 

-> In second terminal enter the command for compiling p2.c and create and executable file name 'second' : gcc p3.c -o second

-> In third terminal enter the command for compiling p3.c and create and executable file name 'third' : gcc p3.c -o third

-> To run the executable file run the commands in the appropriate terminals:
	./first
	./second
	./third

-> Now terminal 1 asks the user to enter password, enter the password of length 10 otherwise it will not accept the password and
   ask it again.p1.c prints wheather the password is weak or not.
   
   
*********************************************************************************************************
# WORKING OF THE PROGRAM
_________________________________________________________________________________________________________

-> There are three programs p1.c,p2.c and p3.c. These three programs generate three independent process while executing. 
   ie., p1.c gives process P1, p2.c gives process P2 and p3.c gives process P3.For communicating between these non-related
   process i am using shared memory.

-> I have created a user defined header file called 'mylib.h'.Inside that I have defined four constants, BUFF_SIZE, 
   CHAR_FILLED_BY_P1,P2_COMPLETED and P3_COMPLETED.also defined a structure having an array of size BUFF_SIZE, status 
   variable for storing the status of the processes, alphaNum and specialChar variable for storing number of alpha 
   numeric characters and special characters.

-> Process P1 creates a shared memory key using ftok() function. later it is used with shmget() function to get a 
   shared memory identifier.Then we use shmat() function for getting the address of the shared memory. This shared 
   memory we created is the structure for storing all the details that I have explained earlier.

-> Now Process P1 asks the user to enter password, if the password is of length 10 then P1 accepts it and copied to
   the buff array present in shared memory otherwise it prompts again for password and repeat until user input a 
   password of length 10.After P1 stores a valid password in the shared memory, P1 changes the value of status variable
   present in shared memory to CHAR_FILLED_BY_P1.

-> Whenever P2.c executed, Process P2 attach the same shared memory that we have generated from process P1 to it's memory
   space.By using the same parameters for ftok() function It can get same identifier generated in case of process P1 and 
   hence get the same address of the shared memory.
   
-> Process P2 waits until the shared memory status variable changing to CHAR_FILLED_BY_P1. Whenever it changes, P2 
   retrieve the password string from the buff array present in shared memory.Now P2 calculates the no.of alpha numeric
   and special characters in the string and save that value to the alphaNum and specialChar variable in shared memory.
   Also it changes the status variable to P2_COMPLETED. Then it will detach the shared memory from it's address space 
   using shmdt() function and terminate.

-> The Process P3 attach the shared memory and waits until the status variable changes to P2_COMPLETED. After that, 
   it compares the value present in alphaNum and specialChar.Based on the comparison, P3 writes either 'strong' or 'weak' 
   in the array buff.Then P3 changes the status variable to P3_COMPLETED. Then detaches the shared memory using shmdt() 
   function and the process will get terminated.

-> Process P1 waits until the status variable changes to P3_COMPLETED. It will print the message given by process P3 from
   the buff array.Later it will detach the shared memory using shmdt() function and destroy the shared memory segment using
   shared memory control operation with command IPC_RMID.




