#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char str1[12] = {0};
    scanf("%11s", str1); // scanf будет читать максимум 11 символов
    printf("%s", str);
    // вместо s можно написать [abc] --> scanf будет читать до a, b, c
    // вместо s можно написать [a-z] --> scanf будет читать до первой мал. лат. буквы
    // вместо s можно написать [^abc] --> scanf будет читать до любого кроме a, b, c

    // динамическое считывание (медленное, но без фикс. размера)
    char *buf = NULL;
    scanf("%ms", &buf);
    printf("%s\n", buf);
    free(buf);

    return 0;
}