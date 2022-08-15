#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

void _InThreading(ThreadTree p, ThreadTree& pre);
void InThreading(ThreadTree T);
void Traverse_TT(ThreadTree T, void (*visit)(ThreadTree e));
ThreadNode* firstNode(ThreadTree T);
ThreadNode* Succ(ThreadNode* p);

typedef enum { Link, Thread } PointerThr;
typedef int DataType_TT;
typedef struct ThreadNode {
	DataType_TT data;
	struct ThreadNode* lchild, * rchild;
	PointerThr LTag, RTag;
} ThreadNode, * ThreadTree;

void Traverse_TT(ThreadTree T, void (*visit)(ThreadTree e)) {
	for (ThreadTree p = firstNode(T); p; p = Succ(p))
		visit(p);
}

ThreadNode* firstNode(ThreadTree T) {
	if (!T)
		return NULL;

	ThreadTree p = T;
	while (p->LTag == Link)
		p = p->lchild;
	return p;
}

ThreadNode* Succ(ThreadNode* p) {
	if (!p)
		return NULL;

	if (p->RTag == Thread)
		return p->rchild;
	return firstNode(p->rchild);
}

void _InThreading(ThreadTree p, ThreadTree & pre){
	if (!p)
		return;

	_InThreading(p->lchild, pre);
	if (p->lchild)
		p->LTag = Link;
	else {
		p->LTag = Thread;
		p->lchild = pre;
	}
	if (pre) {
		if (pre->rchild)
			pre->RTag = Link;
		else {
			pre->RTag = Thread;
			pre->rchild = p;
		}
	}
	pre = p;
	_InThreading(p->rchild, pre);
}

void InThreading(ThreadTree T) {
	if (!T)
		return;

	ThreadTree pre = NULL;
	_InThreading(T, pre);
	pre->RTag = Thread; 
}