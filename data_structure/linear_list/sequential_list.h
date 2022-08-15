#ifndef SL_H
#define SL_H

#include <cstdio>
#include <cstdlib>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define INITIAL_MAX_SIZE 1000
#define INCREMENT_SIZE 1000

typedef int Status;
template<typename T_SL> struct SeqList {
	T_SL* data;
	int max_size;
	int length;
};

template<typename T_SL> Status Init_SL(SeqList<T_SL>& L);
template<typename T_SL> Status Expansion_SL(SeqList<T_SL>& L, int space);
template<typename T_SL> void Destroy_SL(SeqList<T_SL>& L);
template<typename T_SL> bool Empty_SL(SeqList<T_SL>& L);
template<typename T_SL> Status Insert_SL(SeqList<T_SL>& L, int i, T_SL x);
template<typename T_SL> Status Delete_SL(SeqList<T_SL>& L, int i, T_SL& e);

template<typename T_SL> Status Init_SL(SeqList<T_SL>& L) {
	L.data = (T_SL*)malloc((INITIAL_MAX_SIZE + 1) * sizeof(T_SL));
	if (!L.data) {
		fputs("¥Ê¥¢∑÷≈‰ ß∞‹£°", stderr);
		exit(1);
	}

	L.length = 0;
	L.max_size = INITIAL_MAX_SIZE;

	return OK;
}

template<typename T_SL> Status Expansion_SL(SeqList<T_SL>& L, int space) {
	if (L.max_size >= space)
		return ERROR;

	L.max_size = space;
	T_SL* new_base = (T_SL*)realloc(L.data, L.max_size * sizeof(T_SL));
	if (!new_base) {
		fputs("¿©»› ß∞‹£°", stderr);
		exit(OVERFLOW);
	}
	L.data = new_base;
	return OK;
}

template<typename T_SL> Status Insert_SL(SeqList<T_SL>& L, int i, T_SL x) {
	if (L.length == L.max_size) {
		L.max_size += INCREMENT_SIZE;
		T_SL* new_base = (T_SL*)realloc(L.data, (L.max_size + 1) * sizeof(T_SL));
		if (!new_base) {
			fputs("¿©»› ß∞‹£°", stderr);
			exit(OVERFLOW);
		}
		L.data = new_base;
	}

	if (i < 1 || i > L.length + 1)
		return ERROR;

	T_SL* q = L.data + i;
	for (T_SL* p = L.data + L.length; p >= q; p--)
		*(p + 1) = *p;
	*q = x;
	L.length++;
	return OK;
}

template<typename T_SL> Status Delete_SL(SeqList<T_SL>& L, int i, T_SL& e) {
	if (L.length > 0 && i >= 1 && i <= L.length) {
		T_SL* p = L.data + i, * tail = L.data + L.length;
		e = *p;
		while (p < tail) {
			*p = *(p + 1);
			p++;
		}
		L.length--;
		return OK;
	}
	else
		return ERROR;
}

template<typename T_SL> void Destroy_SL(SeqList<T_SL>& L) {
	free(L.data);
	L.length = L.max_size = -1;
}

template<typename T_SL> bool Empty_SL(SeqList<T_SL>& L) {
	return !L.length;
}

#endif