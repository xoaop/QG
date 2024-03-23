#include"../Headers/stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

//获取相应类型的数据的大小
size_t get_size_of_type(void* value,Elemtype type)
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
}

//获取栈节点元素
Status get_value(StackNode* node,void* output)
{   
    if(node==NULL)
    {
        return _NULLPOINTER;
    }

    size_t valuesize=get_size_of_type(node->value,node->type);
    memcpy(output,node->value,valuesize);
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

    size_t valuesize=get_size_of_type(value,type);
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
    free(poped);
    stack->size--;

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
Status stack_get_top(Stack* stack,void* output)
{   
    if(stack==NULL)
    {
        return _NULLPOINTER;
    }

    if(stack->size==0)
    {
        return _ERROR;
    }

    get_value(stack->stacktop,output);

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

//菜单
int main()
{   
    SetConsoleOutputCP(65001);

    Stack *stack=NULL;

    Status result;
    int selection;

    while (1)
    {


        //打印菜单
        printf("\n\n栈:\n\
        1.创建栈\n\
        2.销毁栈\n\
        3.向栈推入元素\n\
        4.弹出栈顶元素\n\
        5.获取栈顶元素\n\
        6.获取栈当前元素数量\n\
        7.退出\n\
        输入对应编号(1-7):\n");

        scanf("%d",&selection);

        system("cls");

        if(selection==1)
        {   
            result=stack_init(&stack);
            if(result==_SUCCESS)
            {
                printf("\n创建成功");
            }
            else if(result==_EXIST)
            {
                printf("\n栈已存在");
            }
        }
        else if(selection==2)
        {
            result=stack_destroy(&stack);
            if(result==_SUCCESS)
            {
                printf("\n销毁成功");
            }
            else if(result==_NULLPOINTER)
            {
                printf("\n栈未创建");
            }
        }
        else if(selection==3)
        {   
            Elemtype tp;
            int ip1;
            double ip2;
            char ip3[1000];

            printf("\n输入想要入栈的数据的类型(输入1为int类型,2为double类型,3为字符串(char*)类型):\n");
            scanf("%d",&tp);
            fflush(stdin);

            if(tp>3||tp<1)
            {
                printf("\n输入错误");
                continue;
            }
            
            printf("\n输入数据:\n");
            
            if(tp==_INT)
            {
                if(!scanf("%d",&ip1))
                {
                    printf("\n输入数据与类型不匹配");
                    fflush(stdin);
                    continue;
                }
                else
                {
                    result=stack_push(stack,&ip1,tp);
                }
            }
            else if(tp==_DOUBLE)
            {
                if(!scanf("%lf",&ip2))
                {
                    printf("\n输入数据与类型不匹配");
                    fflush(stdin);
                    continue;
                }
                else
                {
                    result=stack_push(stack,&ip2,tp);
                }

            }
            else if(tp==_STRING)
            {
                if(!scanf("%s",&ip3))
                {
                    printf("\n输入数据与类型不匹配");
                    fflush(stdin);
                    continue;
                }
                else
                {
                    result=stack_push(stack,ip3,tp);
                }

            }

            
            if(result==_SUCCESS)
            {
                printf("\n数据推入成功");
            }
            else if(result==_NULLPOINTER)
            {
                printf("\n栈未创建");
            }

        }
        else if(selection==4)
        {
            result=stack_pop(stack);
            if(result==_SUCCESS)
            {
                printf("\n弹出成功");
            }
            else if(result==_NULLPOINTER)
            {
                printf("\n栈未创建");
            }
            else if (result==_ERROR)
            {
                printf("\n栈为空");
            }
            

        }
        else if(selection==5)
        {   
            if(stack==NULL)
            {
                printf("\n栈未创建");
                continue;
            }
            if(stack->size==0)
            {
                printf("\n栈为空");
                continue;
            }

            void* op=malloc(get_size_of_type(stack->stacktop->value,stack->stacktop->type));

            result=stack_get_top(stack,op);
            if(result==_SUCCESS)
            {
                if(stack->stacktop->type==_INT)
                {
                    printf("\n栈顶元素为:%d",*(int*)op);
                }
                else if(stack->stacktop->type==_DOUBLE)
                {
                    printf("\n栈顶元素为:%lf",*(double*)op);
                }
                else if(stack->stacktop->type==_STRING)
                {
                    printf("\n栈顶元素为:%s",(char*)op);
                }
            }
            else if (result==_ERROR)
            {
                printf("\n栈为空");
            }
            
        }
        else if (selection==6)
        {
            printf("\n元素数量为:%d",stack_get_size(stack));
        }
        else if (selection==7)
        {
            break;
        }

    }

}