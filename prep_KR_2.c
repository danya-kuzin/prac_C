#include <stdio.h>
#include <stdlib.h>

int main () {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);

    for (int i = a - 1; i < b; i++) {
        for (int j = a - 1; j < b; j++) {
            if (i == a - 1 && j == a - 1)
                for (int t = 0; t < n; t++) printf(" ");
            else if (i == a - 1)
                printf("%*d", n, j);
            else if (j == a - 1)
                printf("%*d", n, i);
            else 
                printf("%*lld", n, (long long)i*j);

            if (j != b - 1) printf(" ");
        }

         printf("\n");
    }
    return 0;
}