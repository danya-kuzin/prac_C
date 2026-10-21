#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    // проверкка на аргументы
    if (argc != 3) return 1;

    // открываем
    FILE *f_read = NULL;
    FILE *f_write = NULL;
    f_read = fopen(argv[1], "r");
    f_write = fopen(argv[2], "w");

    // проверкка на не сущ файЛ
    if (f_read == NULL) return 1;

    // читаем почарово
    int count_str = 0;
    int count_words = 0;
    int count_symb = 0;
    int cur_ch;
    char flag_end_word = 0;

    while ((cur_ch = fgetc(f_read)) != EOF) {
        count_symb++;

        if (cur_ch == ' ' || cur_ch == '\n') {

            // слово закончилосm
            if (flag_end_word)
                count_words++;

            // закончиллась строчка
            if (cur_ch == '\n')
                count_str++;

            flag_end_word = 0; // пока идут пробелы

        } else {
            flag_end_word = 1; // пока идут букавы
        }
    }

    //printf("\ncount_words_a: %d", count_words_a);
    //printf("\ncount_str_a: %d", count_str_a);
    fprintf(f_write, "%d %d %d", count_str, count_words, count_symb);

    // закрываем
    fclose(f_read);
    fclose(f_write);
    f_read = NULL;
    f_write = NULL;
    return 0;
}