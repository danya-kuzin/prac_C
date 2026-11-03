// скопировать файл

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#define BUF_SIZE 128

int main (int argc, cha **argv) {
    if (argc < 3) {
        fprintf(stderr, "Use %s <sourse file> <dst file>\n", argv[0]);
        return 1;
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 2;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {close(fd1);retutn 3;} // заполняем поля структуры и проверяем

    // копируем права с помощью st_mode
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (fd2 == -1) {
        perror("open2");
        close(fd1);
        return 2;
    }

    char buf[BUF_SIZE];
    size_t size;
    while ((size = read(fd1, buf, BUF_SIZE)) > 0) {
        write(fd2, buf, size);
    }

    close(fd1);
    close(fd2);
    return 0;
}