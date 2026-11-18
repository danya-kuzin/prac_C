#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char** argv) {

    // кол-во ключей и возможно > файлик
    int k_keys_in_cur_conv = 0;
    int cur_num_pr = 0;
    int argv_num_keys[3];
    char flag_has_filename = 0;
    char *filename;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0 || i == argc - 1 || strcmp(argv[i], ">") == 0) {
            if (i == argc - 1) k_keys_in_cur_conv++;
            //printf("%d ", k_keys_in_cur_conv);
            argv_num_keys[cur_num_pr] = k_keys_in_cur_conv;
            cur_num_pr++;
            k_keys_in_cur_conv = 0;
            if (strcmp(argv[i], ">") == 0) { flag_has_filename = 1; break; }
        }
        else
            k_keys_in_cur_conv++;
    }

    int fd_file;
    if (flag_has_filename) {
        filename = argv[argc - 1];
        fd_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    //printf("\n\n%s\n\n", filename);

    // массивы аргум дъя exec
    char** argv1 = (char**)malloc((argv_num_keys[0] + 1) * sizeof(char *));
    if (argv1 == NULL) { printf("Error"); return 1; }
    char** argv2 = (char**)malloc((argv_num_keys[1] + 1) * sizeof(char *));
    if (argv2 == NULL) { printf("Error"); return 1; }
    char** argv3 = (char**)malloc((argv_num_keys[2] + 1) * sizeof(char *));
    if (argv3 == NULL) { printf("Error"); return 1; }

    int pos = 1;
    for (int j = 0; j < argv_num_keys[0]; j++) { argv1[j] = argv[pos]; pos++; }
    argv1[argv_num_keys[0]] = NULL;

    pos++; // пропуск |
    for (int j = 0; j < argv_num_keys[1]; j++) { argv2[j] = argv[pos]; pos++; }
    argv2[argv_num_keys[1]] = NULL;

    pos++;
    for (int j = 0; j < argv_num_keys[2]; j++) { argv3[j] = argv[pos]; pos++; }
    argv3[argv_num_keys[2]] = NULL;


    int fd_1_2[2];
    pipe(fd_1_2);

    int fd_2_3[2];
    pipe(fd_2_3);

    //первого сына связ с записью в пайп 1_2
    if (fork() == 0) {
        dup2(fd_1_2[1], 1);
        close(fd_1_2[0]); close(fd_1_2[1]);
        close(fd_2_3[0]); close(fd_2_3[1]);
        execvp(argv1[0], argv1);
        perror("execvp");
        return 1;
    }

    //второго сына связ с чтением пайпа 1_2 и запиью в пайп 2_3
    if (fork() == 0) {
        dup2(fd_1_2[0], 0);
        close(fd_1_2[0]); close(fd_1_2[1]);

        dup2(fd_2_3[1], 1);
        close(fd_2_3[0]); close(fd_2_3[1]);

        execvp(argv2[0], argv2);
        perror("execvp");
        return 1;
    }

    //третьего сына связ с чтением пайпа 2_3 и (возможно) запиью в фвйлик
    if (fork() == 0) {
        dup2(fd_2_3[0], 0);
        close(fd_1_2[0]); close(fd_1_2[1]);
        close(fd_2_3[0]); close(fd_2_3[1]);
        if (flag_has_filename) dup2(fd_file, 1);
        execvp(argv3[0], argv3);
        perror("execvp");
        return 1;
    }

    close(fd_1_2[0]);
    close(fd_1_2[1]);
    close(fd_2_3[0]);
    close(fd_2_3[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    if (flag_has_filename) close(fd_file);
    return 0;
}