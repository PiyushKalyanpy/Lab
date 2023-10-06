#include <stdio.h>

struct Process {
    int pid, bt, ct, tat, wt;
};

// Function to perform SJF scheduling
void SJF(struct Process p[], int n) {
    int ct = 0;

    for (int i = 0; i < n; i++) {
        // Find the process with the shortest burst time
        int shortest = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].bt < p[shortest].bt) {
                shortest = j;
            }
        }

        // Swap the processes
        struct Process temp = p[i];
        p[i] = p[shortest];
        p[shortest] = temp;

        // Update completion time, turnaround time, and waiting time
        p[i].ct = ct + p[i].bt;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;

        // Update current time
        ct = p[i].ct;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].pid = i + 1;
    }

    // Call the SJF scheduling function
    SJF(p, n);

    printf("PID\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}
