// построить бинарное дерево и написат функцию, которая ищет два минимальных ключа
#include <stdio.h>
#include <stdlib.h>

struct tnode{
    int k;
    struct tnode *left;
    struct tnode *right;
};

// функция для построения бинарного дерева
struct tnode *add_node(struct tnode *p, int k){ 
    if (p == NULL){  
        p = (struct tnode*)malloc(sizeof(struct tnode)); 
        p->k = k;  
        p->left = NULL;  
        p->right = NULL; 
        //printf("k_null: %d \n", k);
    } 
    else if (k < (p->k)) {
        //printf("k_left: %d \n", k);
        p->left = add_node(p->left, k); 
    }
    else if (k > (p->k)) {
        //printf("k_right: %d \n", k);
        p->right = add_node(p->right, k);  
    }
    return p;
}


// функция для поиска двух минимумов
void find_min_keys(struct tnode *p, int *min_1, int *min_2) {

    if (p->left == NULL) {
        // если уперлись влево, то это минимум всего дерева
        *min_1 = p->k;
        // идем на одну ветвь вправо
        // если справа нету ветки
        if (p->right == NULL) {
            return;
        } 
        // если справа ветка есть
        else {
            struct tnode *temp = p->right; // создаем временный указатель
            // идем влево пока не достигнем дна
            while (temp->left != NULL) {
                temp = temp->left;
            }
            *min_2 = temp->k;
            return;
        }
    } 

    // если левая ветка есть, то текущий узел - кандидат на второй мин
    *min_2 = p->k; 
    
    // идем влево, пока не упремся в NULL
    find_min_keys(p->left, min_1, min_2);
}

// функция рекурсивного освобождения памяти дерева
void free_tree(struct tnode *p) {
    // если дошли до листочка, то освобождать ничего не нужно
    if (p == NULL) return;

    // если левое поддерево не пустое
    free_tree(p->left);

    // если правое поддерево не пустое
    free_tree(p->right);

    free(p);

}
int main(void) {
    // считываем почисленно и строим дерево
    int num;
    int ch;
    struct tnode *p = NULL;
    while (scanf("%d", &num) == 1) {
        p = add_node(p, num);

        // смотрим, что ввели после числа
        ch = getchar(); 
        if (ch == '\n' || ch == EOF)
            break;
    }

    // получаем указатель на минимум
    //printf("\n\n---------find mins---------\n\n\n");
    int min_1 = 0; 
    int min_2 = 0;
    find_min_keys(p, &min_1, &min_2);
    //printf("\nmin_1: %d", min_1);
    //printf("\nmin_2: %d", min_2);
    printf("%d %d", min_1, min_2);

    // освобождаем память
    free_tree(p);

    return 0;
}