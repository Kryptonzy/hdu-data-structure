#include <stdio.h>

typedef struct stack
{
    int size;
    node * top;
    node * base;
}Stack;

typedef struct queue
{
    node * front;
    node * rear;
}Queue;

typedef struct node
{
    node * next;
    char data;
}node;

void input();
void complex();
void InitQueue(Queue * q);
void InitStack(Stack * s);
void EnQueue(Queue *q,char x);
int QIsEmpty(Queue *q);
int SIsEmpty(Queue *q);
void PushStack(Stack *s,char x);
void PopStack(Stack *s);
void DestoryQueue(Queue *q);
void DestoryStack(Stack *s);
void Destorynode(node * n);
void gettop(Stack s,char t);
void Printq(Queue *q);

void complex()
{
    Queue q;
    Stack s;
    InitQueue(&q);
    InitStack(&s);
    char x;
    char top;
    char theta;
    do
    {
        x=getchar();
        theta=x;
        EnQueue(&q,x);
    }while(QIsEmpty(&q));
    do
    {
        x=getchar();
        PushStack(&s,x);
    }while(x!=')');
    while(!SIsEmpty(&s))
    {
        gettop(s,top);
        EnQueue(&q,top);
        EnQueue(&q,theta);       
        PopStack(&s);
    }
    Printq(&q);
    DestoryStack(&s);
    DestoryQueue(&q);
}
void input()
{
    char x;
    do
    {
        x=getchar();
        if(x=='A')
        {
            printf("sae");
        }
        else if(x=='B')
        {
            printf("tsaedsae");
        }
        else if(x=='(')
        {
            complex();
        }
        else
        {
            printf("%c",x);
        }
    }
    while(x<='z'&&x>='A');
}
int main()
{
    input();
    return 0;
}
