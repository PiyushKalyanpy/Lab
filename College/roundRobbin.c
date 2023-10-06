#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid, at, bt, priority, ct, tat, wt, remaining_time;
};

void calculateTimes(struct Process *processes, int n, int time_quantum) {
    int currentTime = 0;
    int idle = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            struct Process *p = &processes[i];
            if (p->remaining_time > 0 && p->at <= currentTime) {
                int execute_time = (p->remaining_time < time_quantum) ? p->remaining_time : time_quantum;
                p->remaining_time -= execute_time;
                currentTime += execute_time;

                if (p->remaining_time == 0) {
                    completed++;
                    p->ct = currentTime;
                    p->tat = p->ct - p->at;
                    p->wt = p->tat - p->bt;
                }
                else {
                    idle += time_quantum;
                }
            }
        }
    }

    double atat = 0, awt = 0;
    for (int i = 0; i < n; i++) {
        atat += processes[i].tat;
        awt += processes[i].wt;
    }

    int count = n;

    printf("PID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].at,
               processes[i].bt,
               processes[i].priority,
               processes[i].ct,
               processes[i].tat,
               processes[i].wt);
    }

    printf("atat : %.2f , awt : %.2f\n", atat, awt);
    printf("Idle time is %d sec\n", idle);
    printf("AWT : %.2f\n", awt / count);
    printf("ATAT : %.2f\n", atat / count);
    printf("Throughput : %.2f\n", count / (double)processes[count - 1].ct);
    printf("Utilization : %.2f%%\n", ((processes[count - 1].ct - idle) / (double)processes[count - 1].ct) * 100.0);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    struct Process processes[n];
    printf("Enter process details (PID, AT, BT, Priority):\n");
    for (int i = 0; i < n; i++) {
        scanf(" %d %d %d", &processes[i].at, &processes[i].bt, &processes[i].priority);
        processes[i].remaining_time = processes[i].bt;
    }

    calculateTimes(processes, n, time_quantum);

    return 0;
}
