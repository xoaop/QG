#ifndef QUEUE_H
#define QUEUE_H

typedef unsigned long long size_t;

//定义数据类型枚举
typedef enum Elemtype
{
    _INT=1,
    _DOUBLE=2,
    _STRING=3,
}Elemtype;

//定义栈节点
typedef struct QueueNode
{
    void* value;
    Elemtype type;
    QueueNode* next;
}QueueNode;


//定义栈
typedef struct Queue
{   
    QueueNode* queuehead;
    QueueNode* queuetail;
    int size;
} Queue;



//定义状态枚举
typedef enum Status 
{
	_ERROR,
	_SUCCESS,
    _OVERFLOW,
    _EXIST,
    _NULLPOINTER
} Status;

//函数声明
size_t queue_get_size_of_type(void* value,Elemtype type);
Status queue_get_value(QueueNode* node,void** output);
Status queue_push(Queue* queue,void* value,Elemtype type);
Status queue_pop(Queue* queue);
Status queue_pop(Queue* queue);
Status queue_init(Queue** queue);
Status queue_destroy(Queue** queue);
Status queue_get_top(Queue* queue,void** output);
int queue_get_size(Queue* queue);


#endif
