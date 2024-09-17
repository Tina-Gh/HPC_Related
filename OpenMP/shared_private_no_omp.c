#include <time.h> /*A random thing for myself to check the execution time*/
#include <stdio.h>
#define N 10000


double time1, timedif;

int main(){

    time1 = (double) clock(); /*gets nitial time*/
    time1 = time1 / CLOCKS_PER_SEC; /*in seconds*/

    int i;
    float a[N], b[N], c[N]; 

    /*Initializing vectors*/ 
    for (int i=0; i<N; i++){
        a[i] = i;
        b[i] = a[i] * N;
    }



    for (int i=0; i<N; i++){
        c[i] = a[i] + b[i];
    }


    for (int i=0; i<10; i++) printf("%17.1f %17.1f %17.1f\n", a[i], b[i], c[i]);
    printf("...\n");
    for (int i=N-10; i<N; i++) printf("%17.1f %17.1f %17.1f\n", a[i], b[i], c[i]);

    timedif = (((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("The elapsed time is %f seconds\n", timedif);

}

/*Output:

The elapsed time is 0.000272 seconds
*/

/*Analysis and Comparison:

Comparing code "omp_shared_private_example.c" with this code "shared_private_no_omp.c" (which are the same code except this one
doesn't use openMP and parallelization) shows that using openMP takes more time! Previously, I thought using threads ad parallelization 
reduces the execution time, but that's not the case.
*/


