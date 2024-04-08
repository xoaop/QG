#include "../Headers/bst.h"
#include<stdlib.h>
#include "../Headers/stack.h"
#include "../Headers/queue.h"
#include "../Headers/status.h"


//create a binary search tree
void bst_create_bst(BST** bst)
{
    if (*bst != NULL)
    {
        return bst;
    }

    *bst = (BST *)malloc(sizeof(BST));
    (*bst)->root = NULL;
    return bst;
}

//destroy the binary search tree
void bst_destroy_tree(Treenode *root)
{
    if (root == NULL)
        return;
    bst_destroy_tree(root->left);
    bst_destroy_tree(root->right);
    free(root);
}

void bst_destroy_bst(BST **bst)
{   
    if(*bst == NULL)
    {
        return;
    }
    bst_destroy_tree((*bst)->root);
    free(*bst);
    *bst = NULL;
}


//insert a node
Treenode* bst_insertnode(Treenode* rootnode,Type data)
{
    if(rootnode == NULL)
    {
        Treenode* newnode = (Treenode*)malloc(sizeof(Treenode));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }

    if(data > rootnode->data)
    {
        rootnode->right = bst_insertnode(rootnode->right,data);
    }
    else if(data < rootnode->data)
    {
        rootnode->left = bst_insertnode(rootnode->left,data);
    }

    return rootnode;
}


//insert a node
void bst_insert(BST* bst, Type data)
{
    if(bst == NULL)
    {
        return NULL;
    }

    if(bst->root == NULL)
    {
        bst->root = (Treenode*)malloc(sizeof(Treenode));
        bst->root->data = data;
        bst->root->left = NULL;
        bst->root->right = NULL;
        return bst->root;
    }


    bst->root= bst_insertnode(bst->root, data);
}


void bst_inorder(Treenode* root,int* size)
{   

    if(root == NULL)
        return;
    bst_inorder(root->left,size);

    printf("%d ",root->data);
    (*size)++;
    
    bst_inorder(root->right,size);


}


void bst_inorder_travel(BST* bst,int* size)
{   
    if (bst == NULL)
    {
        return;
    }
    
    bst_inorder(bst->root,size);
}

void bst_inorder_nonrecursive(Treenode* root,int* size)
{   
    if(root == NULL)
        return ;

    Stack* stack = NULL;
    stack_init(&stack);

    Treenode* currentnode;
    void* current;

    stack_push(stack,&root,_POINTER);

    while(stack_get_size(stack)>0)
    {
        stack_get_top(stack,&current);
        stack_pop(stack);
        currentnode = *(Treenode**)current;

        while(currentnode != NULL)
        {
            stack_push(stack,&currentnode, _POINTER);
            currentnode = currentnode->left;
        }

        if(stack_get_size(stack)>0)
        {
            stack_get_top(stack,&current);
            stack_pop(stack);
            currentnode = *(Treenode**)current;

            printf("%d ",currentnode->data);
            (*size)++;

            currentnode = currentnode->right;
            stack_push(stack,&currentnode,_POINTER);
        }
    }
}


void bst_inorder_nonrecursive_travel(BST* bst,int* size)
{   
    if(bst == NULL)
    {
        return ;
    }

    bst_inorder_nonrecursive(bst->root,size);
}


void bst_preorder(Treenode* root,int* size)
{
    if(root == NULL)
        return ;

    printf("%d ",root->data);
    (*size)++;
    bst_preorder(root->left,size);
    bst_preorder(root->right,size);
}



void bst_preorder_travel(BST* bst,int* size)
{   
    if(bst == NULL)
    {
        return ;
    }

    bst_preorder(bst->root,size);
}


void bst_preorder_nonrecursive(Treenode* root,int* size)
{   
    if(root == NULL)
        return ;

    Stack* stack = NULL;
    stack_init(&stack);

    Treenode* currentnode =NULL;
    void* current;

    stack_push(stack,&root,_POINTER);

    while(stack_get_size(stack)>0)
    {
        stack_get_top(stack,&current);
        stack_pop(stack);
        currentnode = *(Treenode**)current;

        printf("%d ",currentnode->data);
        (*size)++;

        if(currentnode->right != NULL)
        {
            stack_push(stack,&(currentnode->right),_POINTER);
        }

        if(currentnode->left != NULL)
        {
            stack_push(stack,&(currentnode->left),_POINTER);
        }
    }

    stack_destroy(&stack);
}

void bst_preorder_nonrecursive_travel(BST* bst,int* size)
{   
    if(bst == NULL)
    {
        return ;
    }

    return bst_preorder_nonrecursive(bst->root,size);
}



void bst_postorder_nonrecursive(Treenode* root,int* size)
{   
    if(root == NULL)
        return ;

    Stack* stack = NULL;
    stack_init(&stack);

    Treenode* currentnode = NULL;
    void* current;

    Treenode* prevnode = NULL;

    stack_push(stack, &root, _POINTER);

    while (stack_get_size(stack) > 0) 
    {
        stack_get_top(stack, &current);
        currentnode = *(Treenode**)current;

        if (currentnode->left != NULL && currentnode->left != prevnode && currentnode->right != prevnode) 
        {
            stack_push(stack, &(currentnode->left), _POINTER);
        } else if (currentnode->right != NULL && currentnode->right != prevnode) 
        {
            stack_push(stack, &(currentnode->right), _POINTER);
        } else 
        {
            stack_pop(stack);
            printf("%d ", currentnode->data);
            (*size)++;
            prevnode = currentnode;
        }
    }

    stack_destroy(&stack);
}

void bst_postorder_nonrecursive_travel(BST* bst,int* size)
{   
    if(bst == NULL)
    {
        return;
    }

    bst_postorder_nonrecursive(bst->root,size);
}

Treenode* bst_search(Treenode* root,Type target)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (target > root->data)
    {
        return bst_search(root->right, target);
    }
    else if (target < root->data)
    {
        return bst_search(root->left, target);
    }
    else
    {
        return root;
    }
    

}


Treenode* bst_search_bst(BST* bst,Type target)
{   
    if(bst == NULL)
    {
        return NULL;
    }

    return bst_search(bst->root,target);
}

void bst_postorder(Treenode* root,int* size)
{
    if(root == NULL)
        return ;

    bst_postorder(root->left,size);
    bst_postorder(root->right,size);
    printf("%d ",root->data);
    (*size)++;
}

void bst_postorder_travel(BST* bst,int* size)
{   
    if(bst == NULL)
    {
        return;
    }

    bst_postorder(bst->root,size);
}

void bst_leverorder(Treenode* root, int* size)
{   
    if(root == NULL)
    {
        return;
    }

    Queue* queue = NULL;
    queue_init(&queue);

    void* current;

    queue_push(queue,&root,_POINTER);

    while(queue_get_size(queue)>0)
    {
        queue_get_head(queue,&current);
        queue_pop(queue);

        printf("%d ",(*(Treenode**)current)->data);
        (*size)++;

        if((*(Treenode**)current)->left != NULL)
        {
            queue_push(queue,&((*(Treenode**)current)->left),_POINTER);
        }

        if((*(Treenode**)current)->right != NULL)
        {
            queue_push(queue,&((*(Treenode**)current)->right),_POINTER);
        }
    }

    queue_destroy(&queue);

}

void bst_leverorder_travel(BST* bst,int* size)
{   
    if(bst == NULL)
    {
        return;
    }

    bst_leverorder(bst->root,size);
}


Treenode* bst_delete_node(Treenode* root,Type target)
{

    if(root == NULL)
    {
        return NULL;
    }


    if(target > root->data)
    {
        root->right = bst_delete_node(root->right,target);
    }
    else if(target < root->data)
    {
        root->left = bst_delete_node(root->left,target);
    }
    else//target==root->data
    {   
        //left is null or all is null
        if(root->left == NULL)
        {
            Treenode* temp = root->right;
            free(root);
            return temp;
        }
        //left is not null
        else if(root->right == NULL)
        {
            Treenode* temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            Treenode* temp = root->right;
            if(temp->left == NULL)
            {
                root->data = temp->data;
                root->right = temp->right;
                free(temp);
            }
            else
            {
                while(temp->left->left != NULL)
                {
                    temp = temp->left;
                }
                root->data = temp->left->data;
                Treenode* delNode = temp->left;
                temp->left = temp->left->right;
                free(delNode);
            }
        }
    }

    return root;
}


Treenode* bst_delete(BST* bst,Type target)
{   
    if(bst == NULL)
    {
        return NULL;
    }



    bst->root= bst_delete_node(bst->root,target);
    return bst->root;

}





