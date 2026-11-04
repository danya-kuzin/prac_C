#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Твой ряд целых чисел
    int numbers[] = {3, 10, 2, 12, 4, 9, 7, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    FILE *f = fopen("numbers.bin", "wb");
    if (!f) {
        perror("fopen");
        return 1;
    }

    // Записываем весь массив одним вызовом
    size_t written = fwrite(numbers, sizeof(int), count, f);
    if (written != count) {
        perror("fwrite");
        fclose(f);
        return 1;
    }

    fclose(f);
    return 0;
}
