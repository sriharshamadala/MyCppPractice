/**
 * Reader-writer or producer-consumer example.
 * Use of counting semaphore. Alternatively condition variables can be used.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFER_SIZE 10

typedef struct {
    int * buf_head;
    int buf_len;
    int * read_ptr;
    int * write_ptr;
} buffer_t;

sem_t nf_filled_semaphore;
sem_t nf_empty_semaphore;

void * writerFunc (void * ip_buffer) {
    buffer_t * buffer = (buffer_t *) ip_buffer;
    int ii = 0;
    while (1) {
        sem_wait(&nf_empty_semaphore);
        sleep(0.5);
        printf("writing to the buffer...\n");
        *(buffer->write_ptr) = ii;
        // All the boundary condition checking is indirectly handled by the semaphores.
        ii = (ii+1) % MAX_BUFFER_SIZE;
        (buffer->write_ptr) += ii;
        sem_post(&nf_filled_semaphore);
    }
    pthread_exit(NULL);
}

void * readerFunc (void * ip_buffer) {
    buffer_t * buffer = (buffer_t *) ip_buffer;
    int ii = 0;
    while (1) {
        sem_wait(&nf_filled_semaphore);
        sleep(2);
        printf("reading from the buffer. Value = %d\n", *buffer->read_ptr);
        *(buffer->read_ptr) = 0;
        ii = (ii+1) % MAX_BUFFER_SIZE;
        (buffer->read_ptr) += ii; 
        sem_post(&nf_empty_semaphore);
    }
    pthread_exit(NULL);
}

int main (int argc, char * argv[]) {
    buffer_t buffer;
    pthread_t writer, reader;

    // Initializing the buffer
    buffer.buf_head = (int *) malloc(MAX_BUFFER_SIZE*sizeof(int));
    memset(buffer.buf_head, 0, MAX_BUFFER_SIZE*sizeof(int));
    buffer.buf_len = MAX_BUFFER_SIZE;
    buffer.read_ptr = buffer.buf_head;
    buffer.write_ptr = buffer.buf_head;

    sem_init(&nf_filled_semaphore, 0, 0);
    sem_init(&nf_empty_semaphore, 0, MAX_BUFFER_SIZE);
    printf("creating the reader and writer threads...\n");
    pthread_create(&writer, NULL, writerFunc, (void *) &buffer);
    pthread_create(&reader, NULL, readerFunc, (void *) &buffer);

    pthread_exit(NULL);
    return 0;
}
