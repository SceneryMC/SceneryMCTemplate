#ifndef LQ_H
#define LQ_H

#include <cstdio>
#include <cstdlib>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
template<typename T_LQ> struct LinkNode_LQ {
	T_LQ data;
	struct LinkNode_LQ<T_LQ>* next;
};
template<typename T_LQ> struct LinkQueue {
	struct LinkNode_LQ<T_LQ>* front;
	struct LinkNode_LQ<T_LQ>* back;
	int length;
};

template<typename T_LQ> Status Init_LQ(LinkQueue<T_LQ>& L);
template<typename T_LQ> void Destroy_LQ(LinkQueue<T_LQ>& L);
template<typename T_LQ> bool Empty_LQ(LinkQueue<T_LQ>& L);
template<typename T_LQ> Status GetFront_LQ(LinkQueue<T_LQ>& L, T_LQ& e);
template<typename T_LQ> void Clear_LQ(LinkQueue<T_LQ>& L);
template<typename T_LQ> Status Enqueue_LQ(LinkQueue<T_LQ>& L, T_LQ x);
template<typename T_LQ> Status Dequeue_LQ(LinkQueue<T_LQ>& L, T_LQ& e);

template<typename T_LQ> Status Init_LQ(LinkQueue<T_LQ>& L) {
	L.front = L.back = (LinkNode_LQ<T_LQ>*)malloc(sizeof(LinkNode_LQ<T_LQ>));
	if (!L.front) {
		fputs("´æ´¢·ÖÅäÊ§°Ü£¡", stderr);
		return ERROR;
	}

	L.front->next = NULL;
	L.length = 0;

	return OK;
}

template<typename T_LQ> void Destroy_LQ(LinkQueue<T_LQ>& L) {
	Clear_LQ(L);

	free(L.front);
}

template<typename T_LQ> Status GetFront_LQ(LinkQueue<T_LQ>& L, T_LQ& e) {
	if (L.length == 0)
		return ERROR;

	e = L.front->next->data;
	return OK;
}

template<typename T_LQ> Status Enqueue_LQ(LinkQueue<T_LQ>& L, T_LQ x) {
	LinkNode_LQ<T_LQ>* s = (LinkNode_LQ<T_LQ>*)malloc(sizeof(LinkNode_LQ<T_LQ>));
	if (!s) {
		fputs("²åÈëÊ§°Ü£¡", stderr);
		exit(OVERFLOW);
	}

	s->data = x;
	s->next = NULL;
	L.back->next = s;
	L.back = L.back->next;
	L.length++;

	return OK;
}

template<typename T_LQ> Status Dequeue_LQ(LinkQueue<T_LQ>& L, T_LQ& e) {
	if (L.length == 0)
		return ERROR;

	LinkNode_LQ<T_LQ>* p = L.front->next;
	if (L.back == p)
		L.back = L.front;
	L.front->next = p->next;
	e = p->data;
	free(p);
	L.length--;

	return OK;
}

template<typename T_LQ> void Clear_LQ(LinkQueue<T_LQ>& L) {
	for (LinkNode_LQ<T_LQ>* p = L.front->next, *q; L.length; L.length--) {
		q = p->next;
		free(p);
		p = q;
	}
	L.back = L.front;
}

template<typename T_LQ> bool Empty_LQ(LinkQueue<T_LQ>& L) {
	return L.length == 0;
}

#endif