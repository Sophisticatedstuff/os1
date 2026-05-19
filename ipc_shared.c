#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    key_t key;
    int shmid;
    char *shared_mem;

    // Generate unique key
    key = ftok("shmfile", 65);

    // Create shared memory segment (1024 bytes)
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach shared memory
    shared_mem = (char*) shmat(shmid, NULL, 0);

    if (fork() == 0) {
        // Child process
        sleep(1);  // ensure parent writes first
        printf("Child reads: %s\n", shared_mem);
        shmdt(shared_mem);
    } else {
        // Parent process
        strcpy(shared_mem, "Hello from parent via shared memory");
        printf("Parent writes message\n");
        wait(NULL);
        shmdt(shared_mem);
        shmctl(shmid, IPC_RMID, NULL);  // delete shared memory
    }

    return 0;
}
