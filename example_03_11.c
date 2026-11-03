#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(){
/*    int fd  = open("file_1.txt", O_RDONLY);
    if (fd == -1) {
        perror("Open");
        if (errno == ENOENT)
            printf("errno = %d\n", errno);
    }
    printf("fd = %d", fd);
*/

    int fd = open("output.txt", O_CREAT | O_WRONLY | O_EXCL, 0640);
    printf("fd = %d", fd);
    return 0;
}