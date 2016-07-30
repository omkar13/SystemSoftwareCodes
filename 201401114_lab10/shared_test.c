#include <stdio.h>
#include "libtest.h"

int main(){

printf("shared_test is about to call dynamically -linked functions in libtest.so...\n");

lib_func1();
lib_func2();


}
