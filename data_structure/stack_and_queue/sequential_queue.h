#ifndef SQ_H
#define SQ_H

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define STATIC_MAX_SIZE 1000

typedef int Status;
template<typename T_SQ> struct SeqQueue {
	T_SQ data[STATIC_MAX_SIZE + 1];
	int front;
	int back;
	int max_size;
};

template<typename T_SQ> void Init_SQ(SeqQueue<T_SQ>& L);
template<typename T_SQ> bool Empty_SQ(SeqQueue<T_SQ>& L);
template<typename T_SQ> Status GetFront_SQ(SeqQueue<T_SQ>& L, T_SQ& e);
template<typename T_SQ> void Clear_SQ(SeqQueue<T_SQ>& L);
template<typename T_SQ> Status Enqueue_SQ(SeqQueue<T_SQ>& L, T_SQ x);
template<typename T_SQ> Status Dequeue_SQ(SeqQueue<T_SQ>& L, T_SQ& e);

template<typename T_SQ> void Init_SQ(SeqQueue<T_SQ>& L) {
	L.front = L.back = 0;
	L.max_size = STATIC_MAX_SIZE + 1;
}

template<typename T_SQ> Status GetFront_SQ(SeqQueue<T_SQ>& L, T_SQ& e) {
	if (L.front == L.back)
		return ERROR;

	e = L.data[L.front == 0 ? L.max_size : L.front - 1];
	return OK;
}

template<typename T_SQ> Status Enqueue_SQ(SeqQueue<T_SQ>& L, T_SQ x) {
	if (L.front == (L.back + 1) % L.max_size) {
		fputs("¶ÓÁÐÒÑÂú£¡", stderr);
		exit(OVERFLOW);
	}

	L.data[L.back] = x;
	L.back = (L.back + 1) % L.max_size;

	return OK;
}

template<typename T_SQ> Status Dequeue_SQ(SeqQueue<T_SQ>& L, T_SQ& e) {
	if (L.front == L.back)
		return ERROR;

	e = L.data[L.front];
	L.front = (L.front + 1) % L.max_size;
	return OK;
}

template<typename T_SQ> bool Empty_SQ(SeqQueue<T_SQ>& L) {
	return L.front == L.back;
}

template<typename T_SQ> void Clear_SQ(SeqQueue<T_SQ>& L) {
	L.front = L.back = 0;
}

#endif