//该头文件定义了链表

#ifndef LIST_H
#define LIST_H

#define Elemtype int

//定义状态枚举
typedef enum Status 
{
	ERR,
	SUCCESS,
    OVERFLOW,
    EXIST,
    OUTOFBOUND,
} Status;

//定义双向链表节点
typedef struct DoubleLinkedListNode
{
    Elemtype data;
    DoubleLinkedListNode* previous;
    DoubleLinkedListNode* next;
} DoubleLinkedListNode;

//定义双向链表
typedef struct DoubleLinkedList
{
    int length;
    DoubleLinkedListNode* head;
} DoubleLinkedList;




Status init_DoubleLinkedList(DoubleLinkedList** DLL);
Status destroy_DoubleLinkedList(DoubleLinkedList** DLLp);
DoubleLinkedListNode* create_node_DoubleLinkedList();
Status insert_DoubleLinkedList(DoubleLinkedList** DLLp,int index,Elemtype data);
Status getnode_DoubleLinkedList(DoubleLinkedList** DLLp,DoubleLinkedListNode** result,int index);
Status delete_node_DoubleLinkedList(DoubleLinkedList** DLLp,int index);
Status search_DoubleLinkedList(DoubleLinkedList** DLLp,Elemtype target);
void traverse_with_display_DoubleLinkedList(DoubleLinkedList** DLLp);





#endif






