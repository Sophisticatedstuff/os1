#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int at;
    int bt;
    int priority;
    int ct, tat, wt;
    int completed;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time for P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter Priority for P%d: ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].completed = 0;
    }

    int completed = 0, time = 0;
    float totalWT = 0;

    while (completed != n) {
        int idx = -1;
        int bestPriority = -1; // For highest priority selection

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time) {
                // Higher number = higher priority
                if (p[i].priority > bestPriority) {
                    bestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        p[idx].completed = 1;
        completed++;

        totalWT += p[idx].wt;
    }

    printf("\nNon-Preemptive Priority Scheduling Result:\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);

    return 0;
}
