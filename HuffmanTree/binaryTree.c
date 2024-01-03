#include <stdio.h>
typedef struct BTNode
{
    struct BTNode * lchild, * rchild;
    char data;
    float power;
}BTNode;

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