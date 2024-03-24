#include "status.h"
#ifndef QUEUE_H
#define QUEUE_H


//定义队列节点
typedef struct QueueNode
{
    void* value;
    Elemtype type;
    struct QueueNode* next;
} QueueNode;


//定义队列
typedef struct Queue
{   
    QueueNode* queuehead;
    QueueNode* queuetail;
    int size;
} Queue;


//函数声明
size_t queue_get_size_of_type(void* value,Elemtype type);
Status queue_get_value(QueueNode* node,void** output);
Status queue_push(Queue* queue,void* value,Elemtype type);
Status queue_pop(Queue* queue);
Status queue_init(Queue** queue);
Status queue_destroy(Queue** queue);
Status queue_get_head(Queue* queue,void** output);
int queue_get_size(Queue* queue);


#endif
