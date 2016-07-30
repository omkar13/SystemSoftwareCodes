#include<stdio.h>
#include<unistd.h>

int main(){

pid_t pid = getpid();
char cmd[20];

if(fork()==0)           //child c
        {
        if(fork()==0)
                while(1);       //child e

        if(fork()==0)
                while(1);       //child f
        while(1);
        }

fork();
fork();

if(getpid() == pid){
	
sprintf(cmd , "pstree -p %d\n",pid);
system(cmd);

}

else
	while(1);

}
