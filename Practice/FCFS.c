// program to implement FCFS scheduling algorithm

#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt;
};

int main(){
    int p;
    printf("Enter the number of processes: ");
    scanf("%d", &p);

    struct Process processes[p];

    printf("Enter process details (PID, AT, BT):\n");
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &processes[i].pid, &processes[i].at, &processes[i].bt);
    }

    int currentTime = 0;
    int idle = 0;

    for (int i = 0; i < p; i++) {
        if (currentTime < processes[i].at) {
            idle += processes[i].at - currentTime;
            currentTime = processes[i].at;
        }

        processes[i].ct = currentTime + processes[i].bt;
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;

        currentTime = processes[i].ct;
    }

    double atat = 0, awt = 0;
    for (int i = 0; i < p; i++) {
        atat += processes[i].tat;
        awt += processes[i].wt;
    }

    int count = p;

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < p; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].at,
               processes[i].bt,
               processes[i].ct,
               processes[i].tat,
               processes[i].wt);
    }

    printf("Idle time is %d sec\n", idle);
    printf("AWT : %f\n", awt / count);
    printf("ATAT : %f\n", atat / count);
    printf("Throughput : %f\n", count / (double)processes[count - 1].ct);
    printf("Utilization : %f%%\n", ((processes[count - 1].ct - idle) / (double)processes[count - 1].ct) * 100.0);

}