// программа для поиска максимума и его места в файле

#include <stdio.h>

int main(void) {
    // открываем файл и проверяем что он открылся
    FILE *f = fopen("./filename", "r");
    if (f==NULL) {}

    int a, max;
    long pos;

    fread(&a, sizeof(int), 1, f);
    max = a;

    pos = 0;
    while (fread(&a, sizeof(int), 1, f)) 
        if (max < a) {
            max = a;
            pos = ftell(f) - sizeof(int);
        }
    
    printf("max: %d \n pos: %ld ", max, pos);
    fclose(f);
    return 0;
}