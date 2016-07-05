/**
 * Simple example of a deadlock when using semaphores for synchronization.
 * Two threads using the same set of semaphores would likely cause deadlocks, especially if not called in the same order.
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NF_WATER 50
sem_t o_ready;
sem_t h_ready;

void * oxygenFunc (void * ip) {
    static int ii;
    sem_wait(&h_ready);
    sem_wait(&h_ready);
    sem_post(&o_ready);
    sem_post(&o_ready);
    ii++;
    printf("Water molecule #%d\n", ii);
    pthread_exit(NULL);
}

void * hydrogenFunc (void * ip) {
    // If the order of the following sem post and waits are reversed, we would see a deadlock situation.
    sem_wait(&o_ready);
    sem_post(&h_ready);
    pthread_exit(NULL);
}
int main (int argc, char * argv[]) {
    pthread_t o_thread[NF_WATER], h_thread[2*NF_WATER];
    int ii;

    sem_init(&o_ready, 0, 0);
    sem_init(&h_ready, 0, 0);
    printf ("Lets make some water!!\n");
    for (ii=0; ii<NF_WATER; ii++) {
        pthread_create(&o_thread[ii], NULL, oxygenFunc, NULL);
        pthread_create(&h_thread[ii], NULL, hydrogenFunc, NULL);
        pthread_create(&h_thread[ii+NF_WATER], NULL, hydrogenFunc, NULL);
    }

    pthread_exit(NULL);
    return 0;
    }

