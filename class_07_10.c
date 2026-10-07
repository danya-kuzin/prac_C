#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// функция удаления из строки нецензурного слова
void remove_part(char *start_del, size_t count)
{
    // start_del - указатель на начало удаляемого слова
    // end_del - указатель на конец удаляемого слова (на пробел после него)
    char *end_del = start_del + count;
    do {
        // копируем посимвольно с расстоянием в count (по факту сдвигаем)
        *start_del = *end_del;
        end_del++;
        start_del++;
    } while (*(end_del - 1) != '\0');
}

// функция сравнения двух слов
int comp_words(char* bad_word, char* real_word) {

    // все слово из маленьких букв
    if (strcmp(bad_word, real_word) == 0)
        return 0;

    // проверка на одинаковые длины, чтобы правльно посчитать count_big
    if (strlen(bad_word) != strlen(real_word))
        return 1;

    // считаем количество больших букв
    size_t count_big = 0;
    for (int i = 0; real_word[i] != '\0'; i++) {
        if (real_word[i] <= 'Z' && real_word[i] >= 'A')
            count_big++;
    }

    // большая только первая буква или все слово из больших
    if (real_word[0] <= 'Z' && real_word[0] >= 'A' &&
        (count_big == 1 || count_big == strlen(real_word))) {
        
        // проверяем совпадение всех букв
        for (int i = 0; real_word[i] != '\0'; i++) {
            if (tolower(real_word[i]) != tolower(bad_word[i]))
                return 1;
        }

        return 0;
    }

    return 1;
}

// функция проверки слова на цензурность
int censorship_word(char** argv, int argc, char *word, size_t len_word) {

    // слово без мусора после последнего значащаго символа
    char *real_word = strndup(word, len_word);

    // перебираем нецензурные слова и сравниваем
    for (int i = 1; i < argc; i++) {
        if (comp_words(argv[i], real_word) == 0) {
            free(real_word);
            return 1;
        }
    }

    free(real_word);
    return 0;
}

int main(int argc, char** argv) {

    // вводим строку 
    char *buf = NULL;
    size_t size = 0;
    ssize_t read_size;

    while ((read_size = getline(&buf, &size, stdin)) != -1) {

        // выделяем память под слово
        char *word = NULL;
        int size_word = 1000;
        word = (char *)malloc(size_word * sizeof(char));

        // проверка на возможность выделить память
        if (!word) {
            printf("Cant allocate memory\n");
            return 1;
        }

        // разбираем строку по словам
        size_t len_word = 0;
        ssize_t i = 0;
        while (i <= read_size) {

            // кончилось текущее слово
            if (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\0') {

                // проверка на нецензурное слово
                if (censorship_word(argv, argc, word, len_word)) {

                    // buf + i - len_word это начало удаляемого слова
                    // len_word + 1 это длина удаляемого слова + пробел
                    if (buf[i] == ' ') {
                        remove_part(buf + i - len_word, len_word + 1);
                        read_size -= len_word + 1;
                    } else {
                        remove_part(buf + i - len_word, len_word);
                        read_size -= len_word;
                    }

                    i -= len_word;
                    len_word = 0;
                    continue;
                }

                len_word = 0;
                i++;
                continue;
            }

            // накапливаем слово
            word[len_word] = buf[i];
            len_word++;
            i++;
        }

        // выводим строку
        printf("%s", buf);

        free(word);
    }

    free(buf);
    return 0;
}