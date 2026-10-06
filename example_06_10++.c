// вводим параметры

#include <stdio.h>
#include <stdlib.h>

// argv[1], argv[2] и т.д. - будут char * указатели на введенные строки-параметры
int main(int argc, char** argv) {

    if (argc == 1) {
        printf("no parmeters");
        return 1;
    }

    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv)
    }

    // чтобы распарсить параметры используем sscanf
    int num;
    sscanf(argv[1], "%d", &num);

    // чтобы вывести строку, опасность выйти за границы массива
    char buf[100];
    sprintf(buf, "%d", num);

    // более безопасный вариант
    sprintf(buf, sizeof(buf), "%d", num)

    // если то, что вернул sprintf меньше размера buf, то он прочитал не все

    return 0;
}