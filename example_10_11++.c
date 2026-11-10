#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char a;
    int fd;
    fd = open("b.txt", O_RDONLY);
    if(fork()) {
        int fd2 = open("b.txt", O_RDONLY);
        lseek(fd, 2, SEEK_CUR);
        wait(NULL);
        read(fd2, &c, 1); write(1, &c, 1);
        read(fd, &c, 1); write(1, &c, 1);
    }
    else {
        read(fd, &c, 1); write(1, &c, 1);
    }

    return 0;
}