
#include "status.h"

#ifndef STACK_H
#define STACK_H




//定义栈节点
typedef struct StackNode
{
    void* value;
    Elemtype type;
    struct StackNode* next;
} StackNode;


//定义栈
typedef struct Stack
{
    StackNode* stacktop;
    int size;
} Stack;




//函数声明
size_t stack_get_size_of_type(void* value,Elemtype type);
Status stack_get_value(StackNode* node,void** output);
Status stack_push(Stack* stack,void* value,Elemtype type);
Status stack_pop(Stack* stack);
Status stack_init(Stack** stack);
Status stack_destroy(Stack** stack);
Status stack_get_top(Stack* stack,void** output);
int stack_get_size(Stack* stack);


#endif
