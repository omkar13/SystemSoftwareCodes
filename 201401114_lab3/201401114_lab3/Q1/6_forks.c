#include<stdio.h>
#include<unistd.h>

int main()
{
pid_t pid;
char cmd[20];
int flag = 0;

pid = getpid();

if(fork()==0)           //child d
	{	if(fork()==0);
			while(1);		//child g
	while(1);
	}

if(fork()==0)		//child c
	{ 	
	if(fork()==0)
		while(1);	//child e
	
	if(fork()==0)
                while(1);	//child f
	while(1);
	}
if(fork()==0)			//child b
	{
		while(1);
	}
sprintf(cmd , "pstree -p %d\n",pid);
system(cmd);
}
