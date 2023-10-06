// priority scheduling algorithm

#include <stdio.h>

typedef struct process
{
    int pid, at, bt, ct, tat, wt, pt;
} ps;

float averageWaitingTime(ps *p, int s)
{
    float awt = 0.0;
    for (int i = 0; i < s; i++)
    {
        awt += (float)p[i].wt;
    }
    return awt / s;
}


void calculateTATWT(ps *p, int s, float *atat, float *awt)
{
    for (int i = 0; i < s; i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        *atat += (float)p[i].tat;
        *awt += (float)p[i].wt;
    }
}


void calculateCT(ps *p, int s)
{
    p[0].ct = p[0].bt;
    for (int i = 1; i < s; i++)
    {
        p[i].ct = p[i - 1].ct + p[i].bt;
    }
}

int main()
{
    int count;
    scanf("%d", &count);
    ps p[count];
    int idle = 0;
    float atat = 0.0, awt = 0.0, tp = 0.0, uz = 0.0;
    for (int i = 0; i < count; i++)
    {
        p[i].pid = i;

        scanf("%d", &p[i].bt);
        scanf("%d", &p[i].pt);
        p[i].at = 0;
    }


    // sort on the basis of pt
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (p[j].pt > p[j + 1].pt)
            {
                ps temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    
    // update the ct
    calculateCT(p, count);

    calculateTATWT(p, count, &atat, &awt);
    printf("PID \t BT \t PR \t CT \t TAT \t WT\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d \t", p[i].pid);
        printf("%d \t", p[i].bt);
        printf("%d \t", p[i].pt);
        printf("%d \t", p[i].ct);
        printf("%d \t", p[i].tat);
        printf("%d \n", p[i].wt);
    }
    printf("atat : %f , awt : %f\n", atat, averageWaitingTime(p, count));
    printf("Idle time is %d sec\n", idle);
    printf(" AWT : %f\n", awt / count);
    printf(" ATAT : %f\n", atat / count);
    printf(" Throughput : %f\n", count / (p[count - 1].ct));
    printf(" Utilization : %f\n", ((p[count - 1].ct - idle) / p[count - 1].ct) * 100.0);
}