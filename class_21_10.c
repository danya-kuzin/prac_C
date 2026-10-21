#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    // проверкка на аргументы
    if (argc != 3) {
        fprintf(stderr, "Something's wrong");
        return 1;
    }

    // открываем
    FILE *f_read = NULL;
    FILE *f_write = NULL;
    f_read = fopen(argv[1], "r");
    f_write = fopen(argv[2], "w");

    // проверкка на не сущ файЛ
    if (f_read == NULL) {
        fprintf(stderr, "Something's wrong");
        return 1;
    }

    // читаем почарово
    char cur_word_lst_sym = ' ';
    int count_str_a = 0;
    int count_words_a = 0;
    int cur_ch;
    char flag_end_word = 0;
    char flag_cur_str_a = 0;

    while (1) {
        cur_ch = fgetc(f_read);

        if (cur_ch == ' ' || cur_ch == '\n' || cur_ch == EOF) {

            // слово закончилось с буковкой "а"
            if (cur_word_lst_sym == 'a' && flag_end_word) {
                count_words_a++;
                flag_cur_str_a = 1;
            }

            // закончиллась строчка со словечком с буковкой "а"
            if ((cur_ch == '\n' || cur_ch == EOF) && flag_cur_str_a) {
                count_str_a++;
                flag_cur_str_a = 0;
            }

            flag_end_word = 0; // пока идут пробелы

            if (cur_ch == EOF) break;
        } else {
            flag_end_word = 1; // пока идут букавы
            cur_word_lst_sym = cur_ch;
        }
    }

    //printf("\ncount_words_a: %d", count_words_a);
    //printf("\ncount_str_a: %d", count_str_a);
    fprintf(f_write, "%d %d", count_words_a, count_str_a);

    // закрываем
    fclose(f_read);
    fclose(f_write);
    f_read = NULL;
    f_write = NULL;
    return 0;
}