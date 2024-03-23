
#ifndef STACK_H
#define STACK_H

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


#endif
