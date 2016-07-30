#include<stdio.h>
#include<unistd.h>
int main(){

pid_t pid_a = getpid(),pid_c,pid_d;
char cmd[20];

if(fork() == 0)
	pid_c = getpid();	//generates child c

if(fork() == 0)			// generates child f and d
	{if(getppid() == pid_a)
		pid_d = getpid();
	}

//4 processes running currently

if(getpid() == pid_d || getpid() == pid_a)  //generates child b and g
 	{
		if(fork()==0)
			while(1);
	
	}

if(getpid()==pid_c)
	{
	if(fork()==0)				//generates child e
		while(1);
	}

if(getpid()==pid_a)
	{
	sprintf(cmd , "pstree -p %d\n" , pid_a);
	system(cmd);
	}
else
	while(1);
	
return 0;
}
