#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *arr = NULL;
    int size = 10;
    int count = 0;

    arr = (int*)malloc(size * sizeof(int));
    if (!arr) {
        printf("Cant allocate memory\n");
        return 1;
    }

    while (scanf("%d", arr+count == 1)) {
        count++;

        if (count == size) {

            int *buf = (int*)realloc(arr, size * 2 * sizeof(int));
            if (!buf) {
                printf("Cant allocate memory");
                free(arr);
                return 1;
            } else {
                arr = buf;
                size *= 2;
            }

        }
    }

    for (int i = count-1; i >= 0; i--)
        printf("%d", arr[i]);
    printf("/n");
    free(arr);
    arr = NULL;
    return 0;
}