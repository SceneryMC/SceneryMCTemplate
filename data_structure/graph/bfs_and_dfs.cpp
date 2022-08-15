#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "stack_and_queue/link_queue.h"

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int VRType;
typedef int InfoType;
typedef int VertexType;
typedef bool IfVisited;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
    int from;
    int dest;
}Arc;
typedef struct {
    VRType adj;
    InfoType* info;//相关信息指针，没用过
}ArcCell, ** AdjMatrix;
typedef struct {
    VertexType* VerticesList;
    AdjMatrix Edges;
    int numVertices, numEdges;
    GraphKind kind;
} MGraph;
typedef struct Enode {
    int dest;
    struct Enode* link;
    InfoType* info;//相关信息指针，没用过
} EdgeNode;
typedef struct {
    VertexType data;
    EdgeNode* head;
} VertexNode;
typedef struct {
    VertexNode* VerticesList;
    int numVertices, numEdges;
    GraphKind kind;
} ALGraph;
typedef struct {
    int mark;//不知道用来干啥，内置的visited？
    int vertex1, vertex2;
    struct ArcBox* nextout, * nextin;
    InfoType* info;//相关信息指针，没用过
} ArcBox;
typedef struct {
    VertexType  data;
    ArcBox* firstin, * firstout;
} VexNode;
typedef struct {
    VexNode* xlist;
    int numVertices, numEdges;
} OLGraph;
typedef struct {
    IfVisited mark;
    int   vertex1, vertex2;
    struct EBox* path1, * path2;
    InfoType* info;
} EBox;
typedef struct {
    VertexType  data;
    EBox* Firstout;
} VexBox;
typedef struct {
    VexBox* adjmulist;
    int  numVertices, numEdges;
} AMLGraph;

void Init_ALG(ALGraph& G, int nv, int ne, GraphKind kind);
void Create_ALG(ALGraph& G, char* vex, Arc arc);
void BFSTraverse_ALG(ALGraph G, void (*visit)(VertexType));
void BFS(ALGraph G, int begin, void (*visit)(VertexType), IfVisited* visited);
void DFSTraverse_ALG(ALGraph G, void (*visit)(VertexType));
Status DFS(ALGraph G, int begin, void (*visit)(VertexType), IfVisited* visited);

void Init_ALG(ALGraph& G, int nv, int ne, GraphKind kind) {
    G.numEdges = ne;
    G.numVertices = nv;
    G.kind = kind;

    G.VerticesList = (VertexNode*)malloc(nv * sizeof(VertexNode));
    if (!G.VerticesList) {
        puts("创建失败！");
        exit(OVERFLOW);
    }
}

void Create_ALG(ALGraph& G, char* vex, Arc arc) {
    for (int i = 0; i < G.numVertices; i++) {
        G.VerticesList[i].data = vex[i];
        G.VerticesList[i].head = NULL;
    }

    EdgeNode* p;
    for (int i = 0; i < G.numEdges; i++) {
        p = (EdgeNode*)malloc(sizeof(EdgeNode));
        p->dest = arc.dest;
        p->info = NULL;
        p->link = G.VerticesList[i].head;
        G.VerticesList[i].head = p;
    }
}

void BFSTraverse_ALG(ALGraph G, void (*visit)(VertexType)) {
    IfVisited* visited = (IfVisited*)calloc(G.numVertices, sizeof(IfVisited));

    for (int i = 0; i < G.numVertices; i++)
        if (!visited[i])
            BFS(G, i, visit, visited);

    free(visited);
}

void BFS(ALGraph G, int begin, void (*visit)(VertexType), IfVisited* visited) {
    LinkQueue<int> Q;
    Init_LQ(Q);
    visit(begin);
    visited[begin] = true;

    int u;
    EdgeNode* p;
    Enqueue_LQ(Q, begin);
    while (!Empty_LQ(Q)) {
        Dequeue_LQ(Q, u);
        p = G.VerticesList[u].head;
        while (p) {
            if (!visited[p->dest]) {
                visit(p->dest);
                visited[p->dest] = true;
                Enqueue_LQ(Q, p->dest);
            }
            p = p->link;
        }
    }
}

void DFSTraverse_ALG(ALGraph G, void (*visit)(VertexType)) {
    IfVisited* visited = (IfVisited*)calloc(G.numVertices, sizeof(IfVisited));

    for (int i = 0; i < G.numVertices; i++)
        if (!visited[i])
            DFS(G, i, visit, visited);

    free(visited);
}

Status DFS(ALGraph G, int begin, void (*visit)(VertexType), IfVisited* visited) {
    visited[begin] = true;
    for (EdgeNode* p = G.VerticesList[begin].head; p; p = p->link) {
        visit(p->dest);
        if (!visited[p->dest])
            DFS(G, p->dest, visit, visited);
    }
}
