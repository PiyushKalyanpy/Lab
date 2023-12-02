#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int pid, at, bt, ct, tat, wt, st, rt;
};

int main() {
    int n, tq;
    scanf("%d %d", &n, &tq);
    struct process p[n];

    // enter at and bt
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        p[i].rt = p[i].bt;
        p[i].st = 0;
    }

    // scheduling
    int completed = 0, ct = 0;
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                if (p[i].rt > tq) {
                    p[i].rt -= tq;
                    ct += tq;
                } else {
                    ct += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = ct;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }
    }

    // printing the table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt);
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    // printing the average tat and average wt
    printf("Average TAT: %f\n", avg_tat / n);
    printf("Average WT: %f\n", avg_wt / n);

    return 0;
}
