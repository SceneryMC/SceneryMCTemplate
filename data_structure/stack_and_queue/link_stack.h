#ifndef LS_H
#define LS_H

#include <cstdio>
#include <cstdlib>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
template<typename T_LS> struct LinkNode_LS {
	T_LS data;
	struct LinkNode_LS<T_LS>* next;
};
template<typename T_LS> struct LinkStack {
	struct LinkNode_LS<T_LS>* top;
	int length;
};

template<typename T_LS> Status Init_LS(LinkStack<T_LS>& L);
template<typename T_LS> void Destroy_LS(LinkStack<T_LS>& L);
template<typename T_LS> bool Empty_LS(LinkStack<T_LS>& L);
template<typename T_LS> Status GetTop_LS(LinkStack<T_LS>& L, T_LS& e);
template<typename T_LS> void Clear_LS(LinkStack<T_LS>& L);
template<typename T_LS> Status Push_LS(LinkStack<T_LS>& L, T_LS x);
template<typename T_LS> Status Pop_LS(LinkStack<T_LS>& L, T_LS& e);

template<typename T_LS> Status Init_LS(LinkStack<T_LS>& L) {
	L.top = (LinkNode_LS<T_LS>*)malloc(sizeof(LinkNode_LS<T_LS>));
	if (!L.top) {
		fputs("´æ´¢·ÖÅäÊ§°Ü£¡", stderr);
		return ERROR;
	}

	L.top->next = NULL;
	L.length = 0;

	return OK;
}

template<typename T_LS> void Destroy_LS(LinkStack<T_LS>& L) {
	Clear_LS(L);

	free(L.top);
}

template<typename T_LS> Status GetTop_LS(LinkStack<T_LS>& L, T_LS& e) {
	if (L.length == 0)
		return ERROR;

	e = L.top->next->data;
	return OK;
}

template<typename T_LS> Status Push_LS(LinkStack<T_LS>& L, T_LS x) {
	LinkNode_LS<T_LS>* s = (LinkNode_LS<T_LS>*)malloc(sizeof(LinkNode_LS<T_LS>));
	if (!s) {
		fputs("²åÈëÊ§°Ü£¡", stderr);
		exit(OVERFLOW);
	}

	s->data = x;
	s->next = L.top->next;
	L.top->next = s;
	L.length++;

	return OK;
}

template<typename T_LS> Status Pop_LS(LinkStack<T_LS>& L, T_LS& e) {
	if (L.length == 0)
		return ERROR;

	LinkNode_LS<T_LS>* s = L.top->next;
	e = s->data;
	L.top->next = s->next;
	free(s);
	L.length--;

	return OK;
}

template<typename T_LS> void Clear_LS(LinkStack<T_LS>& L) {
	for (LinkNode_LS<T_LS>* p = L.top->next, *q; L.length; L.length--) {
		q = p->next;
		free(p);
		p = q;
	}
}

template<typename T_LS> bool Empty_LS(LinkStack<T_LS>& L) {
	return L.length == 0;
}

#endif