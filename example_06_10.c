#include <stdio.h>
#include <stdlib.h>

int main(void) {

    /* способ через fgets
    // gets(str) делать нельзя, т.к. нет способа проверить вышло ли за границу массива
    fgets(str, sizeof(str), stdin);

    char str[10];

    // меняем \n на \0
    for (int i = 0; i < sizeof(str); i++) {
        if (str[i] == '\n') {
            str[i] = 0;
            break;
        }
    }
    */

    char *buf = NULL;
    size_t size = 0;
    ssize_t r = 0;
    getline(&buf, &size, stdin);
    //цикл вывода - while ()
    printf("%s\n", buf);
    return 0;
}