#include <stdio.h>

struct Process
{
    int pid, at, bt, ct, tat, rt, wt;
};

int main()
{
    int n, remain = 0, shortest = -1, ttat = 0, twt = 0;
    printf("Enter the number of process : ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter the Arrival and burst time : \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i;
        p[i].rt = p[i].bt;
    }
    
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int time = 0; remain <= n; time++)
    {

        // find shortest remaining
        for (int i = 0; i < n; i++)
        {
            if (p[i].at < time && p[i].rt != 0)
            {
               
                    shortest = i;
                
            }
        }

        // decreament remaining time
        p[shortest].rt--;

        // process this process
        if (p[shortest].rt <= 0)
        {
            remain++;
            int comptime = time + 1;
            p[shortest].ct = comptime;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            ttat += p[shortest].tat;
            twt += p[shortest].wt;
            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[shortest].pid, p[shortest].at, p[shortest].bt, p[shortest].ct, p[shortest].tat, p[shortest].wt);
        }


    }

        printf("Average wait time  : %f\n", twt / (float)n);
        printf("Average turn around time  : %f\n", ttat / (float)n);
}