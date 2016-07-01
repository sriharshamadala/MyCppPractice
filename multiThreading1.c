/**
 * A simple program to understand how to create and exit pthreads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NF_THREADS 15

void * printHelloWorld (void * thread_id) {
    unsigned int tid = ((unsigned int) thread_id);
    printf("Hello World! From thread #%d\n", tid);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    pthread_t threads[NF_THREADS];
    int rc;
    unsigned int ii;
    for (ii=0; ii<NF_THREADS; ii++) {
        printf("Creating thread #%d\n", ii+1);
        /* The argument passed has to be a void pointer. 
         * If we sent pointer to ii instead of ii cast as (void *) the value might change by the time the thread executes and hence the output wont be as expected. 
         * Solution is to use an array to store the arguments sent to each thread.
         * If multiple arguments need to be sent, use a struct.
         */
        rc = pthread_create(&threads[ii], NULL, printHelloWorld, (void *)(ii+1));
        if (rc) {
            printf("Error creating thread #%d\n", ii+1);
            exit(-1);
        }
    }
    // Without this statement the main() may exit before all threads complete execution. This causes threads to terminate without completion.
    pthread_exit(NULL);
    return 0;
}
