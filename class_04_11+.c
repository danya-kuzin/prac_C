#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 2

int main(int argc, char** argv) {
    if (argc < 3) return 1;

    int fd1 = open(argv[1], O_RDWR);
    if (fd1 == -1) return 2;

    int fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT);
    if (fd2 == -1) { close(fd1); return 3; }

    struct stat st;
    if (stat(argv[1], &st) == -1) {close(fd1); close(fd2); return 4;} 
    if (st.st_size % sizeof(int) != 0) {close(fd1); close(fd2); return 0;} 

    int buf[BUF_SIZE];
    ssize_t size; // заменил size_t, т.к. он беззнаковый и -size_t дает гигантское полож. число
    int tmp_elem;
    off_t offset;
    int num_of_iterations = ((st.st_size) / sizeof(int)) * ((st.st_size) / sizeof(int));
    for (int i = 0; i < num_of_iterations; i++) {
        while ((size = read(fd1, buf, BUF_SIZE * sizeof(int))) > 0) {
            if (size == 2 * sizeof(int) && buf[0] > buf[1]) {
                tmp_elem = buf[1];
                buf[1] = buf[0];
                buf[0] = tmp_elem;
            }

            lseek(fd1, -size, SEEK_CUR);
            write(fd1, buf, size);

            if (size == 1 * sizeof(int)) break;
            // сдвгаем чтобы сортировать каждую пару а не только непересек-ия
            // тут превожу к off_t по той же причине, что и я заменил size_t на ssize_t
            else lseek(fd1, -1 * (off_t)sizeof(int), SEEK_CUR);
        }

        offset = 0;
        lseek(fd1, offset, SEEK_SET);
    }

    while ((size = read(fd1, buf, BUF_SIZE * sizeof(int))) > 0)
        write(fd2, buf, size);


    close(fd1);
    close(fd2);
    return 0;
}