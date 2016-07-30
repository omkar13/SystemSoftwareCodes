#include<stdio.h>
#include<stdlib.h>

int main(){

union u{
	int i;
	char c;
	}u1;

u1.i=1;
if(u1.c ==1 )
	printf("little endian\n ");
else
 	printf("big endian\n");

return 0;
}

