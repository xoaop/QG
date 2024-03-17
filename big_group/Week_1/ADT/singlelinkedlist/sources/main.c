#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<windows.h>

typedef int Elemtype;

//定义单向链表节点
typedef struct SingleListNode
{
    Elemtype data;
    SingleListNode* next;
}SingleListNode;

SingleListNode* create_node();
void mainloop();


int main()
{
    SetConsoleOutputCP(65001);
    mainloop();
}

//链表初始化
int init(SingleListNode** head,int data,int* length)
{   
    if(*head!=NULL)
    {
        return 0;
    }

    *head=create_node();
    (*head)->data=data;
    (*head)->next=NULL;
    *length=1;

    return 1;
}

int destroy(SingleListNode** head)
{
    SingleListNode* after=*head;
    SingleListNode* before=*head;

    while(after!=NULL)
    {   
        after=after->next;
        free(before);
        before=after;
    }

    *head=NULL;

    return 1;
}

//创建链表节点
SingleListNode* create_node()
{
    return (SingleListNode*)malloc(sizeof(SingleListNode));
}


//获取某位置的前节点
SingleListNode* before_node(SingleListNode** head,int index)
{   

    if(*head==NULL)
    {
        return NULL;
    }

    SingleListNode* temp=*head;
    for(int i=0;i<index-1;i++)
    {   
        if(temp->next==NULL)
            break;

        temp=temp->next;
    }

    return temp;
}


//插入新节点
int insert_node(SingleListNode** head,int* length,int index,Elemtype data)
{
    if(*head==NULL)
    {
        return 0;
    }

    if(index<0)
    {
        return 0;
    }

    SingleListNode* temp=before_node(head,index);

    SingleListNode* newnode=create_node();
    newnode->data=data;

    //插入
    if(index==0)
    {
        newnode->next=temp;
        *head=newnode;
    }
    else
    {
        newnode->next=temp->next;
        temp->next=newnode;
    }

    (*length)++;
    
    return 1;

}

//删除节点
int delete_node(SingleListNode** head,int* length,int index)
{
    if(*head==NULL)
    {
        return 0;
    }

    if(index<0||index>=*length)
    {
        return 0;
    }

    SingleListNode* temp=before_node(head,index);

    SingleListNode* deleted;

    if(index==0)
    {
        deleted=temp;
        temp=temp->next;
        *head=temp;
        free(deleted);
    }
    else
    {
        deleted=temp->next;
        temp->next=temp->next->next;
        free(deleted);
    }

    (*length)--;

    return 1;
}



//判断链表是否成环
int if_circle(SingleListNode** head)
{   
    if(*head==NULL)
    {
        return 0;
    }

    SingleListNode* slow=*head;
    SingleListNode* fast=slow->next;

    while(fast!=NULL&&fast->next!=NULL)
    {
        if(fast==slow)
        {
            return 1;
        }
        
        slow=slow->next;
        fast=fast->next->next;
    }

    return 2;
}

//使链表首尾相连
int make_circle(SingleListNode**head)
{   
    if(*head==NULL)
    {
        return 0;
    }
    if(if_circle(head)==1)
    {
        return 0;
    }

    SingleListNode* first=*head;
    SingleListNode* last=*head;
    while(last->next!=NULL)
    {
        last=last->next;
    }

    last->next=first;
    return 1;
}

//找到链表中点
SingleListNode* find_middle(SingleListNode** head)
{
    if(*head==NULL)
    {
        return 0;
    }

    SingleListNode* slow=*head;
    SingleListNode* fast=slow->next;

    while(fast!=NULL&&fast->next!=NULL)
    { 
        slow=slow->next;
        fast=fast->next->next;
    }

    return slow;
}

//单链表奇偶调换
int exchange_even_odd(SingleListNode** head)
{
    if(*head==NULL)
    {
        return 0;
    }

    SingleListNode* newhead;

    SingleListNode* odd=*head;
    SingleListNode* even=odd->next;

    SingleListNode* temp;
    SingleListNode* temp2;

    if(even==NULL)
        return 1;

    newhead=even;

    temp=even->next;
    even->next=odd;
    odd->next=temp;
    even=temp;

    while(even!=NULL&&even->next!=NULL)
    {   
        temp2=odd;
        odd=odd->next;
        even=even->next;

        temp=even->next;
        temp2->next=even;
        even->next=odd;
        odd->next=temp;
        even=temp;

    }

    *head=newhead;

    return 1;
}


//递归实现逆转链表
SingleListNode* reverse_recursion(SingleListNode* node)
{
    if(node->next==NULL)
    {
        return node;
    }

    SingleListNode* newhead=reverse_recursion(node->next);

    node->next->next=node;
    node->next=NULL;

    return newhead;

}

//非递归实现逆转链表
int reverse_not_recursion(SingleListNode** head)
{   
    if(*head==NULL)
    {
        return 0;
    }

    SingleListNode* before=NULL;
    SingleListNode* after=*head;
    SingleListNode* temp;

    while(after!=NULL)
    {
        temp=after->next;
        after->next=before;

        before=after;
        after=temp;
    }

    *head=before;

    return 1;
}

int search_DoubleLinkedList(SingleListNode** head,Elemtype target)
{   
    if(*head==NULL)
        return 0;

    SingleListNode* temp=*head;
    while(temp!=NULL)
    {
        if(temp->data==target)
            return 1;

        temp=temp->next;
    }

    return 0;
}

//遍历链表并显示;
void traverse_with_display(SingleListNode** head,int* length)
{   
    SingleListNode* truehead=*head;

    if(*head==NULL)
        return;
    
    SingleListNode* temp=*head;


    printf("\n\n");

    printf("%d->",temp->data);
    temp=temp->next;
    while(temp!=NULL&&temp!=truehead)
    {   
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("\n长度:%d\n",*length);

}


//主循环、菜单
void mainloop()
{   
    SingleListNode* head=NULL;
    int length=0;

    while (1)
    {   
        int result;
        int selection;

        traverse_with_display(&head,&length);

        //打印菜单
        printf("\n\n单向链表:\n\
        1.创建链表\n\
        2.销毁链表\n\
        3.向链表插入元素\n\
        4.删除链表元素\n\
        5.查找元素\n\
        6.使链表首尾相连(相连后不能再次使用该命令,也不能插入或删除或查找)\n\
        7.判断链表是否成环\n\
        8.奇偶调换(链表不能成环)\n\
        9.找到中点(链表不能成环)\n\
        10.逆转链表(非递归)(链表不能成环)\n\
        11.逆转链表(递归)((链表不能成环))\n\
        12.退出\n\
        输入对应编号(1-12):\n");

        scanf("%d",&selection);

        system("cls");

        if(selection==1)
        {   
            printf("输入第一个节点的值:\n");
            Elemtype val;
            scanf("%d",&val);

            result=init(&head,val,&length);
            if(result==1)
            {
                printf("创建成功\n");
            }
            else if(result==0)
            {
                printf("链表已存在\n");
            }
        }
        else if(selection==2)
        {
            result=destroy(&head);
            
            printf("销毁成功\n");

        }
        else if(selection==3)
        {   
            int index;
            Elemtype data;
            printf("输入想要插入的位置下标(以0为起点(类似数组)):\n");
            scanf("%d",&index);
            printf("输入想要插入的节点的值:\n");
            scanf("%d",&data);

            result=insert_node(&head,&length,index,data);
            if(result==1)
            {
                printf("\n插入成功\n");
            }
            else if(result==0)
            {
                printf("\n插入失败,下标越界或链表不存在\n");
            }

        }
        else if(selection==4)
        {
            int index;
            printf("输入想要删除的位置下标(类似数组):\n");
            scanf("%d",&index);

            result=delete_node(&head,&length,index);
            if(result==1)
            {
                printf("\n删除成功\n");
            }
            else if(result==0)
            {
                printf("\n删除失败,下标越界或链表不存在\n");
            }

        }
        else if(selection==5)
        {
            Elemtype data;
            printf("输入想要查找的元素:\n");
            scanf("%d",&data);

            result=search_DoubleLinkedList(&head,data);
            if(result==1)
            {
                printf("\n该元素存在\n");
            }
            else if(result==0)
            {
                printf("\n该元素不存在\n");
            }
        }
        else if (selection==6)
        {
            result=make_circle(&head);

            if(result==1)
            {
                printf("\n首尾已相连");
            }
            else
            {
                printf("\n链表未创建或已经相连过");
            }
        }
        else if (selection==7)
        {
            result=if_circle(&head);

            if(result==1)
            {
                printf("\n成环");
            }
            else
            {
                printf("\n不成环");
            }
        }
        else if (selection==8)
        {
            result=exchange_even_odd(&head);

            if(result==1)
            {
                printf("\n已调换");
            }
            else
            {
                printf("\n链表未创建");
            }
        }
        else if (selection==9)
        {
            SingleListNode* mid=find_middle(&head);

            if(result==1)
            {
                printf("\n已找到,中点值为%d",mid->data);
            }
            else
            {
                printf("\n链表未创建");
            }
        }
        else if (selection==10)
        {
            if(head==NULL)
            {
                printf("\n链表未创建");
                continue;
            }
            
            head=reverse_recursion(head);
            printf("\n已逆转");
                

        }
        else if (selection==11)
        {
            result=reverse_not_recursion(&head);

            if(result==1)
            {
                printf("\n已逆转");
            }
            else
            {
                printf("\n链表未创建");
            }
        }
        else if(selection==12)
        {
            break;
        }


    }

}









