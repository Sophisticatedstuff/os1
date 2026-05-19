#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define MEALS_PER_PHILOSOPHER 3  // 1. Define a limit for the loops

sem_t room;
sem_t chopstick[N];
sem_t mutex;

void* philosopher(void* num) {
    int id = *(int*)num;

    // 2. Changed from while(1) to a fixed loop
    for (int i = 0; i < MEALS_PER_PHILOSOPHER; i++) {
        // Thinking
        printf("Philosopher %d is thinking (Meal %d/%d)\n", id, i + 1, MEALS_PER_PHILOSOPHER);
        sleep(1);

        sem_wait(&room);  // enter dining room

        sem_wait(&chopstick[id]);              // left chopstick
        sem_wait(&chopstick[(id + 1) % N]);    // right chopstick

        sem_wait(&mutex);
        printf("Philosopher %d is eating\n", id);
        sem_post(&mutex);

        sleep(1); // Reduced sleep time slightly for faster execution

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);

        sem_post(&room);  // leave dining room
    }
    
    printf("--> Philosopher %d has finished all meals and left.\n", id);
    return NULL; // 3. Explicitly return to terminate the thread
}

int main() {
    pthread_t tid[N];
    int phil[N];

    sem_init(&room, 0, N - 1);   // allow only 4 philosophers
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }

    // 4. Main thread waits here until all 5 threads finish their loops
    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    // 5. Clean up semaphores before exiting
    sem_destroy(&room);
    sem_destroy(&mutex);
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }

    printf("Simulation complete. All philosophers are full.\n");
    return 0;
}
