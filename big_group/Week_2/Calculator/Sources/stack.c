#include"../Headers/stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

//获取相应类型的数据的大小
size_t stack_get_size_of_type(void* value,Elemtype type)
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
}

//获取栈节点元素
Status stack_get_value(StackNode* node,void** output)
{   
    if(node==NULL)
    {
        return _NULLPOINTER;
    }

    size_t valuesize=stack_get_size_of_type(node->value,node->type);
    *output=malloc(stack_get_size_of_type(node->value,node->type));
    memcpy(*output,node->value,valuesize);
    return _SUCCESS;
}


//入栈
Status stack_push(Stack* stack,void* value,Elemtype type)
{
    if(stack==NULL)
    {
        return _NULLPOINTER;
    }

    StackNode* newnode=(StackNode*)malloc(sizeof(StackNode));
    newnode->type=type;

    size_t valuesize=stack_get_size_of_type(value,type);
    newnode->value=malloc(valuesize);
    
    memcpy(newnode->value,value,valuesize);

    if(stack->stacktop==NULL)
    {   
        newnode->next=NULL;
        stack->stacktop=newnode;
    }
    else
    {   
        newnode->next=stack->stacktop;
        stack->stacktop=newnode;
    }

    stack->size++;

    return _SUCCESS;

}

//出栈
Status stack_pop(Stack* stack)
{
    if(stack==NULL)
    {
        return _NULLPOINTER;
    }

    if(stack->size==0)
    {
        return _ERROR;
    }

    StackNode* poped=stack->stacktop;
    stack->stacktop=stack->stacktop->next;

    free(poped->value);
    free(poped);
    stack->size--;

    if (stack->size == 0)
    {
        stack->stacktop = NULL;
    }

    return _SUCCESS;
}


//初始化栈
Status stack_init(Stack** stack)
{   
    if(*stack!=NULL)
    {
        return _EXIST;
    }

    *stack=(Stack*)malloc(sizeof(Stack));
    (*stack)->size=0;
    (*stack)->stacktop=NULL;

    return _SUCCESS;

}

//销毁栈
Status stack_destroy(Stack** stack)
{   
    if(*stack==NULL)
    {
        return _NULLPOINTER;
    }

    for(StackNode* front=(*stack)->stacktop,*behind=front;front!=NULL;)
    {
        front=front->next;
        free(behind);
        behind=front;
    }

    free(*stack);
    *stack=NULL;

    return _SUCCESS;

}

//获取栈顶元素
Status stack_get_top(Stack* stack,void** output)
{   
    if(stack==NULL)
    {
        return _NULLPOINTER;
    }

    if(stack->size==0)
    {
        return _ERROR;
    }

    stack_get_value(stack->stacktop,output);

    return _SUCCESS;
}

//获取栈大小
int stack_get_size(Stack* stack)
{
    if(stack==NULL)
    {
        return 0;
    }

    return stack->size;
}   
