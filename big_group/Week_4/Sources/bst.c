#include "../Headers/bst.h"
#include<stdlib.h>
#include "../Headers/stack.h"
#include "../Headers/queue.h"
#include "../Headers/status.h"



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
    Stack *stack = NULL;
    stack_init(&stack);

    Treenode* current = root;

    stack_push(stack,current,_POINTER);

    while(stack_get_size(stack)>0)
    {
        stack_get_top(stack,&current);
        stack_pop(stack);

        while(current != NULL)
        {
            stack_push(stack,&current,_POINTER);

            current = current->left;
        }

        if(stack_get_size(stack)>0)
        {
            stack_get_top(stack,&current);
            stack_pop(stack);

            printf("%d ",current->data);
            (*size)++;

            current = current->right;
            stack_push(stack,&current,_POINTER);
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
    Stack* stack = NULL;
    stack_init(&stack);

    Treenode* current = root;

    stack_push(stack,current,_POINTER);

    while(stack_get_size(stack)>0)
    {
        stack_get_top(stack,&current);
        stack_pop(stack);

        printf("%d ",current->data);
        (*size)++;

        if(current->right != NULL)
        {
            stack_push(stack,&(current->right),_POINTER);
        }

        if(current->left != NULL)
        {
            stack_push(stack,&(current->left),_POINTER);
        }
    }
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
    Stack* stack = NULL;
    stack_init(&stack);

    Treenode* current = root;
    Treenode* lastvisited = NULL;

    stack_push(stack,current,_POINTER);

    while(stack_get_size(stack)>0)
    {
        stack_get_top(stack,&current);
        if(lastvisited == NULL || lastvisited->left == current || lastvisited->right == current)
        {
            if(current->left != NULL)
            {
                stack_push(stack,&(current->left),_POINTER);
            }
            else if(current->right != NULL)
            {
                stack_push(stack,&(current->right),_POINTER);
            }
        }
        else if(current->left == lastvisited)
        {
            if(current->right != NULL)
            {
                stack_push(stack,&(current->right),_POINTER);
            }
        }
        else
        {
            printf("%d ",current->data);
            (*size)++;
            stack_pop(stack);
        }

        lastvisited = current;
    }
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
    if(root==NULL)
    {
        return NULL;
    }

    if(target>root->data)
    {
        return bst_search(root->right,target);
    }
    else if(target<root->data)
    {
        return bst_search(root->left,target);
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

    return bst_search(bst,target);
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
    Queue* queue = NULL;
    queue_init(&queue);

    Treenode* current;

    queue_push(queue,root,_POINTER);

    while(queue_get_size(queue)>0)
    {
        queue_get_head(queue,&current);
        queue_pop(queue);

        printf("%d ",current->data);
        (*size)++;

        if(current->left != NULL)
        {
            queue_push(queue,current->left,_POINTER);
        }

        if(current->right != NULL)
        {
            queue_push(queue,current->right,_POINTER);
        }
    }

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
    else
    {
        if(root->left == NULL)
        {
            Treenode* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL)
        {
            Treenode* temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            Treenode* temp = root->right;
            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = bst_delete_node(root->right,temp->data);
            
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

    return bst_delete_node(bst->root,target);
}





