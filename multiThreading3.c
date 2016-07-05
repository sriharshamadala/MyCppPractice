/**
 * A simple program to understand the use of binary semaphore as a lock to protect global variable access.
 * A very simple example of a critical section that is protected by a  semaphore lock. 
 * There is a global variable numTickets which tracks the number of tickets remaining to sell. 
 * We will create many threads that all will attempt to sell tickets until they are all gone. 
 * However, we must control access to this global variable lest we sell more tickets than really exist. 
 * We have a semaphore lock that will only allow one seller thread to access the numTickets variable at a time. 
 * Before attempting to sell a ticket, the thread must acquire the lock by waiting on the semaphore and then release the lock when through by signalling the semaphore.
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NF_SELLERS 4

// It does not have to be a global variable. Local variable in the main func followed by passing pointer to thread func would work too. 
int nf_tickets = 200;
sem_t ticket_access_semaphore;

void * sellTicket (void * thread_num) {
    int ii = (int) thread_num;
    int nf_tickets_sold_by_me = 0;

    // You should post the semaphore asap to let other threads work.
    while (1) {
        sem_wait(&ticket_access_semaphore);
        if (nf_tickets > 0) {
            nf_tickets--;
            printf("Seller #%d sold ticket #%d\n", ii, nf_tickets);
            sem_post(&ticket_access_semaphore);
            nf_tickets_sold_by_me ++;
        }
        else {
            sem_post(&ticket_access_semaphore);
            printf("All tickets are sold. Seller #%d sold %d tickets\n", ii, nf_tickets_sold_by_me);
            break;
        }
    }
    pthread_exit(NULL);
}

int main (int argc, char * argv[]) {
    pthread_t threads[NF_SELLERS];
    int ii;

    sem_init(&ticket_access_semaphore, 0, 1);
    printf("Let the ticket selling begin!\n");

    for (ii=0; ii<NF_SELLERS; ii++) {
        pthread_create(&threads[ii], NULL, sellTicket, (void *)ii);
    }
    
    pthread_exit(NULL);
    return 0;
}
