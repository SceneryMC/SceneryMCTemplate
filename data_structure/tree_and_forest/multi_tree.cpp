#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define SPACING "    "

typedef struct multitree {
	int height;
	char data;
	struct multitree* left_child;
	struct multitree* right_sibling;
}MultiNode, * MultiTree;
typedef int Status;
typedef MultiTree DataType_LQ;
typedef struct node {
	DataType_LQ data;
	struct node* prev;
	struct node* next;
}LinkNode, * LinkList;
typedef struct {
	LinkList head;
	LinkList tail;
	int length;
}LinkQueueSet;

void Create_MT(MultiTree L);
void PostTraverse_MT(MultiTree L, void (*visit)(MultiTree L));
void PreTraverse_MT(MultiTree t, void (*visit)(MultiTree L));
Status Init_LQ(LinkQueueSet& L);
bool Empty_LQ(LinkQueueSet& L);
Status Enqueue_LQ(LinkQueueSet& L, DataType_LQ x);
Status Dequeue_LQ(LinkQueueSet& L, DataType_LQ& e);

int main(void) {
	freopen("test.in", "r", stdin);

	MultiTree root = (MultiTree)malloc(sizeof(MultiNode));
	root->left_child = NULL;
	Create_MT(root);

	return 0;
}

void Create_MT(MultiTree L) {
	static bool return_from_child = false;
	static int depth = 0;
	static bool flag = false;
	char c, s;

	while (!flag) {
		switch (c = getchar()) {
		case '(':
			s = getchar();
			for (int i = 1; i <= depth; i++)
				printf(SPACING);
			if (s != ')')
				printf("%c\n", s);
			else {
				flag = true;
				break;
			}

			depth++;
			if (!return_from_child) {
				L->left_child = (MultiTree)malloc(sizeof(MultiNode));
				L->left_child->left_child = L->left_child->right_sibling = NULL;
				L->left_child->data = s;
				Create_MT(L->left_child);
			}
			else {
				L->right_sibling = (MultiTree)malloc(sizeof(MultiNode));
				L->right_sibling->left_child = L->right_sibling->right_sibling = NULL;
				L->right_sibling->data = s;
				L = L->right_sibling;
				return_from_child = false;
			}

			break;
		case ')':
			depth--;
			if (!return_from_child)
				return_from_child = true;
			else
				return;
			break;
		case EOF:
		case '\n':flag = true;
		}
	}
}

void PostTraverse_MT(MultiTree T, void (*visit)(MultiTree L)) {
	if (T->left_child)
		PostTraverse_MT(T->left_child, visit);

	while (T) {
		visit(T);
		T = T->right_sibling;
	}
}

void PreTraverse_MT(MultiTree T, void (*visit)(MultiTree L)) {
	if (!T)
		return;

	visit(T);
	MultiTree p = T->left_child;
	while (p) {
		PreTraverse_MT(p, visit);
		p = p->right_sibling;
	}
}

void LevelTraverse_MT(MultiTree T, void (*visit)(MultiTree L)) {
	if (!T)
		return;

	LinkQueueSet Q;
	Init_LQ(Q);
	Enqueue_LQ(Q, T);

	MultiTree p;
	while (!Empty_LQ(Q)) {
		Dequeue_LQ(Q, p);
		visit(p);
		p = p->left_child;
		while (p) {
			Enqueue_LQ(Q, p);
			p = p->right_sibling;
		}
	}
}

Status Init_LQ(LinkQueueSet& L) {
	L.head = L.tail = (LinkList)malloc(sizeof(LinkNode));
	if (!L.head) {
		puts("存储分配失败！");
		return ERROR;
	}

	L.head->next = L.head->prev = NULL;
	L.length = 0;

	return OK;
}

Status Enqueue_LQ(LinkQueueSet& L, DataType_LQ x) {
	LinkList s = (LinkList)malloc(sizeof(LinkNode));
	if (!s) {
		puts("插入失败！");
		exit(OVERFLOW);
	}

	s->data = x;
	s->prev = L.tail;
	s->next = NULL;
	L.tail->next = s;
	L.tail = L.tail->next;
	L.length++;

	return OK;
}

Status Dequeue_LQ(LinkQueueSet& L, DataType_LQ& e) {
	if (L.length == 0)
		return ERROR;

	LinkList p = L.head->next;
	if (L.tail == p)
		L.tail = L.head;
	L.head->next = p->next;
	if (L.head->next)
		L.head->next->prev = L.head;
	e = p->data;
	free(p);
	L.length--;
	return OK;
}

bool Empty_LQ(LinkQueueSet& L) {
	return !L.length;
}