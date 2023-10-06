// C program to implement Zombie Orphan process.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int pid = fork();
    if(pid == 0){
        printf("Child process\n");
        printf("Child process id: %d\n", getpid());
        printf("Parent process id: %d\n", getppid());
        sleep(10);
        printf("Child process\n");
        printf("Child process id: %d\n", getpid());
        printf("Parent process id: %d\n", getppid());
    }
    else{
        printf("Parent process\n");
        printf("Parent process id: %d\n", getpid());
        printf("Child process id: %d\n", pid);
        sleep(20);
        printf("Parent process\n");
        printf("Parent process id: %d\n", getpid());
        printf("Child process id: %d\n", pid);
    }
    return 0;   
}