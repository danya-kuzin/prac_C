#include <stdio.h>

// перечислимый тип данных для обработки вывода
enum Output {YES, NO, NO_ANSWER, WRONG_SIGN, NO_EQUAL_SIGN, INPUT_ERROR};

// функция для вывода результата
int res_func(enum Output output_res) {
    switch (output_res) {
        case WRONG_SIGN:
            printf("WRONG SIGN");
            return 0;
        
        case NO_EQUAL_SIGN:
            printf("NO EQUAL SIGN");
            return 0;
        
        case NO_ANSWER:
            printf("NO ANSWER");
            return 0;
        
        case INPUT_ERROR:
            printf("INPUT ERROR");
            return 0;
        
        case YES:
            printf("YES");
            return 0;
        
        case NO:
            printf("NO");
            return 0;
        
        default:
            printf("INPUT ERROR");
            return 0;
    }
}

int main(void) {
    int first_num = 0, second_num = 0, result_in = 0, result_real;
    char operation;
    int cur_char;
    short flag_exist_dig_after_eq = 0;
    short flag_exist_dig_in_first_num = 0;
    short flag_exist_dig_in_second_num = 0;

    // пропуск пробелов
    cur_char = getchar();
    while (cur_char == ' ' || cur_char == '\t')
        cur_char = getchar();
    
    // получаем первый операнд
    while (cur_char <= '9' && cur_char >= '0') {
        flag_exist_dig_in_first_num = 1;
        first_num = first_num * 10 + (cur_char - '0');
        cur_char = getchar();
    }

    // проверяем что перед первым числом нет плохих символов
    if (!flag_exist_dig_in_first_num)
        return res_func(INPUT_ERROR);

    // пропуск пробелов
    while (cur_char == ' ' || cur_char == '\t')
        cur_char = getchar();

    // получаем знак и проверяем его
    if (cur_char == '+' || cur_char == '*')
        operation = cur_char;
    else
        return res_func(WRONG_SIGN);

    // пропуск пробелов
    cur_char = getchar();
    while (cur_char == ' ' || cur_char == '\t')
        cur_char = getchar();

    // получаем второй операнд
    while (cur_char <= '9' && cur_char >= '0') {
        flag_exist_dig_in_second_num = 1;
        second_num = second_num * 10 + (cur_char - '0');
        cur_char = getchar();
    }

    // проверяем, что первый символ второго операнда - цифра
    if (!flag_exist_dig_in_second_num)
        return res_func(INPUT_ERROR);

    // пропуск пробелов
    while (cur_char == ' ' || cur_char == '\t')
        cur_char = getchar();

    // проверяем на наличие знака равенства
    if (cur_char != '=')
        return res_func(NO_EQUAL_SIGN);

    // пропуск пробелов
    cur_char = getchar();
    while (cur_char == ' ' || cur_char == '\t')
        cur_char = getchar();

    // получаем введенный результат
    while (cur_char <= '9' && cur_char >= '0') {
        flag_exist_dig_after_eq = 1;
        result_in = result_in * 10 + (cur_char - '0');
        cur_char = getchar();
    }
    
    // проверяем, что после знака равенства есть цифра
    if (!flag_exist_dig_after_eq)
        return res_func(NO_ANSWER);

    // пропуск пробелов
    while (cur_char == ' ' || cur_char == '\t')
        cur_char = getchar();

    // проверяем что в введенном результате нет плохих символов
    if (cur_char != '\n' && cur_char != EOF)
        return res_func(INPUT_ERROR);

    // считаем правильный ответ
    if (operation == '*')
        result_real = first_num * second_num;
    else if (operation == '+')
        result_real = first_num + second_num;

    // проверяем правиьность ответа
    if (result_real == result_in)
        return res_func(YES);
    else if (result_real != result_in)
        return res_func(NO);
}