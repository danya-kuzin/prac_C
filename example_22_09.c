// вывести число в битовом виде с помощью сдвигов
// идея: будем маску сдвигать каждый раз на один бит и делать логическое и

#include <stdio.h>

void print_bit(int num) {
    
    unsigned int mask = 1u<<(8*sizeof(int) - 1); // здесь важно указать unsigned
    for ( ; mask != 0; mask>>=1) { // здесь важно указать именно >>= а не >>
        if (mask&num)  // здесь важно не сравнивать с нулем т.к. > 0 ломает приоритеты
            putchar('1');
        else
            putchar('0');
    }
    putchar('\n');

}

int main(void) {

    int num;
    scanf("%d", &num);
    print_bit(num);
    return 0;

}