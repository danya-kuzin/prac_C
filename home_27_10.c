// выдает ош на  ./home_27_10 input.txt -d 1 2 -w cat -l хотя не должно

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct tnode {
    int k_word_in_str;
    int k_str;
    char word[1000];
    struct tnode *left;
    struct tnode *right;
};

enum mode {
    WORDDUP,
    LINEDUP,
    NOPE_MODE,
    ERROR
};

struct diapazon {
    char diapazon_exist;
    char k_params;
    char error;
    int start;
    int end;
};

// строим бин дерево
struct tnode *add_node(struct tnode *p, int k_word_in_str, int k_str, char *word){ 
    if (p == NULL){  
        p = (struct tnode*)malloc(sizeof(struct tnode)); 
        p->k_word_in_str = k_word_in_str;
        p->k_str = k_str;
        strcpy(p->word, word); 
        p->left = NULL;  
        p->right = NULL; 
        //printf("word_null: %s \n", word);
    } 
    else if (strcmp(word, p->word) < 0) {
        //printf("word_left: %s \n", word);
        p->left = add_node(p->left, k_word_in_str, k_str, word); 
    }
    else if (strcmp(word, p->word) > 0) {
        //printf("word_right: %s \n", word);
        p->right = add_node(p->right, k_word_in_str, k_str, word);
    }
    return p;
}

struct diapazon get_diapazon(int argc, char **argv) {
    int d_i;
    struct diapazon d;
    d.diapazon_exist = 0;
    d.error = 0;

    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--diapason") == 0) {
            d.diapazon_exist = 1;
            d_i = i;
            break;
        }
    
    if (d.diapazon_exist == 1) {
        if ((argc - d_i) < 2) {
            printf("Incorrect parameters of command line");
            d.error = 1;
            return d;
        }

        char *env;
        long start = strtol(argv[d_i + 1], &env, 10);
        if (*env || start != (int)start) {
            printf("Incorrect diapason");
            d.error = 1;
            return d;
        }

        d.k_params = 1;
        long end;
        if ((argc - d_i) != 2) {
            end = strtol(argv[d_i + 2], &env, 10);
            if (!(*env)) d.k_params = 2;
        }

        if (d.k_params == 2) {
            if (start > end) {
                printf("Incorrect diapason");
                d.error = 1;
                return d;
            }
        }

        if (start <= 0 || (d.k_params == 2 && end <= 0)) {
            printf("Incorrect diapason");
            d.error = 1;
            return d;
        }

        d.start = start;
        if (d.k_params == 2) d.end = end;
    }

    return d;
}
enum mode get_mode(int argc, char **argv) {

    enum mode cur_mode = NOPE_MODE;
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--worddup") == 0) 
            cur_mode = WORDDUP;
    
    // проверка на парочку -w -l
    for (int i = 1; i < argc; i++)
        if ((strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--linedup") == 0) && cur_mode == WORDDUP) {
            printf("Incorrect parameters of command line");
            return ERROR;
        }
    
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--linedup") == 0) 
            cur_mode = LINEDUP;
    
    return cur_mode;
}


int main(int argc, char **argv) {
    FILE *f = NULL;
    f = fopen(argv[1], "r");

    if (f == NULL) {
        printf("Can't open file %s", argv[1]);
        return 1;
    }

    enum mode cur_mode;
    cur_mode = get_mode(argc, argv);
    if (cur_mode == ERROR) return 1;

    int norm_arg_count = 2;
    struct diapazon d;
    d = get_diapazon(argc, argv);
    if (d.error == 1) return 1;

    if (d.diapazon_exist) norm_arg_count += 1 + d.k_params;
    if (cur_mode == WORDDUP) norm_arg_count += 2;
    if (cur_mode == LINEDUP) norm_arg_count += 1;
    if (argc != norm_arg_count) {
        printf("Incorrect parameters of command line");
        return 1;
    }

    // читаем почарово
    int cur_ch;
    char cur_word[1001] = {0};
    char cur_str[1001] = {0};
    char pred_str[1001] = {0};
    int i = 0;
    int str_symb_i = 0;
    int count_word_in_str = 0;
    int count_str = 1;
    struct tnode *p = NULL;
    while (1) {
        cur_ch = fgetc(f);

        if (cur_ch != '\n' && cur_ch != EOF) {
            cur_str[str_symb_i] = cur_ch;
            str_symb_i++;
        }

        if (cur_ch == '\n' || cur_ch == EOF) {
            cur_str[str_symb_i] = '\0';
            if (d.diapazon_exist) {
                if (d.k_params == 1) {
                    if (count_str >= d.start) {
                        if ((strcmp(cur_str, pred_str) != 0) && cur_mode == LINEDUP)
                            printf("%s\n", cur_str);
                    }

                }

                if (d.k_params == 2) {
                    if (count_str >= d.start && count_str <= d.end) {
                        if ((strcmp(cur_str, pred_str) != 0) && cur_mode == LINEDUP)
                            printf("%s\n", cur_str);
                    }
                }
            }
            else {
                if ((strcmp(cur_str, pred_str) != 0) && cur_mode == LINEDUP)
                    printf("%s\n", cur_str);
            }
            printf("%s\n", cur_str);
            strcpy(pred_str, cur_str);
            str_symb_i = 0;
        }

        if (cur_ch == ' ' || cur_ch == '(' || cur_ch == ')' || cur_ch == '.' || cur_ch == ':' ||
            cur_ch == EOF || cur_ch == ';' || cur_ch == '-' || cur_ch == ',' || cur_ch == '\n') {
            cur_word[i] = '\0';

            if (strlen(cur_word) == 0) {
                if (cur_ch == EOF) break;
                if (cur_ch == '\n') count_str++;
                continue;
            }

            count_word_in_str++;
            //printf("%d(%d): %s\n", count_str, count_word_in_str, cur_word);
            p = add_node(p, count_word_in_str, count_str, cur_word);
            i = 0;

            if (cur_ch == '\n' || cur_ch == EOF) {
                count_str++;
                count_word_in_str = 0;
            }

            if (cur_ch == EOF)
                break;

            continue;
        }

        cur_word[i] = cur_ch;
        i++;
    }

    fclose(f);
    return 0;
}