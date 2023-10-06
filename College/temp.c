#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid, at, bt, priority, ct, tat, wt, remaining_time;
};

void calculateTimes(struct Process *processes, int n, int time_quantum) {
    int currentTime = 0;
    int idle = 0;
    int completed = 0;

    while (completed < n) { // Continue until all processes are completed
        for (int i = 0; i < n; i++) { // Iterate through all processes
            struct Process *p = &processes[i];
            if (p->remaining_time > 0 && p->at <= currentTime) { // Check if the process is ready and not yet completed
                int execute_time = (p->remaining_time < time_quantum) ? p->remaining_time : time_quantum; // Determine execution time for this round
                p->remaining_time -= execute_time; // Reduce remaining time for the process
                currentTime += execute_time; // Update current time

                if (p->remaining_time == 0) { // If the process is completed
                    completed++;
                    p->ct = currentTime; // Set completion time
                    p->tat = p->ct - p->at; // Calculate turnaround time
                    p->wt = p->tat - p->bt; // Calculate waiting time
                } else {
                    idle += time_quantum; // If the process still needs more time, accumulate idle time
                }
            }
        }
    }

    double atat = 0, awt = 0;
    for (int i = 0; i < n; i++) {
        atat += processes[i].tat; // Calculate total turnaround time
        awt += processes[i].wt; // Calculate total waiting time
    }

    int count = n;

    printf("PID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) { // Display process details
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].at,
               processes[i].bt,
               processes[i].priority,
               processes[i].ct,
               processes[i].tat,
               processes[i].wt);
    }

    printf("atat : %.2f , awt : %.2f\n", atat, awt); // Display average turnaround time and average waiting time
    printf("Idle time is %d sec\n", idle); // Display total idle time
    printf("AWT : %.2f\n", awt / count); // Display average waiting time
    printf("ATAT : %.2f\n", atat / count); // Display average turnaround time
    printf("Throughput : %.2f\n", count / (double)processes[count - 1].ct); // Display throughput
    printf("Utilization : %.2f%%\n", ((processes[count - 1].ct - idle) / (double)processes[count - 1].ct) * 100.0); // Display CPU utilization
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
