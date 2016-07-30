#include<stdio.h>
#include<unistd.h>
int main(){

pid_t pid = getpid(),pid_c,pid_e;
char cmd[20];

if(fork()==0)					//generates child c
	pid_c = getpid();

if(fork()==0)					//generates child e and d
	if(getppid() == pid_c)
		while(1);			//puts e in while loop
fork();						//generates child b,g and f

if(getpid() == pid)
	{sprintf(cmd , "pstree -p %d\n", pid);
	system(cmd);
	}
else
	while(1);

return 0;
}
