#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];

    printf("Enter the requests:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nStep\tFrom\tTo\tMovement\n");
    printf("--------------------------------\n");

    for(int i = 0; i < n; i++) {
        int movement = abs(head - req[i]);

        printf("%d\t%d\t%d\t%d\n", i+1, head, req[i], movement);

        total += movement;
        head = req[i];
    }

    printf("--------------------------------\n");
    printf("Total head movement = %d\n", total);

    return 0;
}
