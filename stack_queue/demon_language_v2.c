#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    struct node * next;
    char data;
}node;

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



void input(Queue * res);
void complex(Queue*q);
node * newnode();
void InitQueue(Queue * q);
void InitStack(Stack * s);
void EnQueue(Queue *q,char x);
int QIsEmpty(Queue *q);
int SIsEmpty(Stack *s);
void PushStack(Stack *s,char x);
void PopStack(Stack *s);
void DestoryQueue(Queue *q);
void DestoryStack(Stack *s);
void Printq(Queue *q);
void Input();

void normalize(Queue *res,Queue *q,char *x,int n);

void InitQueue(Queue * q)
{
    q->front=q->rear=NULL;
}
void InitStack(Stack * s)
{
    s->size=0;
    s->base=s->top=NULL;
}
void EnQueue(Queue *q,char x)
{
    node * n =newnode();
    n->data=x;
    if(q->front==NULL)
    {
        q->front=q->rear=n;
    }
    else
    {
        q->rear->next=n;
        q->rear=n;
    }
}
int QIsEmpty(Queue *q)
{
    if(q->front==NULL)
    {
        return 1;
    }
    return 0;
}
int SIsEmpty(Stack *s)
{
    if(s->size==0||s->base==NULL)
    {
        return 1;
    }
    return 0;
}
void PushStack(Stack *s,char x)
{
    node *n=newnode();
    n->data=x;
    if(SIsEmpty(s))
    {
        s->base=s->top=n;
        s->size++;
    }
    else
    {
        s->top->next=n;
        s->top=n;
        s->size++;
    }
    // printf("top=%c\n",s->top->data);
}
void PopStack(Stack *s)
{
    node *q=s->base;
    node *p=s->top;
    if(s->size==1)
    {
        free(q);
        s->base=s->top=NULL;
    }
    else
    {
        for(int i=0;i<s->size-2;i++)
        {
            q=q->next;
        }
        //q指向top下面一个节点
        q->next=NULL;
        free(p);
        s->top=q;
    }
    s->size--;
}
node * newnode()
{
    node *a;
    a = (node*)malloc(sizeof(node));
    a->data=0;
    a->next =NULL;
    return a;
}
void DestoryQueue(Queue *q)
{
    node *n;
    while(!QIsEmpty(q))
    {
        n=q->front;
        q->front=q->front->next;
        free(n);
    }
}
void DestoryStack(Stack *s)
{
    node *n;
    while(!SIsEmpty(s))
    {
        n=s->base;
        s->base=s->base->next;
        free(n);
        s->size--;
    }
}
void Printq(Queue *q)
{
    node *n;
    n=q->front;
    while(n!=q->rear->next)
    {
        char x;
        x=n->data;
        printf("%c",x);
        n=n->next;
    }
}
void complex(Queue *q)
{
    Stack s;
    InitStack(&s);
    char x;
    char top;
    char theta;
    x=getchar();
    theta=x;
    EnQueue(q,x);
    do
    {
        x=getchar();
        if(x!=')')
        PushStack(&s,x);
        // printf("\nsize=%d  top=%c",s.size,s.top->data);
    }while(x!=')');
    while(!SIsEmpty(&s))
    {
        top=s.top->data;
        EnQueue(q,top);
        // printf("\nrear=%c",q.rear->data); 
        EnQueue(q,theta);
        // printf("\nsize=%d  top=%c",s.size,s.top->data);       
        PopStack(&s);
    }
    // Printq(&q);
    DestoryStack(&s);
}
void input(Queue * res)
{
    char x;
    do
    {
        x=getchar();
        if(x=='(')
        complex(res);
        else
        EnQueue(res,x);
    }
    while(x<='z'&&x>='A'||x=='(');
}

void normalize(Queue *res,Queue *q,char *x,int n)
{
    node *m3,*m2,*m1;

    // printf("res=\n");
    // Printq(res);
    // for(int i=0;i<n;i++)
    // {
    //     printf("q[%d]=\n",i);
    //     Printq(&q[i]);
    // }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            m2=res->front;
            while(m2!=NULL)
            {
                if(m2->data==x[j])
                {
                    m3=m2->next;
                    m1=q[j].front;
                    m2->data=m1->data;
                    m1=m1->next;
                    while(m1!=NULL)
                    {
                        node *New;
                        New =newnode();
                        New->data=m1->data;
                        m2->next=New;
                        New->next=m3;
                        m1=m1->next;
                        m2=m2->next;
                    }
                }
                m2=m2->next;
            }
        }
    }
}
void Input()
{
    int n;
    printf("你要输入几条规则？");
    scanf("%d",&n);
    char x[n];
    char a;
    a=getchar();
    Queue q[n],res;
    InitQueue(&res);
    for(int i=0;i<n;i++)
    InitQueue(&q[i]);
    for(int i=0;i<n;i++)
    {
        x[i]=getchar();
        a=getchar();
        printf("->\n");
        a=getchar();
        while(a<='z'&&a>='A')
        {
            EnQueue(&q[i],a);
            a=getchar();
        }
        // printf("\n");
        // Printq(&q[i]);
    }
    input(&res);
    normalize(&res,q,x,n);
    Printq(&res);
    DestoryQueue(&res);
    for(int i=0;i<n;i++)
    {
        DestoryQueue(&q[i]);
    }
}

int main()
{
    Input();
    return 0;
}
