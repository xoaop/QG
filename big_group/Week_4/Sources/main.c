#include<stdio.h>
#include<stdlib.h>
#include "../Headers/bst.h"
#include "../Headers/stack.h"
#include "../Headers/queue.h"
#include "../Headers/status.h"

void menu()
{   
    int choice;
    BST* bst=NULL;

    while(1)
    {
    

        printf("1. Create a binary search tree\n");
        printf("2. Destroy the tree\n");
        printf("3. Insert a node\n");
        printf("4. Inorder traversal\n");
        printf("5. Preorder traversal\n");
        printf("6. Postorder traversal\n");
        printf("7. Levelorder traversal\n");
        printf("8. Inorder traversal without recursion\n");
        printf("9. Preorder traversal without recursion\n");
        printf("10. Postorder traversal without recursion\n");
        printf("11. Search a node\n");
        printf("12. Delete a node\n");
        printf("13. Exit\n");
        printf("Please enter your choice:");

        scanf("%d",&choice);

        fflush(stdin);
        system("cls");

        switch(choice)
        {
            case 1:
            {
                bst_create_bst(&bst);
                if(bst==NULL)
                {
                    printf("Failed to create a binary search tree\n");
                }
                else
                {
                    printf("Successfully created a binary search tree\n");
                }
                continue;
            }
            case 2:
            {
                bst_destroy_bst(&bst);
                if(bst==NULL)
                {
                    printf("Successfully destroyed the binary search tree\n");
                }
                else
                {
                    printf("Failed to destroy the binary search tree\n");
                }
                continue;
            }
                
            case 3:
            {
                Type data;
                printf("Please enter the data:");
                scanf("%d",&data);
                fflush(stdin);

                if(bst==NULL)
                {
                    printf("The binary search tree is not created\n");
                    continue;
                }

                bst_insert(bst,data);
                printf("Successfully inserted a node\n");
                
                continue;
            }
            
            case 4:
            {
                int size=0;
                
                if(bst==NULL)
                {
                    printf("The binary search tree is empty\n");
                    continue;
                }

                printf("Inorder traversal:\n");
                bst_inorder_travel(bst,&size);
                printf("\n");
                printf("size:%d\n",size);
                continue;

            }

            case 5:
            {
                int size=0;
                if(bst==NULL)
                {
                    printf("The binary search tree is empty\n");
                    continue;
                }

                printf("Preorder traversal:\n");
                bst_preorder_travel(bst,&size);
                printf("\n");
                printf("size:%d\n",size);
                continue;
            }            
            case 6:
            {
                int size=0;
                if(bst==NULL)
                {
                    printf("The binary search tree is empty\n");
                    continue;
                }

                printf("Postorder traversal:\n");
                bst_postorder_travel(bst,&size);
                printf("\n");
                printf("size:%d\n",size);
                continue;
            }
            case 7:
            {
                int size=0;
                if(bst==NULL)
                {
                    printf("The binary search tree is empty\n");
                    continue;
                }

                printf("Levelorder traversal:\n");
                bst_leverorder_travel(bst,&size);
                printf("\n");
                printf("size:%d\n",size);
                continue;
            }
            case 8:
            {
                int size=0;
                if(bst==NULL)
                {
                    printf("The binary search tree is empty\n");
                    continue;
                }

                printf("Inorder traversal without recursion:\n");
                bst_inorder_nonrecursive_travel(bst,&size);
                printf("\n");
                printf("size:%d\n",size);
                continue;



            }
            
            case 9:
            {
                int size=0;
                if(bst==NULL)
                {
                    printf("The binary search tree is empty\n");
                    continue;
                }

                printf("Preorder traversal without recursion:\n");
                bst_preorder_nonrecursive_travel(bst,&size);
                printf("\n");
                printf("size:%d\n",size);
                continue;
            }
            
            case 10:
            {
                int size=0;
                if(bst==NULL)
                {
                    printf("The binary search tree is empty\n");
                    continue;
                }

                printf("Postorder traversal without recursion:\n");
                bst_postorder_nonrecursive_travel(bst,&size);
                printf("\n");
                printf("size:%d\n",size);
                continue;
            }
            
            case 11:
            {
                Type target;
                printf("Please enter the target:");
                scanf("%d",&target);
                fflush(stdin);

                Treenode* node=bst_search_bst(bst,target);
                if(node==NULL)
                {
                    printf("Failed to search the node\n");
                }
                else
                {
                    printf("Successfully searched the node\n");
                }
                continue;
            }
            
            case 12:
            {
                Type target;
                printf("Please enter the target:");
                scanf("%d",&target);
                fflush(stdin);

                bst_delete(bst, target);
                printf("Successfully deleted the node\n");

                continue;

            }
            
            case 13:
            {
                return;
            }
            
            default:
            {
                printf("Invalid choice\n");
                continue;
            }
            
        }

        printf("\n\n");
    }
    
}

int main()
{   

    menu();
    return 0;
}