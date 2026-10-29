#include <stdio.h>
#include <stdlib.h>

int main() {
    int cur_ch;
    int cur_dig = 0;
    int sum = 0;
    while ((cur_ch = getchar()) != EOF) {
        if (cur_ch >= '0' && cur_ch <= '9')
            cur_dig = cur_ch - '0';

        else if (cur_ch >= 'a' && cur_ch <= 'f')
            cur_dig = cur_ch - 'a' + 10;

        else if (cur_ch >= 'A' && cur_ch <= 'F')
            cur_dig = cur_ch - 'A' + 10;

        else continue;
        
        sum += cur_dig;
    }

    fprintf(stdout, "%d\n", sum);
    return 0;
}