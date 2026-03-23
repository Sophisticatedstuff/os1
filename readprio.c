#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;   // Controls access to shared resource
sem_t mutex;      // Controls read_count access
int read_count = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);  // First reader blocks writers
    sem_post(&mutex);

    // Critical Section
    printf("Reader %d is READING\n", id);
    sleep(1);
    printf("Reader %d is DONE reading\n", id);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);  // Last reader releases writers
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&rw_mutex);  // Writer needs exclusive access

    // Critical Section
    printf("\tWriter %d is WRITING\n", id);
    sleep(2);
    printf("\tWriter %d is DONE writing\n", id);

    sem_post(&rw_mutex);

    return NULL;
}

int main() {
    pthread_t r[5], w[5];
    int ids[5];

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < 5; i++)
        ids[i] = i + 1;

    for (int i = 0; i < 5; i++) {
        pthread_create(&r[i], NULL, reader, &ids[i]);
        pthread_create(&w[i], NULL, writer, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
        pthread_join(w[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
