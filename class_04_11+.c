#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 16

int main(int argc, char** argv) {
    if (argc < 3) return 1;

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) return 2;

    int fd2 = open(argv[2], O_WRONLY);
    if (fd2 == -1) { close(fd1); return 3; }

    char buf[BUF_SIZE];
    size_t size;
    while ((size = read(fd1, buf, BUF_SIZE)) > 0)
        write(fd2, buf, BUF_SIZE);

    close(fd1);
    close(fd2);
    return 0;
}