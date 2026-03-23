#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n){
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j]>a[j+1]){
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
}

int main(){
    int n, head, dir;
    int total = 0;

    printf("Enter number of requests: ");
    scanf("%d",&n);

    int req[n];

    printf("Enter the requests:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&req[i]);

    printf("Enter initial head position: ");
    scanf("%d",&head);

    printf("Enter direction (1 = RIGHT, 0 = LEFT): ");
    scanf("%d",&dir);

    sort(req,n);

    printf("\n-------------------------------------------\n");
    printf("Step\tFrom\tTo\tMovement\n");
    printf("-------------------------------------------\n");

    int cur = head, step = 1;

    if(dir==1){   // RIGHT FIRST

        for(int i=0;i<n;i++){
            if(req[i] >= head){
                int move = abs(cur - req[i]);
                printf("%d\t%d\t%d\t%d\n", step, cur, req[i], move);
                total += move;
                cur = req[i];
                step++;
            }
        }

        for(int i=n-1;i>=0;i--){
            if(req[i] < head){
                int move = abs(cur - req[i]);
                printf("%d\t%d\t%d\t%d\n", step, cur, req[i], move);
                total += move;
                cur = req[i];
                step++;
            }
        }

    } else {   // LEFT FIRST

        for(int i=n-1;i>=0;i--){
            if(req[i] <= head){
                int move = abs(cur - req[i]);
                printf("%d\t%d\t%d\t%d\n", step, cur, req[i], move);
                total += move;
                cur = req[i];
                step++;
            }
        }

        for(int i=0;i<n;i++){
            if(req[i] > head){
                int move = abs(cur - req[i]);
                printf("%d\t%d\t%d\t%d\n", step, cur, req[i], move);
                total += move;
                cur = req[i];
                step++;
            }
        }
    }

    printf("-------------------------------------------\n");
    printf("Total Head Movement = %d\n", total);
    printf("-------------------------------------------\n");

    return 0;
}
