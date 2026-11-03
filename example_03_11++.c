#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Use: %s <binary file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        return 2;
    }

    off_t min_p;
    int min, tmp;

    if (read(fd, &min, sizeof(int)) == sizeof(int)) {
        min_p = 0;
    }
    else { close(fd); return 2; }
    while (read(fd, &tmp, sizeof(int)) == sizeof(int)) {
        if (tmp < min) {
            min = tmp;
            min_p = lseek(fd, 0, SEEK_CUR) - sizeof(int); // т.к. указатель съехал на след число
        }
    }

    min = -min;
    lseek(fd, min_p, SEEK_SET);
    write(fd, &min, );
    return 0;
}