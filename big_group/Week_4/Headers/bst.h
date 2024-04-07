#ifndef BST_H
#define BST_H

#define FIRSTMALLOCSIZE 50
#define MALLOCINCREMENT 10
#define ZERO 0
// Define the type of element in the tree
typedef int Type;


// Define the structure of the tree node
typedef struct treenode 
{
    Type data;
    struct treenode *left;
    struct treenode *right;
} Treenode;

// Define the structure of the tree
typedef struct bst 
{
    Treenode* root;
} BST;


// Function declaration
void bst_create_bst(BST** bst);
void bst_destroy_tree(Treenode *root);
void bst_destroy_bst(BST **bst);
Treenode* bst_insertnode(Treenode* rootnode,Type data);
void bst_insert(BST* bst, Type data);
void bst_inorder(Treenode* root,int* size);
void bst_inorder_travel(BST* bst,int* size);
void bst_inorder_nonrecursive(Treenode* root,int* size);
void bst_inorder_nonrecursive_travel(BST* bst,int* size);
void bst_preorder(Treenode* root,int* size);
void bst_preorder_travel(BST* bst,int* size);
void bst_preorder_nonrecursive(Treenode* root,int* size);
void bst_preorder_nonrecursive_travel(BST* bst,int* size);
void bst_postorder(Treenode* root,int* size);
void bst_postorder_travel(BST* bst,int* size);
void bst_postorder_nonrecursive(Treenode* root,int* size);
void bst_postorder_nonrecursive_travel(BST* bst,int* size);
Treenode* bst_search(Treenode* root,Type target);
Treenode* bst_search_bst(BST* bst,Type target);
void bst_leverorder(Treenode* root, int* size);
void bst_leverorder_travel(BST* bst,int* size);
Treenode* bst_delete_node(Treenode* root,Type target);
Treenode* bst_delete(BST* bst,Type target);



#endif