#include <stdio.h> 
#include <string.h>
int main() 
{ 
	int sum; 
	sum = foo(1, 2, 3, "hithere"); 
	printf("sum: %d\n", sum);
} 
int foo(int p1, int p2, int p3, char *p4) 
{
	int acc; 
	char buf[8]; 
	acc = p1+p2+p3; 
	strcpy(buf, p4); 
	return acc; 
}

