#include <stdio.h>

int main(void)
{
    unsigned int command;

    // общая часть ввода
    unsigned int mask_rs1, mask_funct3, mask_rd, mask_opcode;
    unsigned char opcode, rd, funct3, rs1;
    unsigned char opcode_r_type, opcode_i_type;
    unsigned char addi_funct3, andi_funct3, ori_funct3;
    unsigned char add_funct3, sub_funct3, mul_funct3, div_funct3;

    // различия по opcode
    unsigned int mask_funct7, mask_rs2;
    unsigned char funct7, rs2;
    unsigned char add_funct7, sub_funct7, mul_funct7, div_funct7;
    signed short imm; // т.к. потом будем выводить это число в знак. виде

    scanf("%u", &command);
    mask_rs1    = 0x000F8000; 
    mask_funct3 = 0x00007000;
    mask_rd     = 0x00000F80;
    mask_opcode = 0x0000007F;
    mask_funct7 = 0xFE000000;
    mask_rs2    = 0x01F00000;

    rs1    = (command & mask_rs1) >> 15;
    funct3 = (command & mask_funct3) >> 12;
    rd     = (command & mask_rd) >> 7;
    opcode = command & mask_opcode;

    opcode_r_type = 0x33;
    opcode_i_type = 0x13;

    addi_funct3 = 0x00;
    andi_funct3 = 0x07;
    ori_funct3  = 0x06;

    add_funct3 = 0x00;
    sub_funct3 = 0x00;
    mul_funct3 = 0x00;
    div_funct3 = 0x04;

    add_funct7 = 0x00;
    sub_funct7 = 0x20;
    mul_funct7 = 0x01;
    div_funct7 = 0x01;

    if (opcode == opcode_r_type) {
        funct7 = (command & mask_funct7) >> 25;
        rs2 = (command & mask_rs2) >> 20;

        if (funct3 + funct7 == add_funct3 + add_funct7)
            printf("add ");
        else if (funct3 + funct7 == sub_funct3 + sub_funct7)
            printf("sub ");
        else if (funct3 + funct7 == mul_funct3 + mul_funct7)
            printf("mul ");
        else if (funct3 + funct7 == div_funct3 + div_funct7)
            printf("div ");
    }

    if (opcode == opcode_i_type) {
        /*маска не нужна, т.к. слева от числа ничего не стоит
         и выполнится автоматическое знаковое расширение*/
        imm = ((signed int)command) >> 20;

        if (funct3 == addi_funct3)
            printf("addi ");
        else if (funct3 == andi_funct3)
            printf("andi ");
        else if (funct3 == ori_funct3)
            printf("ori ");

    }

    // выводим первые два операнда
    printf("x%u, x%u, ", rd, rs1);

    if (opcode == opcode_i_type) {
        printf("%d", imm);
    }

    if (opcode == opcode_r_type) {
        printf("x%u", rs2);
    }

    return 0;
}