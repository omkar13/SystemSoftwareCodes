#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void* threadFunction (void* arg)
{

	int fd ;
	int newlines=0;	
	char temp;

	fd = open((char*)arg , O_RDONLY);

	if(fd == -1)
		{
		//open failed
		printf("open call failed for %s file\n" , (char*)arg);
		pthread_exit(NULL);
		}

	while(read(fd , &temp , 1) != 0)		//end of file reached
	{
	
	if(temp=='\n')
		newlines++;
	}

	printf("filename: %s has  %d newlines.\n",(char*)arg ,newlines );
	pthread_exit(NULL);
	
}

int main(int argc, char** argv)
{

if(argc == 1)				//no filename mentioned
	{
	printf("please give some filenames");
	exit(0);
	}
int i;
pthread_t threads[argc-1];

for(i=1 ; i<=argc-1 ; i++)
{
	pthread_create(&threads[i-1] , NULL , threadFunction , argv[i]);
}

for(i=1 ; i<=argc-1 ; i++)
{
        pthread_join(threads[i-1] , NULL);
}

return 0;
}

