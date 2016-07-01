/**
 * A simple program to understand pthread_join()
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#define NF_THREADS 4

void * busyWork (void * thread_id) {
    unsigned int tid = ((unsigned int) thread_id);
    float result = 0;
    for (int ii=0; ii<1e6; ii++) {
        result += sin(ii)*cos(ii);
    }
    printf("Finished computation from thread #%d\n", tid);
    pthread_exit((void *)thread_id);
}

int main (int argc, char *argv[]) {
    pthread_t threads[NF_THREADS];
    pthread_attr_t attr;
    int rc;
    unsigned int ii;
    void * status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (ii=0; ii<NF_THREADS; ii++) {
        printf("Creating thread #%d\n", ii+1);
        // Setting the attribute to make the thread joinable is to ensure portability across all systems whose default might be PTHREAD_CREATE_DETACHED. While the latter saves memory resources, the former lets the main wait on the threads.
        rc = pthread_create(&threads[ii], &attr, busyWork, (void *)(ii+1));
        if (rc) {
            printf("Error creating thread #%d\n", ii+1);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);
    for (ii=0; ii<NF_THREADS; ii++) {
        rc = pthread_join(threads[ii], (void *) &status);
        if (rc) {
            printf("Error code returned from join thread #%d is %d\n", (ii+1), rc);
            exit(-1);
        }
        else {
            printf("Finished joining with thread #%d with status %d\n", (ii+1), (int) status);
        }
    }
    // pthread_exit vs pthread_join: If all the main thread is supposed to do is spawn the threads and exit then former. If we need further processing after the threads complete then the latter.
    //pthread_exit(NULL);
    return 0;
}
