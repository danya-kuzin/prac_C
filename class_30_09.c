#include <stdio.h>
#include <stdlib.h>

// функция для преобразования строки (сортировка пузырьком)
void transform(int *arr, int count) {

    int cur_change_ch;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < (count - i - 1); j++) {
            if (arr[j] <= 'Z' && arr[j] >= 'A' 
                && arr[j+1] <= 'z' && arr[j+1] >= 'a') {
                cur_change_ch = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = cur_change_ch;
            }
        }
    }
}

int main(void) {
    int size = 100;
    int cur_ch; 
    int count = 0;
    int *arr = NULL;

    // пытаемся выделить память
    arr = (int*)malloc(size * sizeof(int));

    // проверка на возможность выделить память
    if (!arr) {
        printf("Cant allocate memory\n");
        return 1;
    }

    // вводим строку
    do {
        cur_ch = getchar();
        arr[count] = cur_ch;
        count++;

        // если текущей памяти не хватило -> выделяем еще
        if (count == size) {
            int *buf = (int*)realloc(arr, size * 2 * sizeof(int));

            // проверка на возможность выделить память
            if (!buf) {
                printf("Cant allocate memory");
                free(arr);
                return 1;
            } else {
                arr = buf;
                size *= 2;
            }
        }
    
    } while (cur_ch != '\n' && cur_ch != EOF);

    // преобразуем строку
    transform(arr, count);

    // выводим строку
    for (int i = 0; i < count; i++) {
        putchar(arr[i]);
    }

    // освобождаем память
    free(arr);
    arr = NULL;

    return 0;
}