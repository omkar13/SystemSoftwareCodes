#include "libtest.h"
#include "stdio.h"

int main(void){

printf("static_test is about to call statically-linked functions in libtest.a...\n");

lib_func1();
lib_func2();


}
