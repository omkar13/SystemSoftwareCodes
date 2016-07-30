#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<string.h>

int main(){

int fd1[2],fd2[2],fd3[2],fd4[2];
int n;

pipe(fd1);
pipe(fd2);
pipe(fd3);
pipe(fd4);

pid_t cpid1,cpid2,cpid3;

if((cpid1=fork())==0)
	{				// in child 1
		
	//close all reads except 1
	close(fd2[0]);			
	close(fd3[0]);
	close(fd4[0]);

	//close all writes
	close(fd1[1]);
	close(fd2[1]);
	close(fd3[1]);
	close(fd4[1]);
	
	//char temp[1];
	char message[100];

	sleep(1);	

	while( read(fd1[0] , message ,100) > 0 )
	{
	printf("Child 1 read: %s",  message );
	}
	
	printf("C1 exiting... \n");
	exit(0);
	}

if((cpid2=fork())==0)
        {				// in child 2
	//close 1st and 3rd read
 	 close(fd1[0]);
        close(fd3[0]);
        
	//close all writes except 3
	 close(fd1[1]);
        close(fd2[1]);
        close(fd4[1]);

	//sleep(1);	

	char message[100];
	int a,flag = 0;	// if flag is set message is transferred

	
	while( read(fd2[0] , message , 100) > 0 )
		{
		printf("i am in upper while loop of child 2\n");
		for( a=0 ;a<100 ;a++ )
			{
			if(message[a] == '@')
				{
				break;
				}
			else if(message[a] == '#')
				{
				char buf[a];
				strncpy(buf , message , a);
				printf("* Forwarding message along Pipe P3.");
				write( fd3[1] , buf , a );
				flag =1;		
				}			
			}
		
		if(flag == 0)	
		 	printf("Child 2 read: %s " , message );

		}	
	printf("in child 2, upper while loop finished\n");
	
	 while( read(fd4[0] , message ,100) > 0 )
        	    	printf("Child 2 read: %s " , message );

close(fd3[1]);
	//printf("Child 2 read: " + message );
        printf("C2 exiting... \n");
        close(fd4[0]);
	close(fd2[0]);
//	close(fd3[1]);
	exit(1);

        }

if((cpid3=fork())==0)
        {				// in child 3
	//close reads 1 and 4
	 close(fd1[0]);
        close(fd4[0]);

	//close all writes except 4
	 close(fd1[1]);
        close(fd2[1]);
        close(fd3[1]);

	 char message[100];
         int a;
	
	sleep(1);

	while( read(fd2[0] , message , 100) > 0 )
                {
		printf("i am in upper while loop of child 3\n");

                for( a=0 ;a<100 ;a++ )
                        {
                        if(message[a] == '#')
                                {
                                break;
                                }
                        else if(message[a] == '@')
                                {
                                char buf[a];
                                strncpy(buf , message , a);
                                printf("* Forwarding message along Pipe P4.");
                                write( fd4[1] , buf , a );
                                }                                 
                        }
		 printf("Child 3 read: %s " , message );
                }

	close(fd4[1]);

	 while( read(fd3[0] , message ,100) > 0 )                       
                        printf("Child 3 read: %s" , message );


//	  printf("Child 3 read: " + message );
        printf("C3 exiting...\n ");
        close(fd2[0]);
	close(fd3[0]);
//	close(fd4[1]);
	exit(1);

        }

// execute only in parent - how?

//close all reads in parent
close(fd1[0]);
close(fd2[0]);
close(fd3[0]);
close(fd4[0]);

// close write end of 3rd and 4th pipe
close(fd3[1]);
close(fd4[1]);




printf("-Hello, I am the parent. How many messages should I send?\n");

scanf("%d" , &n);

printf("give the messages in the following format: <message string> <child to receive message>");
char message[20];
int child_no , message_length;

while(n-- > 0)
	{
	scanf("%s" ,message);
	message_length = strlen(message);	

	scanf("%d" ,&child_no );	
	
	if(child_no == 1)
		{			//send to child 1 through pipe 1
		write(fd1[1] , message ,message_length );	
		printf("+ Sent message along Pipe P1.\n");
		}
	else if(child_no == 2)
		{			//send to child 2 through pipe 2
		message[message_length] = '@'; //special character for child 2
		write(fd2[1] , message , message_length + 1);
		printf("+ Sent message along Pipe P2.\n");
		}
	else if(child_no == 3)
                {                       //send to child 3 through pipe 2
        	message[message_length] = '#'; //special character for child 3
                write(fd2[1] , message , message_length + 1);
		printf("+ Sent message along Pipe P2.\n");
                 }
	}
//close the write ends
close(fd1[1]);
close(fd2[1]); 

printf("now let us wait for the children\n");

waitpid(cpid1, NULL , 0);
printf("child 1 reaped\n");
waitpid(cpid2, NULL , 0);
printf("child 2 reaped\n");
waitpid(cpid3, NULL , 0);
printf("child 3 reaped\n");

printf("parent exiting\n");
return 0;
}
