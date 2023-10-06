// C program in which parent process compute sum of odd numbers and child process computes sum of even numbers stored in array using fork().

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int sumOdd = 0, sumEven = 0;
    int pid = fork();
    if(pid == 0){
        for(int i=0; i<10; i++){
            if(arr[i]%2 == 0){
                sumEven += arr[i];
            }
        }
        printf("Sum of even numbers: %d\n", sumEven);
    }
    else{
        for(int i=0; i<10; i++){
            if(arr[i]%2 != 0){
                sumOdd += arr[i];
            }
        }
        printf("Sum of odd numbers: %d\n", sumOdd);
    }
    return 0;
}