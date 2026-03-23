#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt, readTry;
int readCount = 0;

// Reader Priority
void *reader_priority_reader(void *arg) {
    sem_wait(&mutex);
    readCount++;
    if (readCount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %ld is reading\n", (long)arg);
    sleep(1);

    sem_wait(&mutex);
    readCount--;
    if (readCount == 0)
        sem_post(&wrt);
    sem_post(&mutex);

    return NULL;
}

void *reader_priority_writer(void *arg) {
    sem_wait(&wrt);

    printf("Writer %ld is writing\n", (long)arg);
    sleep(1);

    sem_post(&wrt);
    return NULL;
}

// Writer Priority
int writeCount = 0;

void *writer_priority_reader(void *arg) {
    sem_wait(&readTry);
    sem_wait(&mutex);

    readCount++;
    if (readCount == 1)
        sem_wait(&wrt);

    sem_post(&mutex);
    sem_post(&readTry);

    printf("Reader %ld is reading\n", (long)arg);
    sleep(1);

    sem_wait(&mutex);
    readCount--;
    if (readCount == 0)
        sem_post(&wrt);
    sem_post(&mutex);

    return NULL;
}

void *writer_priority_writer(void *arg) {
    sem_wait(&mutex);
    writeCount++;
    if (writeCount == 1)
        sem_wait(&readTry);
    sem_post(&mutex);

    sem_wait(&wrt);

    printf("Writer %ld is writing\n", (long)arg);
    sleep(1);

    sem_post(&wrt);

    sem_wait(&mutex);
    writeCount--;
    if (writeCount == 0)
        sem_post(&readTry);
    sem_post(&mutex);

    return NULL;
}

int main() {
    int choice, n;
    pthread_t r[10], w[10];

    printf("Enter number of readers/writers: ");
    scanf("%d", &n);

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    sem_init(&readTry, 0, 1);

    do {
        printf("\n1. Reader Priority\n2. Writer Priority\n3. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Reader Priority Execution ---\n");
                readCount = 0;
                for (long i = 0; i < n; i++) {
                    pthread_create(&r[i], NULL, reader_priority_reader, (void *)i);
                    pthread_create(&w[i], NULL, reader_priority_writer, (void *)i);
                }
                for (int i = 0; i < n; i++) {
                    pthread_join(r[i], NULL);
                    pthread_join(w[i], NULL);
                }
                break;

            case 2:
                printf("\n--- Writer Priority Execution ---\n");
                readCount = 0;
                writeCount = 0;
                for (long i = 0; i < n; i++) {
                    pthread_create(&r[i], NULL, writer_priority_reader, (void *)i);
                    pthread_create(&w[i], NULL, writer_priority_writer, (void *)i);
                }
                for (int i = 0; i < n; i++) {
                    pthread_join(r[i], NULL);
                    pthread_join(w[i], NULL);
                }
                break;
        }
    } while (choice != 3);

    return 0;
}
