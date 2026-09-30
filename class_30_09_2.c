#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int row, col;
    int **matr = NULL; 

    // задаем размеры матрицы
    scanf("%d", &row);
    col = row;

    // пытаемся выделить память для matr
    matr = (int**)malloc(row * sizeof(int*));

    // проверка на возможность выделить память для matr
    if (!matr) {
        printf("Cant allocate memory\n");
        return 1;
    }

    // пытаемся выделить память для строк
    for (int i = 0; i < row; i++) {
        matr[i] = (int*)malloc(col * sizeof(int));
        // проверка на возможность выделить память для строки
        if (!matr[i]) {
            // очистка строки
            for (int j = 0; j < i; j++) {
                free(matr[j]);
            }
            // очистка самого matr
            free(matr);
            matr = NULL;
            printf("Cant allocate memory\n");
            return 1;
        }
    }

    // заполняем матрицу и выводим ее
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {

            // находим глибину вложенности текущего кольца
            // это min(i, j, row - 1 - i, col - 1 - j)
            int cur_depth_of_circle = i; // глубина вложенности, т.е. порядковый номер кольца
            if (j < cur_depth_of_circle) cur_depth_of_circle = j;
            if (row - 1 - i < cur_depth_of_circle) cur_depth_of_circle = row - 1 - i;
            if (col - 1 - j < cur_depth_of_circle) cur_depth_of_circle = col - 1 - j;

            // считаем сумму элементов во всех предыдущих, т.е. внешних, кольцах как периметры
            int sum_prev_circles = 0;
            for (int p = 0; p < cur_depth_of_circle; p++) {
                sum_prev_circles += 2 * (2 * (row - 2 * p) - 2);
            }

            // считаем смещение текущей ячейки внутри её собственного кольца
            int offset = 0; // текущее смещение
            int cur_size_of_circle = row - 2 * cur_depth_of_circle; // размер стороны текущего кольца

            if (i == cur_depth_of_circle) { 
                // верхняя грань кольца
                offset = j - cur_depth_of_circle;
            } else if (j == col - 1 - cur_depth_of_circle) { 
                // правая грань кольца
                offset = (cur_size_of_circle - 1) + (i - cur_depth_of_circle);
            } else if (i == row - 1 - cur_depth_of_circle) { 
                // нижняя грань кольца
                offset = 2 * (cur_size_of_circle - 1) + (col - 1 - cur_depth_of_circle - j);
            } else if (j == cur_depth_of_circle) { 
                // левая грань кольца
                offset = 3 * (cur_size_of_circle - 1) + (row - 1 - cur_depth_of_circle - i);
            }

            // Итоговое значение
            matr[i][j] = sum_prev_circles + offset + 1;

            if (j + 1 == row) {
                printf("%2d", matr[i][j]);
            } else {
                printf("%2d ", matr[i][j]);
            }
        }
        if (i != row -1)
            printf("\n");
    }

    // освобождаем память
    for (int i = 0; i < row; i++)
        free(matr[i]);
    free(matr);
    matr = NULL;

    return 0;
}