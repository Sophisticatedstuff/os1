#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int rt;  // Remaining Time
    int ct;
    int tat;
    int wt;
};

int main() {
    int n, tq, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time of P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int queue[100], front = 0, rear = 0;
    int inQueue[n];
    for (int i = 0; i < n; i++) inQueue[i] = 0;

    // Start by adding all processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while (completed != n) {
        if (front == rear) {
            time++; // CPU idle
            for (int i = 0; i < n; i++)
                if (p[i].at == time && !inQueue[i]) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            continue;
        }

        int idx = queue[front++];
        
        // Execute process
        int execTime = (p[idx].rt < tq ? p[idx].rt : tq);
        time += execTime;
        p[idx].rt -= execTime;

        // Add newly arrived processes
        for (int i = 0; i < n; i++)
            if (p[i].at <= time && !inQueue[i]) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }

        if (p[idx].rt > 0) {
            queue[rear++] = idx; // Re-queue
        } else {
            p[idx].ct = time;
            completed++;
        }
    }

    // Calculate TAT and WT
    float totalWT = 0;
    printf("\nRR Scheduling Result:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalWT += p[i].wt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);

    return 0;
}
