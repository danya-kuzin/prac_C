#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define LEN_STR 1000

struct position {
    int k_word_in_str;
    long long k_str;
    struct position *next;
};

struct tnode {
    struct position *positions; //список повторов слова
    char word[LEN_STR + 1];
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
    long long start;
    long long end;
};

// строим бин дерево
struct tnode *add_node(struct tnode *p, int k_word_in_str, long long k_str, char *word){ 
    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        if (!p) {
            fprintf(stderr, "Unknown error");
            exit(1);
        }

        p->positions =(struct position*)malloc(sizeof(struct position));
        if (!(p->positions)) {
            free(p);
            fprintf(stderr, "Unknown error");
            exit(1);
        }

        p->positions->k_word_in_str = k_word_in_str;
        p->positions->k_str = k_str;
        p->positions->next = NULL;

        strcpy(p->word, word);

        p->left = NULL;
        p->right = NULL;
    }
    else {
        if (strcmp(word, p->word) < 0) 
            p->left = add_node(p->left, k_word_in_str, k_str, word);
        
        else if (strcmp(word, p->word) > 0)
            p->right = add_node(p->right, k_word_in_str, k_str, word);
        
        // + к списку для этого слова еще пару (строка, номер слова в этой строке)
        else {
            struct position *new_position = malloc(sizeof(struct position));
            if (new_position == NULL) {
                fprintf(stderr, "Unknown error");
                exit(1);
            }

            new_position->k_word_in_str = k_word_in_str;
            new_position->k_str = k_str;

            // вяяжем новый элм списка с началом списка
            new_position->next = p->positions;
            // меняем указатель списка на новый первый элм
            p->positions = new_position;
        }
    }

    return p;
}

struct diapazon get_diapazon(int argc, char **argv) {
    int d_i;
    struct diapazon d;
    d.diapazon_exist = 0;
    d.error = 0;

    for (int i = 2; i < argc; i++)
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--diapason") == 0) {
            d.diapazon_exist = 1;
            d_i = i;
            break;
        }
    
    if (d.diapazon_exist == 1) {
        if ((argc - d_i) < 2) {
            fprintf(stderr, "Incorrect parameters of command line\n");
            d.error = 1;
            return d;
        }

        char *env;
        long long start = strtoll(argv[d_i + 1], &env, 10);

        d.k_params = 1;
        long long end;
        if ((argc - d_i) != 2) {
            end = strtoll(argv[d_i + 2], &env, 10);
            if (!(*env)) d.k_params = 2;
        }

        if (d.k_params == 2) {
            if (start > end) {
                fprintf(stderr, "Incorrect diapason\n");
                d.error = 1;
                return d;
            }
        }

        if (start <= 0 || (d.k_params == 2 && end <= 0)) {
            fprintf(stderr, "Incorrect diapason\n");
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
    for (int i = 2; i < argc; i++)
        if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--worddup") == 0) 
            cur_mode = WORDDUP;
    
    // проверка на парочку -w -l
    for (int i = 2; i < argc; i++)
        if ((strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--linedup") == 0) && cur_mode == WORDDUP) {
            fprintf(stderr, "Incorrect parameters of command line\n");
            return ERROR;
        }
    
    for (int i = 2; i < argc; i++)
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--linedup") == 0) 
            cur_mode = LINEDUP;

    if (cur_mode == NOPE_MODE)
        fprintf(stderr, "Incorrect parameters of command line");
    
    return cur_mode;
}


char* get_arg_after_worddup(int argc, char** argv) {
    for (int i = 2; i < argc; i++)
        if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--worddup") == 0) { 
            if (argc <= i + 1 || strlen(argv[i + 1]) == 0 || strpbrk(argv[i + 1], " ;,.-:()") != NULL)
                return NULL;
            return argv[i + 1];
        }
    return NULL;
}

int check_start_and_amount_of_strs(struct diapazon d, FILE *f) {
    if (d.diapazon_exist) {
        long long real_count_str = 0;
        int check_ch;
        int last_ch = '\n';

        while ((check_ch = fgetc(f)) != EOF) {
            if (check_ch == '\n') real_count_str++;
            last_ch = check_ch;
        }
        //последняя стр без \n
        if (last_ch != '\n') real_count_str++;

        if (d.start > real_count_str) {
            fprintf(stderr, "Incorrect diapason");
            return 1;
        }

        //указатель на начало файла
        rewind(f);
    }

    return 0;
}


int in_diapazon(struct diapazon d, long long count_str) {

    if (!d.diapazon_exist)
        return 1;
    if (d.diapazon_exist && d.k_params == 1 && d.start <= count_str)
        return 1;
    if (d.diapazon_exist && d.k_params == 2 && d.start <= count_str && d.end >= count_str)
        return 1;

    return 0;
}


void print_l(char *pred_str, char *cur_str, enum mode cur_mode,
            struct diapazon d, long long count_str, int cur_ch) {

    int first_str_in_diapazon = (!d.diapazon_exist && count_str == 1) || (d.diapazon_exist && count_str == d.start);
    if (cur_mode == LINEDUP && in_diapazon(d, count_str)) {
        // печатать только 1ая строка или не повтор
        if (strcmp(pred_str, cur_str) != 0 || first_str_in_diapazon) {
            printf("%s", cur_str);
            if (cur_ch == '\n') putchar('\n');
        }
    }
    else { 
        printf("%s", cur_str);
        if (cur_ch == '\n') putchar('\n');
    }
    
    return;
}


void free_tree(struct tnode *p) {
    if (p != NULL) {
        free_tree(p->left);
        free_tree(p->right);

        while (p->positions != NULL) {
            struct position *next = p->positions->next;
            free(p->positions);
            p->positions = next;
        }

        free(p);
    }
}


struct tnode* find_node(struct tnode *p, char *word) {
    while (p != NULL) {
        if (strcmp(word, p->word) == 0)
            return p;
        else if (strcmp(word, p->word) < 0)
            p = p->left;
        else
            p = p->right;
    }

    return NULL;
}


void print_w(struct tnode *p, char *cur_word, struct diapazon d, 
            long long count_str, char *arg_w, int cur_ch, int flag_first_word_in_str) {
    
    if (!in_diapazon(d, count_str)) {
        printf("%s", cur_word);
        if (cur_ch != '\n' && cur_ch != EOF) putchar(cur_ch);
    }

    else {
        struct tnode* find = find_node(p, cur_word);
        //                                            посл вхождение было в текущ строке
        if (find && (strcmp(cur_word, arg_w) == 0) && find->positions->k_str == count_str)
            return;
        else {
            if (!flag_first_word_in_str) putchar(' ');
            printf("%s", cur_word);
            
        }
    }

    return;
}

int main(int argc, char **argv) {

    enum mode cur_mode;
    cur_mode = get_mode(argc, argv);
    if (cur_mode == ERROR) return 1;
    if (cur_mode == NOPE_MODE) return 1;

    int norm_arg_count = 2;
    struct diapazon d;
    d = get_diapazon(argc, argv);
    if (d.error == 1) return 1;

    if (d.diapazon_exist) norm_arg_count += 1 + d.k_params;
    if (cur_mode == WORDDUP) norm_arg_count += 2;
    if (cur_mode == LINEDUP) norm_arg_count += 1;
    if (argc != norm_arg_count) {
        fprintf(stderr, "Incorrect parameters of command line\n");
        return 1;
    }

    char *arg_w;
    if (cur_mode == WORDDUP) {
        arg_w = get_arg_after_worddup(argc, argv);
        if (!arg_w) {
            fprintf(stderr, "Incorrect parameters of command line\n");
            return 1;
        }
    }

    FILE *f = NULL;
    f = fopen(argv[1], "r");

    if (f == NULL) {
        fprintf(stderr, "Can't open file %s", argv[1]);
        return 1;
    }

    if (check_start_and_amount_of_strs(d, f) == 1) {
        fclose(f);
        return 1;
    }

    // читаем почарово
    int cur_ch;
    char cur_word[1001] = {0};
    char cur_str[1001] = {0};
    char pred_str[1001] = {0};
    int i = 0; // счетчик буквы в тек. словк
    int str_symb_i = 0;
    int count_word_in_str = 0;
    long long count_str = 1;
    int flag_first_word_in_str = 1;
    struct tnode *p = NULL;
    while (1) {
        if (str_symb_i > LEN_STR) {
            fprintf(stderr, "Unknown error");
            free_tree(p);
            fclose(f);
            return 1;
        }

        cur_ch = fgetc(f);

        // пустой файл
        if (cur_ch == EOF && str_symb_i == 0) break;

        if (cur_ch != '\n' && cur_ch != EOF) {
            cur_str[str_symb_i] = cur_ch;
            str_symb_i++;
        }

        if (cur_ch == '\n' || cur_ch == EOF) {
            cur_str[str_symb_i] = '\0';
            if (cur_mode == LINEDUP) 
                print_l(pred_str, cur_str, cur_mode, d, count_str, cur_ch);
            strcpy(pred_str, cur_str);
            str_symb_i = 0;
        }

        if (cur_ch == ' ' || cur_ch == '(' || cur_ch == ')' || cur_ch == '.' || cur_ch == ':' ||
            cur_ch == EOF || cur_ch == ';' || cur_ch == '-' || cur_ch == ',' || cur_ch == '\n') {
            cur_word[i] = '\0';

            if (strlen(cur_word) == 0) {
                if (cur_ch == EOF) {
                    break;
                }
                if (cur_ch == '\n') {
                    if (cur_mode == WORDDUP) printf("\n");
                    count_str++;
                    flag_first_word_in_str = 1;
                    count_word_in_str = 0;
                    continue;
                }

                if (cur_mode == WORDDUP && !in_diapazon(d, count_str)) printf("%c", cur_ch);
                continue;
            }

            count_word_in_str++;
            
            if (cur_mode == WORDDUP) {
                print_w(p, cur_word, d, count_str, arg_w, cur_ch, flag_first_word_in_str);
                flag_first_word_in_str = 0;
            }

            // + вершинка в дерево
            if (cur_mode == WORDDUP && in_diapazon(d, count_str))
                p = add_node(p, count_word_in_str, count_str, cur_word);

            i = 0;

            if (cur_ch == '\n' || cur_ch == EOF) {
                if (cur_mode == WORDDUP && cur_ch == '\n') printf("\n");
                count_str++;
                count_word_in_str = 0;
                flag_first_word_in_str = 1;
            }

            if (cur_ch == EOF) {
                break;
            }

            continue;
        }

        if (i > LEN_STR) {
            fprintf(stderr, "Unknown error");
            free_tree(p);
            fclose(f);
            return 1;
        }

        cur_word[i] = cur_ch;
        i++;
    }

    free_tree(p); 
    p = NULL; 
    fclose(f);
    return 0;
}