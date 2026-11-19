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
    char* str_replase_end_word[3];
    str_replase_end_word[0] = letter_new;
    str_replase_end_word[1] = '*';
    str_replase_end_word[2] = '\0';

    char* name_member;
    if (id == 0) 
        name_member = "DADDY";
    else if (id > 0) { 
        name_member = "SON"; 
        char end[MAX_N];
        snprintf(end, sizeof(end), "%d", id);
        strcat(name_member, end); // добавка номера к SOn
    }

    int first_let_in_word_offset = 0;
    int last_let_in_word_offset = 0;
    char* cur_symb_str[1];
    char cur_symb;
    char pred_cur_symb;

    while () {
        read(fd_file, cur_symb_str, 1);
        cur_symb = cur_symb_str[0];

        is_separator = (cur_symb == ' ' || cur_symb == ',' || cur_symb == '.' || cur_symb == '\n' || cur_symb == EOF);
        if (is_separator && k_let_in_cur_word >= 9 && letter_old == pred_cur_symb) {
            lseek(fd_file, last_let_in_word_offset - 2, SEEK_SET);
            write(fd_file, str_replase_end_word, strlen(str_replase_end_word));
        }

        if (is_separator) {
            k_let_in_cur_word = 0;
            first_let_in_word_offset = last_let_in_word_offset + 2;
        }

        last_let_in_word_offset++;
        pred_cur_symb = cur_symb;
        if (cur_symb == EOF) break;
    }

    return;
}


int main(int argc, char** argv) {
    char *end;
    int num_family_mems = strtol(argv[2], &end, 10);
    if (*end != '\0') return 1;

    // отец + N-1 сыныа
    for (int id = 1; id < num_family_mems; id++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("son%d\n", id);
            fflush(stdout);
            
            // чтоб указатели lseek были у всех сыновей и отца разны
            int fd_file = open(argv[1], O_RDWR, 0644);
            if (fd_file < 0) { fprintf(stderr, "Can't open file"); return 1; }

            replace_letters(fd_file, argv, id);
            close(fd_file);
            return 0;
        }
    }

    id = 0;
    int fd_file = open(argv[1], O_RDWR, 0644);
    if (fd_file < 0) { fprintf(stderr, "Can't open file"); return 1; }
    replace_letters(fd_file, argv, id);
    printf("father\n");

    while (wait(NULL) > 0) {}; // отец ждет смерти всех сыновей(
    close(fd_file);
    return 0;
}