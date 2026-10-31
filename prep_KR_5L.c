// найти максимальную глубину дерева (литкод)

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


int maxDepth(struct TreeNode* root) {

    int max_deep = 0;
    if (root.val == NULL) {
        max_deep = maxDepth(root.left);
        max_deep = maxDepth(root.right);
    }

    return max_deep;
}