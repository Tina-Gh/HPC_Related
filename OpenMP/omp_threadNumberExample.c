/*In order to run:
>> gcc -o bin/ompthreadnumberc -fopenmp  omp_threadNumberExample.c
>> bin/ompthreadnumberc
*/ 

#include <stdio.h>
#include <omp.h>

int main(){

    omp_set_num_threads(8);

    #pragma omp parallel default(none)
    {
        printf("Hello world, from thread# %d!\n", omp_get_thread_num());
    }

    return 0;
}



