#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
pthread_t phil[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        // Pick left fork
        sem_wait(&forks[id]);
        printf("Philosopher %d picked left fork %d\n", id, id);

        // Pick right fork
        sem_wait(&forks[(id + 1) % N]);
        printf("Philosopher %d picked right fork %d\n", id, (id + 1) % N);

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        // Put forks down
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        printf("Philosopher %d finished eating\n", id);
    }
}

int main() {
    int i, ids[N];

    for (i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }

    return 0;
}
