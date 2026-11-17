#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define NUM_PARAMS_BEFORE_LETTERS 2
#define MAX_N 1000

void replace_letters(int fd_file, char** argv, int id) {
    int k_let_in_cur_word = 0;
    char* buf = "abcdef\n";
    write(fd_file, buf, strlen(buf));

    char letter_old = argv[NUM_PARAMS_BEFORE_LETTERS + 2 * id - 1][0];
    char letter_new = argv[NUM_PARAMS_BEFORE_LETTERS + 2 * id][0];
    char* name_member;
    if (id == 0) 
        name_member = "DADDY";
    else if (id > 0) { 
        name_member = "SON"; 
        char end[MAX_N];
        snprintf(end, sizeof(end), "%d", id);
        strcat(name_member, end); // добавка номера к SOn
    }

    is_separator = (cur_symb == ' ' || cur_symb == ',' || cur_symb == '.' || cur_symb == '\n');
    if (is_separator && k_let_in_cur_word >= 9) {
        // изменяем слово
    }
    return;
}


int main(int argc, char** argv) {
    char *end;
    int num_family_mems = strtol(argv[2], &end, 10);
    if (*end != '\0') return 1;

    int fd_file = open(argv[1], O_RDWR, 0644);
    if (fd_file < 0) { fprintf(stderr, "Can't open file"); return 1; }

    // отец + N-1 сыныа
    for (int id = 1; id < num_family_mems; id++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("son%d\n", id);
            fflush(stdout);
            replace_letters(fd_file, argv, id);
            close(fd_file);
            return 0;
        }
    }

    id = 0;
    replace_letters(fd_file, argv, id);
    printf("father\n");

    while (wait(NULL) > 0) {}; // отец ждет смерти всех сыновей(
    close(fd_file);
    return 0;
}