#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

ssize_t my_strlen(const char* ptr) {
    if (ptr == NULL) return -1;
    ssize_t len;
    for (len = 0; *(ptr + len) != '\0'; len++) {}
    return len;
}

int my_strcmp(const char* str1, const char* str2) {
    // проверка на NULL
    if (str1 == NULL || str2 == NULL) return INT_MAX;

    int i = 0;
    while (*(str1 + i) != '\0' || *(str2 + i) != '\0') {
        if (*(str1 + i) > *(str2 + i))
            return 1;

        if (*(str1 + i) < *(str2 + i))
            return -1;
        i++;
    }
    return 0;
}

// найти адрес начала подстроки в строке
char* my_strstr(const char* str, const char* sub) {
    // проверка на NULL
    if (str == NULL || sub == NULL) return NULL;

    // проверка на пустую подстроку
    ssize_t len_sub = my_strlen(sub);
    if (len_sub == 0) return (char*)str;

    // создаем буффер-строку
    char buf [len_sub + 1];
    buf[len_sub] = '\0';

    ssize_t p = 0;
    ssize_t len_str = my_strlen(str);
    while (p + len_sub <= len_str) {
        // создаем буфер текущей подстроки
        for (ssize_t i = 0; i < len_sub; i++) buf[i] = str[i + p];

        // проверка на совпадение текущей подстроки и sub
        if (my_strcmp(buf, sub) == 0) return (char*)(str + p);

        p++;
    }

    return NULL;
}

void print_str_arr(char** mas_of_str, int len_mas) {
    for (int i = 0; i < len_mas; i++) 
        printf("%d:%s\n", i + 1, mas_of_str[i]);
    return;
}

int search_arr(char** mas_of_str, int len_mas, int num_sub, char* sub) {
    // проверка на корректный num_sub
    if (num_sub <= 0) return 1;

    // проверка на корректный len_mas
    if (len_mas <= 0) return 1;

    // проверка на корректный mas_of_str
    if (mas_of_str == NULL) return 1;

    // проверка на корректный sub
    if (sub == NULL || my_strlen(sub) == 0) return 1;

    ssize_t len_sub = my_strlen(sub);

    for (int i = 0; i < len_mas; i++) {
        // считаем количество вхождений подстроки
        char* last_include_sub = my_strstr(mas_of_str[i], sub);
        int res_num_sub = 0;
        while (last_include_sub != NULL) {
            res_num_sub++;
            // сдвигаем указатель на последнее включение на размер искомой подстроки
            last_include_sub += len_sub;
            last_include_sub = my_strstr(last_include_sub, sub);
        }

        if (res_num_sub == num_sub)
            printf("%d:%s\n", i + 1, mas_of_str[i]);
    }
    return 0;
}
int main(int argc, char** argv) {
    // проверка на неправильно число параметров
    if (argc != 3) return 1;

    char **mas_of_str =  NULL;;

    // чтение и запись в mas_of_str
    int count_str = 0;
    int len_mas = 10;
    int cur_ch;
    int size_str = 100;
    int i = 0;

    // пытаемся выделить память для mas_of_str
    mas_of_str = (char**)malloc(len_mas * sizeof(char*));

    // проверка на возможность выделить память для mas_of_str
    if (!mas_of_str) {
        printf("Cant allocate memory\n");
        return 1;
    }

    // пытаемся выделить память для строки
    mas_of_str[count_str] = (char*)malloc(size_str * sizeof(char));

    // проверка на возможность выделить память для строки
    if (!mas_of_str[count_str]) {
        printf("Cant allocate memory\n");
        return 1;
    }

    while ((cur_ch = getchar()) != EOF) {
        if (cur_ch == '\n') {
            mas_of_str[count_str][i] = '\0';
            count_str++;

            // если текущей памяти не хватило для mas_of_str -> выделяем еще
            if (count_str == len_mas) {
                char **buf_mas = (char**)realloc(mas_of_str, len_mas * 2 * sizeof(char*));
                if (!buf_mas) {
                    printf("Cant allocate memory");
                    for (int j = 0; j < count_str; j++) free(mas_of_str[j]);
                    free(mas_of_str);
                    return 1;
                } else {
                    mas_of_str = buf_mas;
                    len_mas *= 2;
                }
            }

            // выделяем память под следующую строку
            size_str = 100;
            i = 0;
            mas_of_str[count_str] = (char*)malloc(size_str * sizeof(char));
            if (!mas_of_str[count_str]) {
                printf("Cant allocate memory\n");
                for (int j = 0; j < count_str; j++) free(mas_of_str[j]);
                free(mas_of_str);
                return 1;
            }
        } else {
            mas_of_str[count_str][i] = (char)cur_ch;
            i++;

            // если буфер строки заполнен -> расширяем его
            if (i == size_str - 1) {
                char *buf = realloc(mas_of_str[count_str], size_str * 2 * sizeof(char));
                if (!buf) {
                    printf("Cant allocate memory\n");
                    for (int j = 0; j <= count_str; j++) free(mas_of_str[j]);
                    free(mas_of_str);
                    return 1;
                }
                mas_of_str[count_str] = buf;
                size_str *= 2;
            }
        }
    }

    // дообработка строки, если файл закончился без переноса строки
    if (i > 0) {
        mas_of_str[count_str][i] = '\0';
        count_str++;
    } else {
        free(mas_of_str[count_str]);
    }


    // преобразуем строку в число
    char *env;
    long num_sub = strtol(argv[2], &env, 10);
    if (*env || num_sub != (int)num_sub) {
        printf("Error");
        return 1;
    }

    char* sub = argv[1];

    // ищем и выводим
    if (search_arr(mas_of_str, count_str, num_sub, sub))
        return 1;

    // освобождаем память
    for (int i = 0; i < count_str; i++)
        free(mas_of_str[i]);
    free(mas_of_str);
    mas_of_str = NULL;

    return 0;
}