#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
    }
}

int fcfs(int req[], int n, int head) {
    int seek = 0;
    for (int i = 0; i < n; i++) {
        seek += abs(head - req[i]);
        head = req[i];
    }
    return seek;
}

int sstf(int req[], int n, int head) {
    int visited[MAX] = {0};
    int seek = 0;

    for (int i = 0; i < n; i++) {
        int min = 1e9, idx = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int d = abs(head - req[j]);
                if (d < min) {
                    min = d; idx = j;
                }
            }
        }
        visited[idx] = 1;
        seek += min;
        head = req[idx];
    }
    return seek;
}

int scan(int req[], int n, int head, int size, int dir) {
    int seek = 0;
    int left[MAX], right[MAX];
    int l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    if (dir == 1) { // right
        for (int i = 0; i < r; i++) {
            seek += abs(head - right[i]);
            head = right[i];
        }
        seek += abs(head - (size - 1));
        head = size - 1;
        for (int i = l - 1; i >= 0; i--) {
            seek += abs(head - left[i]);
            head = left[i];
        }
    } else {
        for (int i = l - 1; i >= 0; i--) {
            seek += abs(head - left[i]);
            head = left[i];
        }
        seek += abs(head - 0);
        head = 0;
        for (int i = 0; i < r; i++) {
            seek += abs(head - right[i]);
            head = right[i];
        }
    }
    return seek;
}

int cscan(int req[], int n, int head, int size) {
    int seek = 0;
    int left[MAX], right[MAX];
    int l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    for (int i = 0; i < r; i++) {
        seek += abs(head - right[i]);
        head = right[i];
    }

    seek += abs(head - (size - 1));
    head = 0;
    seek += (size - 1);

    for (int i = 0; i < l; i++) {
        seek += abs(head - left[i]);
        head = left[i];
    }

    return seek;
}

int look(int req[], int n, int head, int dir) {
    int seek = 0;
    int left[MAX], right[MAX];
    int l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head) left[l++] = req[i];
        else right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    if (dir == 1) {
        for (int i = 0; i < r; i++) {
            seek += abs(head - right[i]);
            head = right[i];
        }
        for (int i = l - 1; i >= 0; i--) {
            seek += abs(head - left[i]);
            head = left[i];
        }
    } else {
        for (int i = l - 1; i >= 0; i--) {
            seek += abs(head - left[i]);
            head = left[i];
        }
        for (int i = 0; i < r; i++) {
            seek += abs(head - right[i]);
            head = right[i];
        }
    }
    return seek;
}

int main() {
    int req[MAX], n, head, size, choice, dir;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    do {
        printf("\n1.FCFS\n2.SSTF\n3.SCAN\n4.C-SCAN\n5.LOOK\n6.Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Total Seek Time (FCFS): %d\n", fcfs(req, n, head));
                break;
            case 2:
                printf("Total Seek Time (SSTF): %d\n", sstf(req, n, head));
                break;
            case 3:
                printf("Enter direction (0=left,1=right): ");
                scanf("%d", &dir);
                printf("Total Seek Time (SCAN): %d\n", scan(req, n, head, size, dir));
                break;
            case 4:
                printf("Total Seek Time (C-SCAN): %d\n", cscan(req, n, head, size));
                break;
            case 5:
                printf("Enter direction (0=left,1=right): ");
                scanf("%d", &dir);
                printf("Total Seek Time (LOOK): %d\n", look(req, n, head, dir));
                break;
        }
    } while (choice != 6);

    return 0;
}
