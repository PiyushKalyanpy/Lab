    #include <stdio.h>
    #include <stdlib.h>

    struct Process {
        int pid, at, bt, ct, tat, wt;
    };

    void calculateTimes(struct Process *processes, int n) {
        int currentTime = 0;
        int idle = 0;

        for (int i = 0; i < n; i++) {
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
        for (int i = 0; i < n; i++) {
            atat += processes[i].tat;
            awt += processes[i].wt;
        }

        int count = n;

        printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
        for (int i = 0; i < n; i++) {
            printf("%d\t%d\t%d\t%d\t%d\t%d\n",
                processes[i].pid,
                processes[i].at,
                processes[i].bt,
                processes[i].ct,
                processes[i].tat,
                processes[i].wt);
        }

        printf("atat : %f , awt : %f\n", atat, awt);
        printf("Idle time is %d sec\n", idle);
        printf("AWT : %f\n", awt / count);
        printf("ATAT : %f\n", atat / count);
        printf("Throughput : %f\n", count / (double)processes[count - 1].ct);
        printf("Utilization : %f%%\n", ((processes[count - 1].ct - idle) / (double)processes[count - 1].ct) * 100.0);
    }

    int main() {
        int n;
        printf("Enter the number of processes: ");
        scanf("%d", &n);
        
        struct Process processes[n];
        printf("Enter process details (PID, AT, BT):\n");
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &processes[i].pid, &processes[i].at, &processes[i].bt);
        }

        // sort on the basis of burst time
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (processes[j].bt > processes[j + 1].bt)
                {
                    struct Process temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }

        calculateTimes(processes, n);
        
        return 0;
    }
