#ifndef SS_H
#define SS_H

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define INITIAL_MAX_SIZE 1000
#define INCREMENT_SIZE 1000

typedef int Status;
template<typename T_SS> struct SeqStack {
	T_SS* bottom;
	T_SS* top;
	int max_size;
};

template<typename T_SS> Status Init_SS(SeqStack<T_SS>& L);
template<typename T_SS> Status Expansion_SS(SeqStack<T_SS>& L, int space);
template<typename T_SS> void Destroy_SS(SeqStack<T_SS>& L);
template<typename T_SS> bool Empty_SS(SeqStack<T_SS>& L);
template<typename T_SS> Status GetTop_SS(SeqStack<T_SS>& L, T_SS& e);
template<typename T_SS> void Clear_SS(SeqStack<T_SS>& L);
template<typename T_SS> Status Push_SS(SeqStack<T_SS>& L, T_SS x);
template<typename T_SS> Status Pop_SS(SeqStack<T_SS>& L, T_SS& e);

template<typename T_SS> Status Init_SS(SeqStack<T_SS>& L) {
	L.bottom = L.top = (T_SS*)malloc(INITIAL_MAX_SIZE * sizeof(T_SS));
	if (!L.bottom) {
		fputs("¥Ê¥¢∑÷≈‰ ß∞‹£°", stderr);
		exit(OVERFLOW);
	}

	L.max_size = INITIAL_MAX_SIZE;

	return OK;
}

template<typename T_SS> Status Expansion_SS(SeqStack<T_SS>& L, int space) {
	if (L.top - L.bottom >= space)
		return ERROR;

	L.max_size = space;
	T_SS* new_base = (T_SS*)realloc(L.data, L.max_size * sizeof(T_SS));
	if (!new_base) {
		fputs("¿©»› ß∞‹£°", stderr);
		exit(OVERFLOW);
	}
	int origial_size = L.top - L.bottom;
	L.bottom = new_base;
	L.top = L.bottom + origial_size;
	return OK;
}

template<typename T_SS> Status GetTop_SS(SeqStack<T_SS>& L, T_SS& e) {
	if (L.top == L.bottom)
		return ERROR;
	e = *(L.top - 1);
	return OK;
}

template<typename T_SS> Status Push_SS(SeqStack<T_SS>& L, T_SS x) {
	if (L.top - L.bottom == L.max_size) {
		L.max_size += INCREMENT_SIZE;
		T_SS* new_base = (T_SS*)realloc(L.bottom, L.max_size * sizeof(T_SS));
		if (!new_base) {
			fputs("¿©»› ß∞‹£°", stderr);
			exit(OVERFLOW);
		}
		L.bottom = new_base;
		L.top = L.bottom + L.max_size - INCREMENT_SIZE;
	}

	*(L.top++) = x;

	return OK;
}

template<typename T_SS> Status Pop_SS(SeqStack<T_SS>& L, T_SS& e) {
	if (L.top == L.bottom)
		return ERROR;

	e = *(--L.top);
	return OK;
}

template<typename T_SS> void Clear_SS(SeqStack<T_SS>& L) {
	L.top = L.bottom;
}

template<typename T_SS> void Destroy_SS(SeqStack<T_SS>& L) {
	free(L.bottom);
	L.max_size = -1;
}

template<typename T_SS> bool Empty_SS(SeqStack<T_SS>& L) {
	return L.top == L.bottom;
}

#endif