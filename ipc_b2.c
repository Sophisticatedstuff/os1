#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>

int main() {
    int fd[2];
    pid_t pid;
    double a, b, c;
    double four_ac, b2, result, discriminant;

    printf("Enter values of a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    // Create pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    else if (pid == 0) {
        // Child process: compute 4ac
        close(fd[0]); // Close read end

        four_ac = 4 * a * c;
        write(fd[1], &four_ac, sizeof(four_ac));

        close(fd[1]); // Close write end
    }

    else {
        // Parent process: compute b^2 and final expression
        close(fd[1]); // Close write end

        b2 = b * b;
        read(fd[0], &four_ac, sizeof(four_ac));

        close(fd[0]); // Close read end

        discriminant = b2 - four_ac;

        if (discriminant < 0) {
            printf("Discriminant (b^2 - 4ac) = %lf is NEGATIVE.\n", discriminant);
            printf("Square root of a negative number is imaginary. Cannot compute real value.\n");
        } else {
            result = sqrt(discriminant);
            printf("Value of sqrt(b^2 - 4ac) = %lf\n", result);
        }
    }

    return 0;
}
