// инвертировать нечетные биты, если число четное
// циклический сдвиг вправо, если число нечетное (не факт что правильно реализовал)

#include <stdio.h>

int main(void)
{
    unsigned short x, new_x;
    unsigned short last_2_bits, mask_nech;
    
    while (scanf("%hd", &x) != EOF) {

        if (x % 2 == 1) {
            last_2_bits = 0x0003;
            last_2_bits = last_2_bits & x;
            new_x = (x >> 2) | (last_2_bits << 14);
        } else {
            mask_nech = 0xAAAA;
            new_x = x ^ mask_nech;
        }

        printf("%hd", new_x);

    }

    return 0;
}