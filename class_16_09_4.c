#include <stdio.h>

int main(void)
{
    int ch;
    int cur_sum = 0;
    short flag_empty = 1;
    short flag_stop = 0;
    short flag_first_output = 1;

    ch = getchar();

    while (1) {
        // пропускаем пробелы и переводы строк между числами
        while (ch == ' ' || ch == '\n' || ch == '\t') {
            ch = getchar();
        }

        // если пустой ввод
        if (ch == EOF) {
            if (flag_empty) {
                printf("-1");
            }
            return 0;
        }

        cur_sum = 0;

        while (ch != ' ' && ch != '\n' && ch != '\t' && ch != EOF) {
            // проверка на не цифру
            if (ch < '0' || ch > '9') {
                flag_stop = 1;
                break;
            }

            // проверка на цифру 5 и суммирование
            if (ch != '5') {
                cur_sum += ch - '0';
            }

            ch = getchar();
        }

        // если некорректный ввод
        if (flag_stop) {
            if (flag_empty) {
                printf("0");
            }
            return 0;
        }

        if (!flag_first_output) {
            printf(" ");
        }

        printf("%d", cur_sum);

        flag_empty = 0;
        flag_first_output = 0;
    }

    return 0;
}