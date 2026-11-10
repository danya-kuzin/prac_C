#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if (pid == 0) {
        int num = 5;
        close(fd[0]);
        printf("Im son num = %d \n", num);
        //write(fd[1], &num, sizeof(int));
        close(fd[1]);
    }
    else {
        int num2;
        close(fd[1]);
        read(fd[0], &num2, sizeof(int));
        printf("Im father num = %d \n", num2);
        close(fd[0]);
    }

    return 0;
}