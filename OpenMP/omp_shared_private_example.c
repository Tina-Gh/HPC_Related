#include <time.h> /*A random thing for myself to check the execution time*/
#include <stdio.h>
#include <omp.h>
#define N 10000
#define CHUNKSIZE 100

double time1, timedif;

int main(){

    time1 = (double) clock(); /*gets nitial time*/
    time1 = time1 / CLOCKS_PER_SEC; /*in seconds*/

    int i, chunk;
    float a[N], b[N], c[N]; 

    /*Initializing vectors*/ 
    for (int i=0; i<N; i++){
        a[i] = i;
        b[i] = a[i] * N;
    }

    chunk = CHUNKSIZE;

    #pragma omp parallel shared(a, b, c, chunk) private(i)
    {
        #pragma omp parallel for schedule(dynamic, chunk)
            for (int i=0; i<N; i++){
                c[i] = a[i] + b[i];
            }
    } /*End of paralle region*/

    for (int i=0; i<10; i++) printf("%17.1f %17.1f %17.1f\n", a[i], b[i], c[i]);
    printf("...\n");
    for (int i=N-10; i<N; i++) printf("%17.1f %17.1f %17.1f\n", a[i], b[i], c[i]);

    timedif = (((double) clock()) / CLOCKS_PER_SEC) - time1;
    printf("The elapsed time is %f seconds\n", timedif);

}

/*Output:

The elapsed time is 0.012248 seconds
*/


/*Analysis and Comparison:

Comparing code "omp_shared_private_example.c" with this code "shared_private_no_omp.c" (which are the same code except this one
doesn't use openMP and parallelization) shows that using openMP takes more time! Previously, I thought using threads ad parallelization 
reduces the execution time, but that's not the case.
*/

/* Explaination and Fixes:

1. Nested #pragma omp parallel Directives
You have two #pragma omp parallel directives, one inside the other. This creates nested parallel regions, which is often inefficient 
unless you explicitly need nested parallelism. OpenMP by default creates one thread per core for a parallel region, so nesting may create
more threads than necessary, adding overhead. You only need the #pragma omp parallel for directive, as it already indicates that the 
loop is to be parallelized.
Fix: Remove the outer #pragma omp parallel directive and keep only the #pragma omp parallel for. 
=> After applying this fix, the elapsed time is 0.003271 seconds

2. Small Problem Size
The array size (N=10000) might not be large enough to see the benefits of parallelization. The overhead of creating and managing threads 
can outweigh the performance gains for small datasets. To observe a significant speedup, you typically need a larger problem size where 
the computation time dominates the overhead of threading.
Fix: Try increasing N (e.g., N=1000000 or larger) and see if the parallel version performs better.
=> 14363 segmentation fault (core dumped)  bin/omp_fix_2

3. Dynamic Scheduling
You're using schedule(dynamic, chunk), which means threads are assigned chunks of iterations dynamically as they finish their current 
work. This can be beneficial when iterations take varying amounts of time, but in this case, all iterations likely take the same time 
since you're performing simple additions. Dynamic scheduling adds overhead due to task redistribution.
Fix: Try using static scheduling (schedule(static)) instead, which evenly divides the work at the start.
=> segmentation fault

4. Clock Overhead
The timing method used (clock()) measures CPU time rather than wall time. When using multiple threads, CPU time increases as it counts 
the time for each thread. Using omp_get_wtime() to measure the actual elapsed wall time is more appropriate for parallelized code.
Fix: Replace your timing logic with omp_get_wtime().
=> The elapsed time is 0.004322 seconds
*/