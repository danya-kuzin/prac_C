// реализация конвейера

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int fd[2];
    pipe(fd);
    //первого сына копируем в пишущий канал
    if (fork() == 0) {
        dup2(fd[1], 1);
        close(fd[0]); close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execl");
        return 1;
    }
    //второго сына копируем в читающий канал
    if (fork() == 0) {
        dup2(fd[0], 0);
        close(fd[0]); close(fd[1]);
        execlp("wc", "wc", NULL);
        perror("execlp");
        return 1;
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}