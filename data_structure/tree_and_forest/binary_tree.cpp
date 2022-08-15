#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define STATIC_MAX_SIZE 1000

typedef int Status;
typedef int DataType_BT;
typedef struct BiTNode {
    DataType_BT data;
    struct BiTNode* lchild, *rchild;
} BiTNode, * BiTree;
typedef BiTree DataType_SQ;
typedef struct {
    DataType_SQ data[STATIC_MAX_SIZE + 1];
    int front;
    int rear;
    int max_size;
}SeqQueue;

void DSCreate_BT(BiTree& T, char pre[], char ino[], int ps, int is, int n);
void SSCreate_BT(BiTree& T, char pre[]);
int CountLeaf_BT(BiTree T);
int Depth_BT(BiTree T);
void PreTraverse_BT(BiTree T, void(*visit)(DataType_BT& e));
void InTraverse_BT(BiTree T, void(*visit)(DataType_BT& e));
void PostTraverse_BT(BiTree T, void(*visit)(DataType_BT& e));
void LevelTraverse_BT(BiTree T, void(*visit)(DataType_BT& e));
void Init_SQ(SeqQueue& L);
bool Empty_SQ(SeqQueue& L);
Status Enqueue_SQ(SeqQueue& L, DataType_SQ x);
Status Dequeue_SQ(SeqQueue& L, DataType_SQ& e);

void PreTraverse_BT(BiTree T, void(*visit)(DataType_BT& e)){
    if (T) {
        visit(T->data);
        PreTraverse_BT(T->lchild, visit);
        PreTraverse_BT(T->rchild, visit);
    }
}

void InTraverse_BT(BiTree T, void(*visit)(DataType_BT& e)) {
    if (T) {
        InTraverse_BT(T->lchild, visit);
        visit(T->data);
        InTraverse_BT(T->rchild, visit);
    }
}

void PostTraverse_BT(BiTree T, void(*visit)(DataType_BT& e)) {
    if (T) {
        PostTraverse_BT(T->lchild, visit);
        PostTraverse_BT(T->rchild, visit);
        visit(T->data);
    }
}

void LevelTraverse_BT(BiTree T, void(*visit)(DataType_BT& e)) {
    static SeqQueue Q;
    Init_SQ(Q);
    BiTree p = T;

    Enqueue_SQ(Q, p);
    while (!Empty_SQ(Q)) {
        Dequeue_SQ(Q, p); 
        visit(p->data);
        if (p->lchild != NULL) 
            Enqueue_SQ(Q, p->lchild);
        if (p->rchild != NULL)
            Enqueue_SQ(Q, p->rchild);
    }
}

int CountLeaf_BT(BiTree T) {
    if (!T)
        return 0;
    if ((!T->lchild) && (!T->rchild))
        return 1;
    return CountLeaf_BT(T->lchild) + CountLeaf_BT(T->rchild);
} 

int Depth_BT(BiTree T) {
    if (!T)
        return 0;

    int depthLeft = Depth_BT(T->lchild);
    int depthRight = Depth_BT(T->rchild);
    return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
}

void SSCreate_BT(BiTree &T, char pre[]) {
    static int n;
    char ch = pre[n++];
    if (ch == ';') {
        n = 0;
        return;
    }

    if (ch == '#') 
        T = NULL;
    else {
        if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        T->data = ch;
        SSCreate_BT(T->lchild, pre);
        SSCreate_BT(T->rchild, pre);
    }
}

void DSCreate_BT(BiTree& T, char pre[], char ino[], int ps, int is, int n) {
    if (n == 0)
        T = NULL;
    else {
        int k = strchr(ino, pre[ps]) - ino;

        if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);

        T->data = pre[ps];
        DSCreate_BT(T->lchild, pre, ino, ps + 1, is, k - is);
        DSCreate_BT(T->rchild, pre, ino, ps + 1 + (k - is), k + 1, n - (k - is) - 1);
    }
}

Status Enqueue_SQ(SeqQueue& L, DataType_SQ x) {
    if (L.front == (L.rear + 1) % L.max_size) {
        puts("队列已满！");
        exit(OVERFLOW);
    }

    L.data[L.rear] = x;
    L.rear = (L.rear + 1) % L.max_size;

    return OK;
}

Status Dequeue_SQ(SeqQueue& L, DataType_SQ& e) {
    if (L.front == L.rear)
        return ERROR;

    e = L.data[L.front];
    L.front = (L.front + 1) % L.max_size;
    return OK;
}

void Init_SQ(SeqQueue& L) {
    L.front = L.rear = 0;
    L.max_size = STATIC_MAX_SIZE + 1;
}

bool Empty_SQ(SeqQueue& L) {
    return L.front == L.rear;
}