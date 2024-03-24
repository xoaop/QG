#include"../Headers/queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

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

//菜单
int main()
{   
    SetConsoleOutputCP(65001);

    Queue *queue=NULL;

    Status result;
    int selection;

    while (1)
    {


        //打印菜单
        printf("\n\n队列:\n\
        1.创建队列\n\
        2.销毁队列\n\
        3.向队列推入元素\n\
        4.弹出队列头元素\n\
        5.获取队列头元素\n\
        6.获取队列当前元素数量\n\
        7.退出\n\
        输入对应编号(1-7):\n");

        scanf("%d",&selection);

        system("cls");

        if(selection==1)
        {   
            result=queue_init(&queue);
            if(result==_SUCCESS)
            {
                printf("\n创建成功");
            }
            else if(result==_EXIST)
            {
                printf("\n队列已存在");
            }
        }
        else if(selection==2)
        {
            result=queue_destroy(&queue);
            if(result==_SUCCESS)
            {
                printf("\n销毁成功");
            }
            else if(result==_NULLPOINTER)
            {
                printf("\n队列未创建");
            }
        }
        else if(selection==3)
        {   
            Elemtype tp;
            int ip1;
            double ip2;
            char ip3[1000];

            printf("\n输入想要入队列的数据的类型(输入1为int类型,2为double类型,3为字符串(char*)(大小不超过999)类型):\n");
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
                    result=queue_push(queue,&ip1,tp);
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
                    result=queue_push(queue,&ip2,tp);
                }

            }
            else if(tp==_STRING)
            {
                if(!scanf("%999s",&ip3))
                {
                    printf("\n输入数据与类型不匹配");
                    fflush(stdin);
                    continue;
                }
                else
                {
                    result=queue_push(queue,ip3,tp);
                }

            }

            
            if(result==_SUCCESS)
            {
                printf("\n数据推入成功");
            }
            else if(result==_NULLPOINTER)
            {
                printf("\n队列未创建");
            }

        }
        else if(selection==4)
        {
            result=queue_pop(queue);
            if(result==_SUCCESS)
            {
                printf("\n弹出成功");
            }
            else if(result==_NULLPOINTER)
            {
                printf("\n队列未创建");
            }
            else if (result==_ERROR)
            {
                printf("\n队列为空");
            }
            

        }
        else if(selection==5)
        {   
            if(queue==NULL)
            {
                printf("\n队列未创建");
                continue;
            }
            if(queue->size==0)
            {
                printf("\n队列为空");
                continue;
            }

            void* op;

            result=queue_get_head(queue,&op);

            if(result==_SUCCESS)
            {
                if(queue->queuehead->type==_INT)
                {
                    printf("\n队列顶元素为:%d",*(int*)op);
                }
                else if(queue->queuehead->type==_DOUBLE)
                {
                    printf("\n队列顶元素为:%lf",*(double*)op);
                }
                else if(queue->queuehead->type==_STRING)
                {
                    printf("\n队列顶元素为:%s",(char*)op);
                }
            }
            else if (result==_ERROR)
            {
                printf("\n队列为空");
            }

            free(op);
            
        }
        else if (selection==6)
        {
            printf("\n元素数量为:%d",queue_get_size(queue));
        }
        else if (selection==7)
        {
            break;
        }

    }

}