#ifndef LL_H
#define LL_H

#include <cstdio>
#include <cstdlib>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
template<typename T_LL> struct LinkNode_LL {
	T_LL data;
	struct LinkNode_LL<T_LL>* prev;
	struct LinkNode_LL<T_LL>* next;
};
template<typename T_LL> struct LinkList {
	struct LinkNode_LL<T_LL>* head;
	struct LinkNode_LL<T_LL>* tail;
	int length;
};

template<typename T_LL> Status Init_LL(LinkList<T_LL>& L);
template<typename T_LL> void Destroy_LL(LinkList<T_LL>& L);
template<typename T_LL> Status GetElem_LL(LinkList<T_LL>& L, int i, T_LL& e);
template<typename T_LL> LinkNode_LL<T_LL>* Search_LL(LinkList<T_LL>& L, T_LL x);
template<typename T_LL> LinkNode_LL<T_LL>* LocatePos_LL(LinkList<T_LL> L, int i);
template<typename T_LL> LinkNode_LL<T_LL>* LocateElem_LL(LinkList<T_LL> L, T_LL x, int(*compare)(T_LL, T_LL));
template<typename T_LL> void Traverse_LL(LinkList<T_LL> L, Status(*visit)(T_LL));
template<typename T_LL> bool Empty_LL(LinkList<T_LL>& L);
template<typename T_LL> void Clear_LL(LinkList<T_LL>& L);
template<typename T_LL> Status Insert_LL(LinkList<T_LL>& L, LinkNode_LL<typename T_LL>* pos, T_LL x);
template<typename T_LL> Status InsertIth_LL(LinkList<T_LL>& L, int i, T_LL x);
template<typename T_LL> Status Delete_LL(LinkList<T_LL>& L, LinkNode_LL<typename T_LL>* pos, T_LL& e);
template<typename T_LL> Status DeleteIth_LL(LinkList<T_LL>& L, int i, T_LL& e);

template<typename T_LL> Status Init_LL(LinkList<T_LL>& L) {
	L.head = L.tail = (LinkNode_LL<T_LL>*)malloc(sizeof(LinkNode_LL<T_LL>));
	if (!L.head) {
		fputs("´æ´¢·ÖÅäÊ§°Ü£¡", stderr);
		return ERROR;
	}

	L.head->next = L.head->prev = NULL;
	L.length = 0;

	return OK;
}

template<typename T_LL> Status GetElem_LL(LinkList<T_LL>& L, int i, T_LL& e) {
	LinkNode_LL* p = L.head->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}

	if (!p || j > i)
		return ERROR;
	e = p->data;
	return OK;
}

template<typename T_LL> LinkNode_LL<typename T_LL>* Search_LL(LinkList<T_LL>& L, T_LL x) {
	LinkNode_LL* p = L.head->next;
	while (p && p->data != x)
		p = p->next;
	return p;
}

template<typename T_LL> Status InsertIth_LL(LinkList<T_LL>& L, int i, T_LL x) {
	LinkNode_LL<T_LL>* p = L.head;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		j++;
	}

	if (!p || j > i)
		return ERROR;
	return Insert_LL(L, p, x);
}

template<typename T_LL> Status DeleteIth_LL(LinkList<T_LL>& L, int i, T_LL& e) {
	LinkNode_LL<T_LL>* p = L.head;
	int j = 0;
	while (p && j < i) {
		p = p->next;
		j++;
	}

	if (!p || j > i)
		return ERROR;
	return Delete_LL(L, p, e);
}

template<typename T_LL> bool Empty_LL(LinkList<T_LL>& L) {
	return !L.head->next;
}

template<typename T_LL> void Destroy_LL(LinkList<T_LL>& L) {
	Clear_LL(L);

	free(L.head);
}

template<typename T_LL> void Clear_LL(LinkList<T_LL>& L) {
	LinkNode_LL<T_LL>* p = L.head->next, *q;

	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	L.head->next = NULL;
	L.tail = L.head;
	L.length = 0;
}

template<typename T_LL> Status Insert_LL(LinkList<T_LL>& L, LinkNode_LL<typename T_LL>* pos, T_LL x) {
	LinkNode_LL<T_LL>* s = (LinkNode_LL<T_LL>*)malloc(sizeof(LinkNode_LL<T_LL>));
	if (!s) {
		fputs("²åÈëÊ§°Ü£¡", stderr);
		exit(OVERFLOW);
	}

	s->data = x;
	s->prev = pos;
	s->next = pos->next;
	pos->next = s;
	if (s->next)
		s->next->prev = s;
	if (pos == L.tail)
		L.tail = pos->next;
	L.length++;

	return OK;
}

template<typename T_LL> Status Delete_LL(LinkList<T_LL>& L, LinkNode_LL<typename T_LL>* pos, T_LL& e) {
	if (pos == L.tail)
		L.tail = L.tail->prev;
	if (pos->next)
		pos->next->prev = pos->prev;
	pos->prev->next = pos->next;
	e = pos->data;
	free(pos);
	L.length--;

	return OK;
}

template<typename T_LL> LinkNode_LL<typename T_LL>* LocatePos_LL(LinkList<T_LL> L, int i) {
	LinkNode_LL<T_LL>* p = L.head;
	for (int j = 1; p && j <= i; j++)
		p = p->next;
	return p;
}

template<typename T_LL> LinkNode_LL<typename T_LL>* LocateElem_LL(LinkList<T_LL> L, T_LL x, int(*compare)(T_LL, T_LL)) {
	LinkNode_LL<T_LL>* p;
	for (p = L.head->next; p; p = p->next)
		if (compare(x, p->data))
			break;
	return p;
}

template<typename T_LL> void Traverse_LL(LinkList<T_LL> L, Status(*visit)(T_LL)) {
	for (LinkNode_LL<T_LL>* p = L.head->next; p; p = p->next)
		visit(p->data);
}

#endif // !LL_H