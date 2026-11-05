#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define N 7
#define MAX_LEN 50

int main(int argc, char** argv) {

    if (argc != 3) {
        fprintf(stderr, "Error");
        return 1;
    }

    int fd_orig = open(argv[1], O_RDONLY);
    if (fd_orig == -1) {
        fprintf(stderr, "Error");
        return 2;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {close(fd_orig); return 3;} 

    int fd_copy = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (fd_copy == -1) {
        close(fd_orig);
        fprintf(stderr, "Error");
        return 4;
    }

    char buf_read[N];
    char buf_write[N];
    ssize_t size;
    int write_buf_i = 0;
    int k_symb_in_str = 0;
    while (1) {
        size = read(fd_orig, buf_read, N);
        if (size <= 0) break;

        for (ssize_t i = 0; i < size; i++) {
            k_symb_in_str++;

            // пропускаем символы до \n
            if (k_symb_in_str > MAX_LEN && buf_read[i] != '\n') {
                continue;
            }

            buf_write[write_buf_i] = buf_read[i];
            write_buf_i++;

            if (buf_read[i] == '\n') {
                k_symb_in_str = 0;
            }

            if (write_buf_i == N) {
                write(fd_copy, buf_write, N);
                write_buf_i = 0;
            }
        }
    }

    // все что осталось
    if (write_buf_i > 0) {
        write(fd_copy, buf_write, write_buf_i);
    }

    close(fd_orig);
    close(fd_copy);
    return 0;
}
