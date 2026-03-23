#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    int completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time of P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].completed = 0;
    }

    int completed = 0, time = 0;
    float totalWT = 0;

    while (completed != n) {
        int idx = -1;
        int minBT = INT_MAX;

        // Find the shortest job available at current time
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        // If no process has arrived yet
        if (idx == -1) {
            time++;
            continue;
        }

        // Execute the selected process
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].completed = 1;
        completed++;
        totalWT += p[idx].wt;
    }

    // Output table
    printf("\nSJF Scheduling Result:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);

    return 0;
}
