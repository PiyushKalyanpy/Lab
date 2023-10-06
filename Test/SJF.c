#include <stdio.h>

struct Process
{
    int pid, at, bt, ct, tat, wt;
};

int main()
{
    int n;
    printf("Enter the no of process : ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
    }

    // Sort processes based on burst time (SJF)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].bt > p[j + 1].bt)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int ct = 0, idle = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].ct = ct + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        ct = p[i].ct;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("IDLE : %d", idle);
    printf("Throughput : %f", n / (float)(p[n - 1].ct));
    printf("Utilization : %f", ((float)(p[n - 1].ct - idle) / p[n - 1].ct) * 100);
}
