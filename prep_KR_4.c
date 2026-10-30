#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int cur_num_1;
    int cur_num_2;
    int flag_end_1 = 0;
    int flag_end_2 = 0;
    int stop;
    FILE *f_1 = NULL;
    FILE *f_2 = NULL;
    f_1 = fopen(argv[1], "r");
    f_2 = fopen(argv[2], "r");

    if (fscanf(f_1, "%d", &cur_num_1) != 1) {
        while (fscanf(f_2, "%d", &cur_num_2) == 1)
            printf("%d\n", cur_num_2);

        fclose(f_1);
        fclose(f_2);
        return 0;
    }

    if (fscanf(f_2, "%d", &cur_num_2) != 1) {
        while (fscanf(f_1, "%d", &cur_num_1) == 1)
            printf("%d\n", cur_num_1);

        fclose(f_1);
        fclose(f_2);
        return 0;
    }

    while (!(flag_end_1 && flag_end_2)) {
        if ((!flag_end_2 && cur_num_2 < cur_num_1) || flag_end_1) {
            printf("%d\n", cur_num_2);
            stop = fscanf(f_2, "%d", &cur_num_2);
            if (stop != 1) flag_end_2 = 1;  
        }

        else if (!flag_end_1) {
            printf("%d\n", cur_num_1);
            stop = fscanf(f_1, "%d", &cur_num_1);
            if (stop != 1) flag_end_1 = 1;
        }
    }

    fclose(f_1);
    fclose(f_2);
    return 0;
}