// реализация простейшего дерева через структуры

struct tnode{
    int k;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *add_node (struct tnode *p, int k){ 
    if (p == NULL){  
        p = (stuct*)malloc(sizeof(struct tnode))  
        p->k = k;  
        p->left = NULL;  
        p->right = NULL; 
    } 
    else if (k < (p->k))
        p->left = add_node(p->left, k); 
    else if (k > (p->k))
        p->right = add_node(p->right, k);  
    return p;
}