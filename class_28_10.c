#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    unsigned long long S;
    scanf("%d", &N);
    scanf("%d", &M);
    unsigned long long * X = NULL;
    unsigned long long * Y = NULL;
    X = (unsigned long long *)malloc(N * sizeof(unsigned long long));
    Y = (unsigned long long *)malloc(M * sizeof(unsigned long long));
    
    for (int i = 0; i < N; i++) {
        scanf("%llo", &X[i]);
    }

    for (int j = 0; j < M; j++) {
        scanf("%llo", &Y[j]);
    }
    
    scanf("%llo", &S);
       
    int flag_exist = 0;
    for (int i = N - 1; i >= 0 && !flag_exist; i--) {
        for (int j = M - 1; j >= 0; j--) {
            if ((X[i] + Y[j]) < Y[j] || (X[i] + Y[j]) < X[i]) {}
            else if (X[i] + Y[j] == S) {
                flag_exist = 1;
                printf("%d %d", i, j);
                break;
            }
        }
    }
    
    int minus_one = -1;
    if (!flag_exist) {
        printf("%d %d", minus_one, minus_one);
    }
    
    free(X);
    free(Y);
    X = NULL;
    Y = NULL;
    //printf("%d", N);
}