#include"../Headers/stack.h"
#include"../Headers/queue.h"
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

int priority[48];



//清空字符串里的空格及换行符
Status clearspace(char* input)
{
    for(char* input_ptr=input,*output_ptr=input;*input_ptr!='\0';)
    {
        if(*input_ptr!=' '&&*input_ptr!='\n')
        {
            *output_ptr=*input_ptr;
            output_ptr++;
        }
        
        input_ptr++;

        if(*input_ptr=='\0')
        {
            *output_ptr='\0';
        }
    }

    return _SUCCESS;

}

//将输入的算式进行解析，并入队列
Status parse(char* input,Queue* queue)
{
    clearspace(input);

    char* ptr=input;

    int consumed=0;

    double buffer;

    while (*ptr!='\0')
    {
        if(*ptr!='+'&&*ptr!='-'&&*ptr!='*'&&*ptr!='/'&&*ptr!='('&&*ptr!=')')
        {
            if(sscanf(ptr,"%lf%n",&buffer,&consumed)==0)
            {
                return _ERROR;
            }
            else
            {
                queue_push(queue,&buffer,_DOUBLE);
            }
            ptr+=consumed;

        }
        else
        {
            queue_push(queue,ptr,_CHAR);
            ptr++;
        }
    }

    return _SUCCESS;
    

}

//中缀表达式转后缀表达式
Status tramsform(Stack* stack,Queue* queue1,Queue* queue2)
{
    while (queue1->size != 0)
    {   
        //数字直接入栈
        if (queue1->queuehead->type == _DOUBLE)
        {
            queue_push(queue2, queue1->queuehead->value, queue1->queuehead->type);
            queue_pop(queue1);
        }
        else//非数字情况
        {   
            //非右括号
            if (*(char*)(queue1->queuehead->value )!= ')')
            {
                if (*(char*)(queue1->queuehead->value) == '(')//左括号直接入栈
                {
                    stack_push(stack, queue1->queuehead->value, queue1->queuehead->type);
                    queue_pop(queue1);
                }
                else //非括号
                {
                    while (stack->size != 0 && *(char*)stack->stacktop->value !='(' &&( priority[*(char*)(queue1->queuehead->value)] <= priority[*(char*)(stack->stacktop->value)]))
                    {
                        queue_push(queue2, stack->stacktop->value, stack->stacktop->type);
                        stack_pop(stack);
                    }

                    stack_push(stack, queue1->queuehead->value, queue1->queuehead->type);
                    queue_pop(queue1);
                }
            }
            else//右括号
            {
                while (stack->size!=0&&*(char*)(stack->stacktop->value) != '(')
                {   
                   

                    queue_push(queue2, stack->stacktop->value, stack->stacktop->type);
                    stack_pop(stack);


                }

                if (stack->size == 0)
                {
                    return _ERROR;
                }

                stack_pop(stack);
                queue_pop(queue1);

            }
        }
    }

    while (stack->size != 0)
    {
        queue_push(queue2, stack->stacktop->value, stack->stacktop->type);
        stack_pop(stack);
    }

    return _SUCCESS;
}

//计算后缀表达式
Status compute(Queue* queue, Stack* stack)
{
    while (queue->size != 0)
    {
        if (queue->queuehead->type == _DOUBLE)
        {
            stack_push(stack, queue->queuehead->value, queue->queuehead->type);
            queue_pop(queue);
        }
        else
        {
            if (stack->size < 2)
            {
                return _ERROR;
            }
            else
            {
                double right=*(double*)(stack->stacktop->value);
                stack_pop(stack);
                double left= *(double*)(stack->stacktop->value);
                stack_pop(stack);

                double ans = 0;
                if (*(char*)(queue->queuehead->value) == '+')
                {
                    ans = left + right;
                }
                else if (*(char*)(queue->queuehead->value) == '-')
                {
                    ans = left - right;
                }
                else if (*(char*)(queue->queuehead->value) == '*')
                {
                    ans = left * right;
                }
                else if (*(char*)(queue->queuehead->value) == '/')
                {
                    ans = left / right;
                }
                stack_push(stack, &ans, _DOUBLE);
                
            }

            queue_pop(queue);
        }

    }


    return _SUCCESS;
}



int main()
{   
    SetConsoleOutputCP(65001);

    priority[43] = 1;
    priority[45] = 1;
    priority[42] = 2;
    priority[47] = 2;
    priority[40] = 3;

    Status result;

    while (1)
    {


        Stack* stack = NULL;
        Queue* queue1 = NULL;
        Queue* queue2 = NULL;

        stack_init(&stack);
        queue_init(&queue1);
        queue_init(&queue2);

        char input[1000];

        printf("\n输入正确格式的算式(输入回车退出):\n");
        fgets(input, sizeof(input), stdin);

        if(input[0]=='\n')
        {
            break;
        }



        fflush(stdin);

        result = parse(input, queue1);
        if (result == _ERROR)
        {
            printf("\n输入格式有误");
            continue;
        }
        result=tramsform(stack, queue1, queue2);
        if (result == _ERROR)
        {
            printf("\n输入格式有误");
            continue;
        }
         compute(queue2, stack);
        if (result == _ERROR)
        {
            printf("\n输入格式有误");
            continue;
        }

        printf("\n%lf", *(double*)(stack->stacktop->value));


    }



}






    






