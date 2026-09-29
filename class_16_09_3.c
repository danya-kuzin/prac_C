#include <stdio.h>
int main()
{
    int ch;
    short flag_incorrect = 0;
    int len_first_str = 0, len_second_str = 0;

    // обработка первой строки
    ch = getchar();
    while (ch != '\n' && ch != EOF) {
        if (ch != '=')
            flag_incorrect = 1;
        len_first_str++;
        ch = getchar();
    }

    // обработка второй строки
    ch = getchar();
    while (ch != '\n' && ch != EOF) {
        if (ch != '=')
            flag_incorrect = 1;
        len_second_str++;
        ch = getchar();
    }

    if (len_first_str == 0 || len_second_str == 0)
        flag_incorrect = 1;

    if (flag_incorrect) {
        printf("Incorrect");
    } 
    else if (len_first_str > len_second_str){
        printf("First");
    }
    else if (len_first_str < len_second_str){
        printf("Second");
    }
    else {
        printf("Equal");
    }
	
	return 0;
}