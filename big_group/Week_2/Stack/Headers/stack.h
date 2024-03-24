#ifndef STACK_H
#define STACK_H

typedef unsigned long long size_t;

//定义数据类型枚举
typedef enum Elemtype
{
    _INT=1,
    _DOUBLE=2,
    _STRING=3,
}Elemtype;

//定义栈节点
typedef struct StackNode
{
    void* value;
    Elemtype type;
    StackNode* next;
}StackNode;


//定义栈
typedef struct Stack
{
    StackNode* stacktop;
    int size;
} Stack;



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
size_t get_size_of_type(void* value,Elemtype type);
Status get_value(StackNode* node,void** output);
Status stack_push(Stack* stack,void* value,Elemtype type);
Status stack_pop(Stack* stack);
Status stack_pop(Stack* stack);
Status stack_init(Stack** stack);
Status stack_destroy(Stack** stack);
Status stack_get_top(Stack* stack,void** output);
int stack_get_size(Stack* stack);


#endif
