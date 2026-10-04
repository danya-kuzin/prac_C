#include <stdio.h>
#include <stdlib.h>

char* packer(char* arr_nums, unsigned char elem_quantity, int* size_arr_pack) {

    // первый проход по массиву, ищем общее количество значащих бит
    int sum_sig_bit = 0;
    unsigned char cur_elem;
    for (unsigned char i = 0; i < elem_quantity; i++) {
        cur_elem = arr_nums[i];
        while (cur_elem != 0) {
            sum_sig_bit++;
            cur_elem >>= 1;
        }
    }

    // выделяем память под массив упакованных чисел
    char *arr_pack = NULL;
    *size_arr_pack = (elem_quantity + 1) / 2 + (sum_sig_bit + 7) / 8 + 1;
    arr_pack = (char*)calloc(*size_arr_pack, sizeof(char));
    if (!arr_pack) {
        printf("Cant allocate memory\n");
        return NULL;
    }

    // собираем массив
    arr_pack[0] = elem_quantity;

    // считаем и пишем кол-ва значищих битов
    unsigned char num_sig_bit;
    unsigned char half_byte = 4;

    for (unsigned char i = 0; i < elem_quantity; i++) {

        // считаем количество значащих битов
        num_sig_bit = 0;
        cur_elem = arr_nums[i];
        while (cur_elem != 0) {
            num_sig_bit++;
            cur_elem >>= 1;
        }

        if (i % 2 == 0)
            num_sig_bit = num_sig_bit << half_byte;

        arr_pack[i / 2 + 1] += num_sig_bit;
        //printf("%hhd   el %hhu, num %hhu, i = %hhu \n", i / 2 + 1, arr_pack[i / 2 + 1], arr_nums[i], i);
    }

    // заполняем следующую часть массива упакованными битами
    unsigned char cur_elem_copy;
    unsigned char cur_ostatok = 0;
    int cur_byte;
    int bit_pos = 0;
    for (unsigned char i = 0; i < elem_quantity; i++) {

        // считаем количество значащих бит для текущего числа
        num_sig_bit = 0;
        cur_elem = arr_nums[i];
        while (cur_elem != 0) {
            num_sig_bit++;
            cur_elem >>= 1;
        }

        // у числа 0 значащих битов нет
        if (num_sig_bit == 0)
            continue;

        // определяем текущий байт и номер свободного бита в этом байте
        cur_byte = bit_pos / 8 + (elem_quantity + 1) / 2 + 1;
        cur_elem = arr_nums[i];
        cur_elem <<= 8 * sizeof(char) - num_sig_bit; // выравниваем по левому краю
        cur_elem_copy = cur_elem;
        cur_elem_copy >>= bit_pos % 8;
        arr_pack[cur_byte] += cur_ostatok + cur_elem_copy;
        cur_ostatok = cur_elem << (8 * sizeof(char) - bit_pos % 8);
        bit_pos += num_sig_bit;
    }

    arr_pack[cur_byte + 1] |= cur_ostatok;

    return arr_pack;

}

int main(void) {

    unsigned char elem_quantity;
    scanf("%hhd", &elem_quantity);

    // выделяем память под массив чисел
    char *arr_nums = NULL;
    arr_nums = (char*)calloc(elem_quantity, sizeof(char));
    if (!arr_nums) {
        printf("Cant allocate memory\n");
        return 1;
    }

    // заполняем массив чисел
    unsigned char cur_elem;
    for (unsigned char i = 0; i < elem_quantity; i++) {
        scanf("%hhd", &cur_elem);
        arr_nums[i] = cur_elem;
    }

    // упаковываем их и проверяем что память смогла выделиться
    int size_arr_pack;
    char* arr_pack = packer(arr_nums, elem_quantity, &size_arr_pack); 
    if (!arr_pack) {
        free(arr_nums);
        arr_nums = NULL;
        return 1;
    }

    for (unsigned char i = 0; i < size_arr_pack; i++) {
        // выводим число в двоичном формате
        unsigned char mask = 1u<<(8*sizeof(char) - 1); 
        for ( ; mask != 0; mask>>=1) {
            if (mask & arr_pack[i])
                putchar('1');
            else
                putchar('0');
        }
        putchar(' ');
    }

    // освоождаем память
    free(arr_nums);
    arr_nums = NULL;

    free(arr_pack);
    arr_pack = NULL;

    return 0;

}