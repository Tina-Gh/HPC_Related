/*C program to illustrate the directive "#pragma GCC poison identifier"*/
/*in order to run, in the terminal: gcc -o bin/example1c example1.c */

#include <stdio.h>

#pragma GCC poison printf

int main(){

    int a = 10;

    if (a == 10){
        printf("this shouldn't print!");
    }
    else{
        printf("This one shouldn't print either!");
    }

    return 0;

}