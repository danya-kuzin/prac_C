#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_pairs(char *str) {
    size_t len_str = strlen(str);
    char* cur_word;
    int i = 0;
    int i_pred = 0;
    int k_words_size = 10;
    int k_words = 0;

    char** mas_of_str = NULL;
    mas_of_str = (char**)malloc(k_words_size * sizeof(char*));

    while (str[i] != '\0') {
        cur_word = NULL;
        cur_word = (char*)malloc(len_str * sizeof(char));

        for (;str[i] != ';' && str[i] != '\0'; i++) {
            cur_word[i - i_pred] = str[i];
        }

        cur_word[i - i_pred] = '\0';

        // выделить еще памяти если нехватает
        if (k_words == k_words_size) {
            char** buf = (char**)realloc(mas_of_str, k_words_size * 2 * sizeof(char*));

            if (!buf) {
                printf("Cant allocate memory");
                free(mas_of_str);
                return;
            } else {
                mas_of_str = buf;
                k_words_size *= 2;
            }
        }

        mas_of_str[k_words] = cur_word;
        k_words++;
        if (str[i] == ';') i++; // в случае когда str[i] == '\0' плюсовать 1 нельзя
        i_pred = i; 
    }

    //for (int j = 0; j < k_words; j++)
    //    printf("%s\n", mas_of_str[j]);

    // переставляем
    char* cur_support_word = NULL;
    cur_support_word = (char*)malloc(len_str * sizeof(char));
    for (int j = 0; j < k_words; j += 2) {
        strcpy(cur_support_word, mas_of_str[j + 1]);
        strcpy(mas_of_str[j + 1], mas_of_str[j]);
        strcpy(mas_of_str[j], cur_support_word);
    }

    //printf("\n\n\n");
    //for (int j = 0; j < k_words; j++)
    //    printf("%s\n", mas_of_str[j]);

    // переворачиваем
    for (int j = 1; j < k_words; j += 2) {
        size_t len_word = strlen(mas_of_str[j]);
        char* new_word = NULL;
        new_word = (char*)malloc((len_word + 1) * sizeof(char)); // +1 для '\0'

        for (size_t t = 0; t < len_word; t++)
            new_word[t] = mas_of_str[j][len_word - t - 1];
        new_word[len_word] = '\0';

        strcpy(mas_of_str[j], new_word);
        free(new_word);
    }

    //printf("\n\n\n");
    //for (int j = 0; j < k_words; j++)
    //    printf("%s\n", mas_of_str[j]);


    // склеиваем обратно      
    const char * str_add = ";";
    size_t pred_words_len = 0;
    for (int j = 0; j < k_words; j++) {
        if (j != k_words - 1) strcat(mas_of_str[j], str_add);
        size_t len_cur_word = strlen(mas_of_str[j]);

        for (size_t t = 0; t < len_cur_word; t++)
            str[pred_words_len + t] = mas_of_str[j][t];

        pred_words_len += len_cur_word;
    }

    //printf("\n\n\n");
    //for (int j = 0; j < k_words; j++)
    //    printf("%s\n", mas_of_str[j]);

    // освобождаем
    for (int j = 0; j < k_words; j++)
        free(mas_of_str[j]);
    free(mas_of_str);
    mas_of_str = NULL;
}

/* int main() {
    char str[] = "";
    printf("%s\n", str);
    swap_pairs(str);
    printf("%s\n", str);
    return 0;
}*/