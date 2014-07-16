typedef struct Node {
    char val;
    struct Node* next;
} Node;

typedef struct TreeNode {
    char* value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Tree {
    int size;
    TreeNode* root;
} Tree;
