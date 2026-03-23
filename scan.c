#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j]>a[j+1]) {
                int t=a[j]; a[j]=a[j+1]; a[j+1]=t;
            }
}

int main() {
    int n, head, size, dir;
    int total = 0;

    printf("Enter number of requests: ");
    scanf("%d",&n);

    int req[n];
    printf("Enter requests:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&req[i]);

    printf("Enter initial head position: ");
    scanf("%d",&head);

    printf("Enter disk size (max track number): ");
    scanf("%d",&size);

    printf("Enter direction (1=RIGHT, 0=LEFT): ");
    scanf("%d",&dir);

    sort(req,n);

    printf("\nStep\tFrom\tTo\tMovement\n");
    printf("--------------------------------\n");

    int cur = head, step = 1;

    if(dir==1) { // RIGHT

        for(int i=0;i<n;i++){
            if(req[i] >= head){
                printf("%d\t%d\t%d\t%d\n",step++,cur,req[i],abs(cur-req[i]));
                total += abs(cur-req[i]);
                cur = req[i];
            }
        }

        // move to disk end
        printf("%d\t%d\t%d\t%d\n",step++,cur,size-1,abs(cur-(size-1)));
        total += abs(cur-(size-1));
        cur = size-1;

        // reverse direction
        for(int i=n-1;i>=0;i--){
            if(req[i] < head){
                printf("%d\t%d\t%d\t%d\n",step++,cur,req[i],abs(cur-req[i]));
                total += abs(cur-req[i]);
                cur = req[i];
            }
        }

    } else { // LEFT

        for(int i=n-1;i>=0;i--){
            if(req[i] <= head){
                printf("%d\t%d\t%d\t%d\n",step++,cur,req[i],abs(cur-req[i]));
                total += abs(cur-req[i]);
                cur = req[i];
            }
        }

        // move to 0
        printf("%d\t%d\t%d\t%d\n",step++,cur,0,abs(cur));
        total += abs(cur);
        cur = 0;

        // reverse
        for(int i=0;i<n;i++){
            if(req[i] > head){
                printf("%d\t%d\t%d\t%d\n",step++,cur,req[i],abs(cur-req[i]));
                total += abs(cur-req[i]);
                cur = req[i];
            }
        }
    }

    printf("--------------------------------\n");
    printf("Total head movement = %d\n",total);

    return 0;
}
