#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        int fd = open("out_ls", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) { perror("open"); return 1; }
        dup2(fd, 1);
        char *argv[] = {"ls", "-l", "-a", NULL};
        execv("/bin/ls", argv);
        perror("execlp");
        return 1;
    }
    int status;
    kill(pid, SIGTERM);
    wait(&status);
    if (WIFEXITED(status)) {
        printf("Child process exited normally with code %d\n", WEXITSTATUS(status));
    }

    if (WIFEXITED(status) && !(WIFEXITED(status) == 0)) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    if (fork() == 0) {
        execlp("ps", "ps", NULL);
        return 1;
    }
    return 0;
}
