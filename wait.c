#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();   // Create a new process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("PCCSL407 ");
    }
    else {
        // Parent process waits for the child
        wait(NULL);
        printf("Operating Systems Lab\n");
    }

    return 0;
}
