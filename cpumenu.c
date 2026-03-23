#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int pid, at, bt, ct, tat, wt, rt, priority;
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void print(Process p[], int n) {
    float avg_wt = 0, avg_tat = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Avg WT = %.2f\n", avg_wt / n);
    printf("Avg TAT = %.2f\n", avg_tat / n);
}

void fcfs(Process p[], int n) {
    sortByArrival(p, n);
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    print(p, n);
}

void sjf(Process p[], int n) {
    int completed = 0, time = 0, min_bt, index;
    int visited[MAX] = {0};

    while (completed < n) {
        min_bt = 1e9;
        index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i] && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                index = i;
            }
        }
        if (index != -1) {
            time += p[index].bt;
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            visited[index] = 1;
            completed++;
        } else {
            time++;
        }
    }
    print(p, n);
}

void srtf(Process p[], int n) {
    int rt[MAX];
    for (int i = 0; i < n; i++) rt[i] = p[i].bt;

    int completed = 0, time = 0, min_rt, index;

    while (completed < n) {
        min_rt = 1e9;
        index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                index = i;
            }
        }
        if (index != -1) {
            rt[index]--;
            time++;
            if (rt[index] == 0) {
                completed++;
                p[index].ct = time;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
            }
        } else {
            time++;
        }
    }
    print(p, n);
}

void priority_np(Process p[], int n) {
    int completed = 0, time = 0, index;
    int visited[MAX] = {0};

    while (completed < n) {
        int highest = 1e9;
        index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !visited[i] && p[i].priority < highest) {
                highest = p[i].priority;
                index = i;
            }
        }
        if (index != -1) {
            time += p[index].bt;
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            visited[index] = 1;
            completed++;
        } else {
            time++;
        }
    }
    print(p, n);
}

void roundRobin(Process p[], int n, int quantum) {
    int rt[MAX];
    for (int i = 0; i < n; i++) rt[i] = p[i].bt;

    int time = 0, completed = 0;

    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && p[i].at <= time) {
                done = 0;
                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                } else {
                    time += rt[i];
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    rt[i] = 0;
                    completed++;
                }
            }
        }
        if (done) time++;
    }
    print(p, n);
}

int main() {
    Process p[MAX];
    int n, choice, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("P%d AT BT Priority: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].pid = i + 1;
    }

    do {
        printf("\n1.FCFS\n2.SJF\n3.SRTF\n4.Priority (Non-Preemptive)\n5.Round Robin\n6.Exit\nChoose: ");
        scanf("%d", &choice);

        Process temp[MAX];
        for (int i = 0; i < n; i++) temp[i] = p[i];

        switch (choice) {
            case 1: fcfs(temp, n); break;
            case 2: sjf(temp, n); break;
            case 3: srtf(temp, n); break;
            case 4: priority_np(temp, n); break;
            case 5:
                printf("Enter Time Quantum: ");
                scanf("%d", &quantum);
                roundRobin(temp, n, quantum);
                break;
        }
    } while (choice != 6);

    return 0;
}
