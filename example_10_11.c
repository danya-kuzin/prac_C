#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    //fork();
    //printf("My PID id %d PPID = %d\n", getpid(), getppid());

    pid_t pid = fork();
    if (pid > 0) {
        printf("I'm father my PID id %d PPID = %d\n", getpid(), getppid());
        wait(NULL);
    }
    else {
        sleep(1);
        printf("I'm son my PID id %d PPID = %d\n", getpid(), getppid());
    }
}