#include"../Headers/queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define get_value(type,value) (*((type)*)(value))

//获取相应类型的数据的大小
size_t queue_get_size_of_type(void* value,Elemtype type)
{
    if(type==_INT)
    {
        return sizeof(int);
    }
    else if(type==_DOUBLE)
    {
        return sizeof(double);
    }
    else if(type==_STRING)
    {
        return strlen((char*)value)+1;
    }
    else if(type==_CHAR)
    {
        return sizeof(char);
    }
    else if(type==_POINTER)
    {
        return sizeof(void*);
    }
    else 
    {
        return 0;
    }

}

//获取队列节点元素
Status queue_get_value(QueueNode* node,void** output)
{   
    if(node==NULL)
    {
        return _NULLPOINTER;
    }

    size_t valuesize=queue_get_size_of_type(node->value,node->type);
    *output=malloc(queue_get_size_of_type(node->value,node->type));
    memcpy(*output,node->value,valuesize);
    return _SUCCESS;
}


//入队列
Status queue_push(Queue* queue,void* value,Elemtype type)
{
    if(queue==NULL)
    {
        return _NULLPOINTER;
    }

    QueueNode* newnode=(QueueNode*)malloc(sizeof(QueueNode));
    newnode->type=type;

    size_t valuesize=queue_get_size_of_type(value,type);
    newnode->value=malloc(valuesize);
    newnode->next=NULL;
    
    memcpy(newnode->value,value,valuesize);

    if(queue->queuehead==NULL)
    {   
        queue->queuehead=newnode;
        queue->queuetail=newnode;
    }
    else
    {   
        queue->queuetail->next=newnode;
        queue->queuetail = newnode;
    }

    queue->size++;

    return _SUCCESS;

}

//出队
Status queue_pop(Queue* queue)
{
    if(queue==NULL)
    {
        return _NULLPOINTER;
    }

    if(queue->size==0)
    {
        return _ERROR;
    }

    QueueNode* poped=queue->queuehead;
    queue->queuehead=queue->queuehead->next;


    free(poped->value);
    free(poped);
    queue->size--;

    if(queue->size==0)
    {
        queue->queuetail=NULL;
    }

    return _SUCCESS;
}


//初始化队列
Status queue_init(Queue** queue)
{   
    if(*queue!=NULL)
    {
        return _EXIST;
    }

    *queue=(Queue*)malloc(sizeof(Queue));
    (*queue)->size=0;
    (*queue)->queuehead=NULL;
    (*queue)->queuetail=NULL;

    return _SUCCESS;

}

//销毁队列
Status queue_destroy(Queue** queue)
{   
    if(*queue==NULL)
    {
        return _NULLPOINTER;
    }

    for(QueueNode* front=(*queue)->queuehead,*behind=front;front!=NULL;)
    {
        front=front->next;
        free(behind);
        behind=front;
    }

    free(*queue);
    *queue=NULL;

    return _SUCCESS;

}

//获取队列头元素
Status queue_get_head(Queue* queue,void** output)
{   
    if(queue==NULL)
    {
        return _NULLPOINTER;
    }

    if(queue->size==0)
    {
        return _ERROR;
    }

    queue_get_value(queue->queuehead,output);

    return _SUCCESS;
}

//获取队列大小
int queue_get_size(Queue* queue)
{
    if(queue==NULL)
    {
        return 0;
    }

    return queue->size;
}   