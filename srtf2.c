#include <stdio.h>

struct Process
{
  int pid, at, bt, ct, tat, rt, wt;
};

int main()
{
  int n, remain = 0, shortest = 0, idle_time = 0, ttat = 0, twt = 0;
  float utilization, throughput;

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

  for (int time = 0; remain <= n; time++)
  {
    // find shortest remaining
    for (int i = 0; i < n; i++)
    {
      if (p[i].at <= time && p[i].rt != 0)
      {
        if (shortest == -1 || p[i].rt < p[shortest].rt)
        {
          shortest = i;
        }
      }
    }

    // if there is no process to schedule, increment idle time
    if (shortest == -1)
    {
      idle_time++;
    }
    else
    {
      // decreament remaining time of shortest process
      p[shortest].rt--;

      // process this process
      if (p[shortest].rt <= 0)
      {
        remain++;
        // p[shortest].ct = time + 1;
        // p[shortest].tat = p[shortest].ct - p[shortest].at;
        // p[shortest].wt = p[shortest].tat - p[shortest].bt;
        // ttat += p[shortest].tat;
        // twt += p[shortest].wt;

        // update shortest variable
      }
    }
  }

  // print results
  printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
  }

  printf("Average TAT : %f\n", ttat / (float)n);
  printf("Average WT : %f\n", twt / (float)n);
  printf("Utilization : %f\n", utilization);
  printf("Throughput : %f\n", throughput);

  return 0;
}
