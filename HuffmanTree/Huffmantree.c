#include <stdio.h>
typedef struct BTNode
{
    struct BTNode * lchild, * rchild;
    char data;
    float power;
}BTNode;


void Initbinarytree(BTNode * T);
void Destorybinarytree(BTNode * T);
void Createybinarytree(BTNode * T,char ch[],int p[]);
void Clearbinarytree(BTNode * T);
int Isempty(BTNode *  T);
int BinarytreeDepth(BTNode * T);
BTNode *Locate(BTNode *T,char e);
BTNode *Parent(BTNode *T);
BTNode *Leftchild(BTNode *T,char  e);
BTNode *Rightchild(BTNode *T,char  e);
BTNode *Leftsibling(BTNode *T,BTNode * p);
BTNode *Rightsibling(BTNode *T,BTNode * p);
BTNode *Copybinarytree(BTNode *T);
void Countleaf(BTNode *T,int  n);
void Preordertraverse(BTNode *T,void(*visit)(char  e));
void Inordertraverse(BTNode *T,void(*visit)(char  e));
void Postordertraverse(BTNode *T,void(*visit)(char  e));

void Initbinarytree(BTNode * T)
{
    T=NULL;
}

void Destorybinarytree(BTNode * T)
{
    if(T)
    {
        Destorybinarytree(T->lchild);
        Destorybinarytree(T->rchild);
        free(T);
    }
    T=NULL;
}

void Createbinarytree(BTNode* T,char ch[],int p[])
{

}

int main()
{


    return 0;
}