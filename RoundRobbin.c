#include <stdio.h>

int main(){
    int i, nop, ct=0, time_quantum, counter;
    printf("Enter the number of processes: ");
    scanf("%d", &nop);

    int at[nop], bt[nop], rt[nop], wt[nop], tat[nop], flag[nop];
    for(i=0; i<nop; i++){
        printf("Enter the arrival time and burst time of process %d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
        flag[i] = 0;
    }
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    while(1){
        for(i=0, counter=0; i<nop; i++){
            if(rt[i] == 0){
                counter++;
                continue;
            }
            if(rt[i] > time_quantum){
                ct += time_quantum;
                rt[i] -= time_quantum;
            }
            else{
                ct += rt[i];
                tat[i] = ct - at[i];
                wt[i] = tat[i] - bt[i];
                rt[i] = 0;
            }
        }
        if(counter == nop){
            break;
        }
    }

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0; i<nop; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct, tat[i], wt[i]);
    }

    return 0;
    
}