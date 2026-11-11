#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int N;
    scanf("%d", &N);

    // спец канал, который говорит основателю рода что все родились
    int ready[2];
    pipe(ready);

    int num = 0; // номер поколления
    int from_papa = -1;
    int to_son = -1;
    pid_t pid;

    for (int i = 0; i < N; i++) {
        int fd[2];
        pipe(fd);

        pid = fork();

        if (pid > 0) {
            close(fd[0]);
            to_son = fd[1];
            break;
        }

        // Новый потомок оставляет канал только от своего родителя.
        close(fd[1]);
        if (from_papa != -1) close(from_papa);

        from_papa = fd[0];
        num = i + 1;
    }

    char token = 1;

    // Последний потомок уже создан — можно сообщить об этом.
    if (num == N) write(ready[1], &token, 1);
    close(ready[1]);

    // Основатель ждёт готовности, потомки — разрешения родителя.
    int wait_fd;
    if (num == 0) {
        wait_fd = ready[0];
    } else {
        close(ready[0]);
        wait_fd = from_papa;
    }

    read(wait_fd, &token, 1);
    close(wait_fd);

    if (num > 0) {
        for (int j = 2; j < num; j++) printf("great-");
        if (num >= 2) printf("grand");
        printf("son\n");
        fflush(stdout);
        fprintf(stderr, "PID = %d PPID = %d\n", (int)getpid(), (int)getppid());
    }

    if (to_son != -1) {
        // Разрешаем сыну печатать только после своего вывода.
        write(to_son, &token, 1);
        close(to_son);

        // Завершаемся только после своего сына.
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}