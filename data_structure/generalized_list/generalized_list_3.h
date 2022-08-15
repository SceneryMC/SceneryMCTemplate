#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define INITIAL_MAX_SIZE 100
#define INCREMENT_SIZE 10

typedef int Status;
typedef enum state { HEAD, ATOM, LIST } State;
typedef struct node {
	State tag;
	struct node* tlink;
	union {
		char name;
		char value;
		struct node* hlink;
	} info;
} GLNode3, * GList3;
typedef struct lib {
	char name;
	GList3 pos;
}GListLib;
typedef GListLib DataType_SL;
typedef struct {
	DataType_SL* data;
	int max_size;
	int length;
}SeqList;

void Create_GL3(GList3& L, char* s, SeqList& lib);
void _Create_GL3(GList3 L, char* s, SeqList& lib);
Status Init_SL(SeqList& L);
Status Insert_SL(SeqList& L, int i, DataType_SL x);
GList3 search_library(SeqList lib, char name);

void Create_GL3(GList3& L, char* s, SeqList& lib) {
	Insert_SL(lib, lib.length + 1, { *s, L });
	L->tag = HEAD;
	L->info.name = *s;
	L->tlink = (GList3)malloc(sizeof(GLNode3));
	_Create_GL3(L->tlink, s + 2, lib);
}

void _Create_GL3(GList3 L, char* s, SeqList& lib) {
	static int i = 0;

	while (char c = s[i++]) {
		switch (c) {
		case ',':
			continue;
		case '(':
			L->tag = LIST;
			L->info.hlink = (GList3)malloc(sizeof(GLNode3));
			_Create_GL3(L->info.hlink, s, lib);
			break;
		case ')':
			L->tlink = NULL;
			if (!s[i])
				i = 0;
			return;
		default:
			if (islower(c)) {
				L->tag = ATOM;
				L->info.value = c;
			}
			else {
				L->tag = LIST;
				L->info.hlink = search_library(lib, c);
			}
		}

		if (s[i] != ')') {
			L->tlink = (GList3)malloc(sizeof(GLNode3));
			L = L->tlink;
		}
	}
}

Status Init_SL(SeqList& L) {
	L.data = (DataType_SL*)malloc((INITIAL_MAX_SIZE + 1) * sizeof(DataType_SL));
	if (!L.data) {
		puts("存储分配失败！");
		exit(1);
	}

	L.length = 0;
	L.max_size = INITIAL_MAX_SIZE;

	return OK;
}

Status Insert_SL(SeqList& L, int i, DataType_SL x) {
	if (L.length == L.max_size) {
		L.max_size += INCREMENT_SIZE;
		DataType_SL* new_base = (DataType_SL*)realloc(L.data, (L.max_size + 1) * sizeof(DataType_SL));
		if (!new_base) {
			puts("扩容失败！");
			exit(OVERFLOW);
		}
		L.data = new_base;
	}

	if (i < 1 || i > L.length + 1)
		return ERROR;

	DataType_SL* q = L.data + i;
	for (DataType_SL* p = L.data + L.length; p >= q; p--)
		*(p + 1) = *p;
	*q = x;
	L.length++;
	return OK;
}

GList3 search_library(SeqList lib, char name) {
	for (int i = 1; i <= lib.length; i++) {
		if (lib.data[i].name == name)
			return lib.data[i].pos;
	}
	return NULL;
}