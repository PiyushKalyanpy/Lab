//Round Robin
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct process
{
    int pid, at, bt, ct, tat, wt, rt, start, remaining, visited;
} pro;

int comp(const void *a, const void *b)
{
    pro *p1 = (pro *)a;
    pro *p2 = (pro *)b;
    return p1->at > p2->at;
}

int max(int a, int b)
{
    if (a <= b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

void averageTime(pro *process, int n, float idle)
{
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\nPid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += process[i].wt;
        total_tat += process[i].tat;
        total_rt += process[i].rt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", process[i].pid, process[i].at, process[i].bt, process[i].ct, process[i].tat, process[i].wt, process[i].rt);
    }

    printf("\nAverage Waiting time %f\n", total_wt / (float)n);
    printf("Average Turn Around time %f\n", total_tat / (float)n);
    printf("Average Response time %f\n", total_rt / (float)n);
    printf("CPU utilization %f\n", ((process[n - 1].ct - idle) / (float)process[n - 1].ct) * 100);
    printf("Throughput %f\n", (float)n / (process[n - 1].ct - process[0].at));
}

int main()
{
    int n, completed = 0, curr_time = 0, first_process = 0, qn, front = -1, rear = -1;
    int queue[100];
    float idle = 0;

    printf("Enter The Number Of Processes : ");
    scanf("%d", &n);

    pro process[n];

    for (int i = 0; i < n; i++)
    {
        process[i].pid=i+1;
        printf("Enter arrival time of %d process : ",i+1);
        scanf("%d",&process[i].at);
        printf("Enter burst time of %d process : ",i+1);
        scanf("%d",&process[i].bt);
        process[i].remaining = process[i].bt;
        process[i].visited = 0;
    }

    printf("Enter time quantam:- ");
    scanf("%d", &qn);
    qsort(process, n, sizeof(pro), comp);
    front = rear = 0;
    queue[rear] = 0;
    process[0].visited = 1;

    while (completed != n)
    {
        int index = queue[front];
        front++;

        if (process[index].bt == process[index].remaining)
        {
            process[index].start = max(curr_time, process[index].at);
            curr_time = process[index].start;
            if (first_process == 1)
            {
                idle += 0;
            }
            else
            {
                idle += process[index].start - curr_time;
            }
        }

        if (process[index].remaining - qn > 0)
        {
            process[index].remaining -= qn;
            curr_time += qn;
        }

        else
        {
            curr_time += process[index].remaining;
            completed++;
            process[index].ct = curr_time;
            process[index].tat = process[index].ct - process[index].at;
            process[index].wt = process[index].tat - process[index].bt;
            process[index].rt = process[index].start - process[index].at;
            process[index].remaining = 0;
        }

        for (int i = 0; i < n; i++)
        {
            if (process[i].at <= curr_time && process[i].visited != 1)
            {
                rear++;
                queue[rear] = i;
                process[i].visited = 1;
            }
        }

        if (process[index].remaining != 0)
        {
            rear++;
            queue[rear] = index;
        }
    }

    averageTime(process, n, idle);

    return 0;
}