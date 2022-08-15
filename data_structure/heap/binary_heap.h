#ifndef BH_H
#define BH_H

#include <cstdio>
#include <cstdlib>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define INITIAL_MAX_SIZE 1000
#define INCREMENT_SIZE 1000

typedef int Status;
template<typename T_BH> struct BinHeap {
	T_BH* data;
	int max_size;
	int size;
};

inline int Left(int i);
inline int Right(int i);
inline int Parent(int i);
template<typename T_BH> Status Init_BH(BinHeap<T_BH>& L);
template<typename T_BH> void Clear_BH(BinHeap<T_BH>& L);
template<typename T_BH> void Destroy_BH(BinHeap<T_BH>& L);
template<typename T_BH> T_BH GetTop_BH(BinHeap<T_BH>& L);
template<typename T_BH> Status Expansion_BH(BinHeap<T_BH>& L, int space);
template<typename T_BH> void Swap(BinHeap<T_BH>& L, int i, int j);
template<typename T_BH> void MaxHeapify_BH(BinHeap<T_BH>& L, int i);
template<typename T_BH> void BuildMax_BH(BinHeap<T_BH>& L);
template<typename T_BH> Status ExtractMax_BH(BinHeap<T_BH>& L, T_BH& e);
template<typename T_BH> Status IncreaseKey_BH(BinHeap<T_BH>& L, int i, T_BH key);
template<typename T_BH> void MaxInsert_BH(BinHeap<T_BH>& L, T_BH key);
template<typename T_BH> void MinHeapify_BH(BinHeap<T_BH>& L, int i);
template<typename T_BH> void BuildMin_BH(BinHeap<T_BH>& L);
template<typename T_BH> Status ExtractMin_BH(BinHeap<T_BH>& L, T_BH& e);
template<typename T_BH> Status DecreaseKey_BH(BinHeap<T_BH>& L, int i, T_BH key);
template<typename T_BH> void MinInsert_BH(BinHeap<T_BH>& L, T_BH key);
template<typename T_BH> void HeapSort(BinHeap<T_BH>& L);

template<typename T_BH> Status Init_BH(BinHeap<T_BH>& L) {
	L.data = (T_BH*)malloc((INITIAL_MAX_SIZE + 1) * sizeof(T_BH));
	if (!L.data) {
		fputs("¥Ê¥¢∑÷≈‰ ß∞‹£°", stderr);
		exit(1);
	}

	L.size = 0;
	L.max_size = INITIAL_MAX_SIZE;

	return OK;
}

template<typename T_BH> void Clear_BH(BinHeap<T_BH>& L) {
	L.size = 0;
}

template<typename T_BH> void Destroy_BH(BinHeap<T_BH>& L) {
	L.max_size = L.size = -1;
	free(L.data);
}

inline int Left(int i) {
	return i << 1;
}

inline int Right(int i) {
	return (i << 1) + 1;
}

inline int Parent(int i) {
	return i >> 1;
}

template<typename T_BH> T_BH GetTop_BH(BinHeap<T_BH>& L) {
	return L.data[1];
}

template<typename T_BH> Status Expansion_BH(BinHeap<T_BH>& L, int space) {
	if (L.max_size >= space)
		return ERROR;

	L.max_size = space;
	T_BH* new_base = (T_BH*)realloc(L.data, L.max_size * sizeof(T_BH));
	if (!new_base) {
		fputs("¿©»› ß∞‹£°", stderr);
		exit(OVERFLOW);
	}
	L.data = new_base;
	return OK;
}

template<typename T_BH> void Swap(BinHeap<T_BH>& L, int i, int j) {
	T_BH temp = L.data[i];
	L.data[i] = L.data[j];
	L.data[j] = temp;
}

template<typename T_BH> void MaxHeapify_BH(BinHeap<T_BH>& L, int i) {
	int left, right;
	int largest;

	while (true) {
		left = Left(i);
		right = Right(i);

		if (left <= L.size && L.data[left] > L.data[i])
			largest = left;
		else
			largest = i;
		if (right <= L.size && L.data[right] > L.data[largest])
			largest = right;

		if (largest == i)
			return;
		Swap(L, i, largest);
		i = largest;
	}
}

template<typename T_BH> void BuildMax_BH(BinHeap<T_BH>& L) {
	for (int i = L.size / 2; i >= 1; i--)
		MaxHeapify_BH(L, i);
}

template<typename T_BH> Status ExtractMax_BH(BinHeap<T_BH>& L, T_BH& e) {
	if (L.size <= 0)
		return ERROR;

	e = L.data[1];
	L.data[1] = L.data[L.size--];
	MaxHeapify_BH(L, 1);
	return OK;
}

template<typename T_BH> Status IncreaseKey_BH(BinHeap<T_BH>& L, int i, T_BH key) {
	if (key <= L.data[i])
		return ERROR;

	L.data[i] = key;
	while (i > 1 && L.data[Parent(i)] < L.data[i]) {
		Swap(L, i, Parent(i));
		i = Parent(i);
	}
	return OK;
}

template<typename T_BH> void MaxInsert_BH(BinHeap<T_BH>& L, T_BH key) {
	if (L.size == L.max_size) {
		L.max_size += INCREMENT_SIZE;
		T_BH* new_base = (T_BH*)realloc(L.data, L.max_size * sizeof(T_BH));
		if (!new_base) {
			fputs("¿©»› ß∞‹£°", stderr);
			exit(OVERFLOW);
		}
		L.data = new_base;
	}

	L.data[++L.size] = key;

	int i = L.size;
	while (i > 1 && L.data[Parent(i)] < L.data[i]) {
		Swap(L, i, Parent(i));
		i = Parent(i);
	}
}

template<typename T_BH> void MinHeapify_BH(BinHeap<T_BH>& L, int i) {
	int left, right;
	int smallest;

	while (true) {
		left = Left(i);
		right = Right(i);

		if (left <= L.size && L.data[left] < L.data[i])
			smallest = left;
		else
			smallest = i;
		if (right <= L.size && L.data[right] < L.data[smallest])
			smallest = right;

		if (smallest == i)
			return;
		Swap(L, i, smallest);
		i = smallest;
	}
}

template<typename T_BH> void BuildMin_BH(BinHeap<T_BH>& L) {
	for (int i = L.size / 2; i >= 1; i--)
		MinHeapify_BH(L, i);
}

template<typename T_BH> Status ExtractMin_BH(BinHeap<T_BH>& L, T_BH& e) {
	if (L.size <= 0)
		return ERROR;

	e = L.data[1];
	L.data[1] = L.data[L.size--];
	MinHeapify_BH(L, 1);
	return OK;
}

template<typename T_BH> Status DecreaseKey_BH(BinHeap<T_BH>& L, int i, T_BH key) {
	if (key >= L.data[i])
		return ERROR;

	L.data[i] = key;
	while (i > 1 && L.data[Parent(i)] > L.data[i]) {
		Swap(L, i, Parent(i));
		i = Parent(i);
	}
	return OK;
}

template<typename T_BH> void MinInsert_BH(BinHeap<T_BH>& L, T_BH key) {
	if (L.size == L.max_size) {
		L.max_size += INCREMENT_SIZE;
		T_BH* new_base = (T_BH*)realloc(L.data, L.max_size * sizeof(T_BH));
		if (!new_base) {
			fputs("¿©»› ß∞‹£°", stderr);
			exit(OVERFLOW);
		}
		L.data = new_base;
	}

	L.data[++L.size] = key;

	int i = L.size;
	while (i > 1 && L.data[Parent(i)] > L.data[i]) {
		Swap(L, i, Parent(i));
		i = Parent(i);
	}
}

template<typename T_BH> void HeapSort(BinHeap<T_BH>& L) {
	BuildMax_BH(L);

	for (int i = L.size; i >= 2; i--) {
		Swap(L, 1, i);
		L.size--;
		MaxHeapify_BH(L, 1);
	}
}

#endif // !BH_H
