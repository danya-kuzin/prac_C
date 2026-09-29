// перевести число из litle endian в big endian
// идея: создадим четыре маски

#include <stdio.h>

int litle_2_big(int num) {
    
    unsigned int mask_1, mask_2, mask_3, mask_4;
    mask_1 = 0xFF000000;
    mask_2 = 0x00FF0000;
    mask_3 = 0x0000FF00;
    mask_4 = 0x000000FF;

    mask_1 = mask_1&num;
    mask_2 = mask_2&num;
    mask_3 = mask_3&num;
    mask_4 = mask_4&num;

    mask_1 >>= 24;
    mask_2 >>= 8;
    mask_3 <<= 8;
    mask_4 <<= 24;
    
    return (mask_1|mask_2|mask_3|mask_4);
}

int main(void) {

    int num;
    scanf("%d", &num);
    litle_2_big(num);
    return 0;

}