#include<stdio.h>
#include<malloc.h>
#include"../Headers/list.h"
#include<stdlib.h>
#include<windows.h>

void mainloop();

int main()
{   
    SetConsoleOutputCP(65001);
    mainloop();
}



Status init_DoubleLinkedList(DoubleLinkedList** DLLp)
{   
    if(!*DLLp)
    {
        *DLLp=(DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
        (*DLLp)->length=0;
        (*DLLp)->head=create_node_DoubleLinkedList();
        (*DLLp)->head->data=0;
        (*DLLp)->head->next=NULL;
        (*DLLp)->head->previous=NULL;
    }
    else
    {
        return EXIST;
    }

    if(*DLLp)
    {
        return SUCCESS;
    }
    else
    {
        return ERR;
    }
}

//销毁链表
Status destroy_DoubleLinkedList(DoubleLinkedList** DLLp)
{   
    if(*DLLp==NULL)
    {
        return ERR;
    }

    DoubleLinkedListNode* temp=(*DLLp)->head;

    while(temp->next!=NULL)
    {
        temp=temp->next;
        free(temp->previous);
    }
    free(temp);

    free(*DLLp);

    *DLLp=NULL;

    return SUCCESS;
}

//创建链表节点
DoubleLinkedListNode* create_node_DoubleLinkedList()
{
    return (DoubleLinkedListNode*)malloc(sizeof(DoubleLinkedListNode));
}

//获取链表对应下标的节点
Status getnode_DoubleLinkedList(DoubleLinkedList** DLLp,DoubleLinkedListNode** result,int index)
{   

    if(index>(*DLLp)->length||index<0)
    {
        return OUTOFBOUND;
    }

    DoubleLinkedListNode* temp=(*DLLp)->head;

    int cnt=index;
    while(cnt>0)
    {
        temp=temp->next;
        cnt--;
    }

    *result=temp;

    return SUCCESS;

}


//插入节点到链表
Status insert_DoubleLinkedList(DoubleLinkedList** DLLp,int index,Elemtype data)
{   
    if(*DLLp==NULL)
    {
        return ERR;
    }

    DoubleLinkedListNode* temp;

    Status result=getnode_DoubleLinkedList(DLLp,&temp,index);

    if(result==OUTOFBOUND)
        return result;

    DoubleLinkedListNode* newnode=create_node_DoubleLinkedList();

    newnode->data=data;
    

    if(index==0)
    {   
        newnode->next=temp;
        newnode->previous=NULL;
        temp->previous=newnode;
        (*DLLp)->head=newnode;
    }
    else
    {   
        newnode->previous=temp->previous;
        newnode->next=temp;
        temp->previous->next=newnode;
        temp->previous=newnode;

    }


    (*DLLp)->length++;

    return SUCCESS;

}

//删除链表节点
Status delete_node_DoubleLinkedList(DoubleLinkedList** DLLp,int index)
{   
    if(*DLLp==NULL)
        return ERR;

    if(index>=(*DLLp)->length||index<0)
        return OUTOFBOUND;

    DoubleLinkedListNode* temp;

    getnode_DoubleLinkedList(DLLp,&temp,index);
    
    if(index==0)
    {
        (*DLLp)->head=temp->next;
        (*DLLp)->head->previous=NULL;
        free(temp);
    }
    else
    {
        temp->previous->next=temp->next;
        temp->next->previous=temp->previous;
        free(temp);
    }

    (*DLLp)->length--;

    return SUCCESS;
}

//查找链表是否存在目标值
Status search_DoubleLinkedList(DoubleLinkedList** DLLp,Elemtype target)
{   
    if(*DLLp==NULL)
        return ERR;

    DoubleLinkedListNode* temp=(*DLLp)->head;
    while(temp->next!=NULL)
    {
        if(temp->data==target)
            return SUCCESS;

        temp=temp->next;
    }

    return ERR;
}

//遍历链表并显示;
void traverse_with_display_DoubleLinkedList(DoubleLinkedList** DLLp)
{   
    if(*DLLp==NULL)
        return;

    if((*DLLp)->head==NULL)
        return;
    
    DoubleLinkedListNode* temp=(*DLLp)->head;


    printf("\n\n");
    while(temp->next!=NULL)
    {   
        printf("%d<->",temp->data);
        temp=temp->next;
    }
    printf("nullptr\n");
    printf("长度:%d\n",(*DLLp)->length);

}

//主循环
void mainloop()
{   
    DoubleLinkedList* DLL=NULL;

    while (1)
    {
        Status result;
        int selection;

        traverse_with_display_DoubleLinkedList(&DLL);

        //打印菜单
        printf("\n\n双向链表:\n\
        1.创建链表\n\
        2.销毁链表\n\
        3.向链表插入元素\n\
        4.删除链表元素\n\
        5.查找元素\n\
        6.退出\n\
        输入对应编号(1-5):\n");

        scanf("%d",&selection);

        system("cls");

        if(selection==1)
        {   
            result=init_DoubleLinkedList(&DLL);
            if(result==SUCCESS)
            {
                printf("创建成功\n");
            }
            else if(result==EXIST)
            {
                printf("链表已存在\n");
            }
            else if(result==ERR)
            {
                printf("创建失败\n");
            }
        }
        else if(selection==2)
        {
            result=destroy_DoubleLinkedList(&DLL);
            if(result==SUCCESS)
            {
                printf("销毁成功\n");
            }
            else if(result==ERR)
            {
                printf("销毁失败\n");
            }
        }
        else if(selection==3)
        {   
            int index;
            Elemtype data;
            printf("输入想要插入的位置下标(以0为起点(类似数组)):\n");
            scanf("%d",&index);
            printf("输入想要插入的节点的值:\n");
            scanf("%d",&data);

            result=insert_DoubleLinkedList(&DLL,index,data);
            if(result==SUCCESS)
            {
                printf("\n插入成功成功\n");
            }
            else if(result==ERR)
            {
                printf("\n插入失败\n");
            }
            else if(result==OUTOFBOUND)
            {
                printf("\n下标越界\n");
            }
        }
        else if(selection==4)
        {
            int index;
            printf("输入想要删除的位置下标(类似数组):\n");
            scanf("%d",&index);

            result=delete_node_DoubleLinkedList(&DLL,index);
            if(result==SUCCESS)
            {
                printf("\n删除成功\n");
            }
            else if(result==ERR)
            {
                printf("\n删除失败\n");
            }
            else if(result==OUTOFBOUND)
            {
                printf("\n下标越界\n");
            }
        }
        else if(selection==5)
        {
            int data;
            printf("输入想要查找的元素:\n");
            scanf("%d",&data);

            result=search_DoubleLinkedList(&DLL,data);
            if(result==SUCCESS)
            {
                printf("\n该元素存在\n");
            }
            else if(result==ERR)
            {
                printf("\n该元素不存在\n");
            }
        }
        else if (selection==6)
        {
            break;
        }

    }

}
