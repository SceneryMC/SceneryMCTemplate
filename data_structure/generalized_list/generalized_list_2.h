#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX_STRING_LENGTH 50

typedef int Status;
typedef char DataType_GL2;
typedef enum {ATOM, LIST} ElemTag;
typedef struct GLNode2 {
    ElemTag tag;
    union {
        DataType_GL2 atom;
        struct GLNode2 *hp;
    } a;
    struct GLNode2 *tp;
} *GList2, GLNode2;

void Init_GL2(GList2 &L);
void Create_GL2(GList2 &L, char* S);
void Destroy_GL2(GList2 &L);
void Copy_GL2(GList2& T, GList2 L);
int Length_GL2(GList2 L);
int Depth_GL2(GList2 L);
bool Empty_GL2(GList2 L);
GList2 GetHead_GL2(GList2 L);
GList2 GetTail_GL2(GList2 L);
void InsertFirst_GL2(GList2& L, GList2 e);
void DeleteFirst_GL2(GList2& L, GList2 &e);
void Traverse_GL2(GList2 L, void(*visit)(DataType_GL2));
void Substring(char* sub, char* s, int pos, int len);
void Sever(char* str, char* hstr);

void Init_GL2(GList2 &L) {
    L = NULL;
}

void Create_GL2(GList2 &L, char* S) {
    char  sub[MAX_STRING_LENGTH], hsub[MAX_STRING_LENGTH];
    GList2 p;

    L = (GList2)malloc(sizeof(GLNode2));
    if (!L) /* 建表结点不成功 */
        exit(OVERFLOW);
    if (!strcmp(S, "()")) { /* 创建空表 */
        L->tag = LIST;
        L->a.hp = L->tp = NULL;
    }
    else if (strlen(S) == 1) { /* 创建单原子广义表 */
        L->tag = ATOM;
        L->a.atom = *S;
        L->tp = NULL;
    }
    else { /* 创建一般表 */
        L->tag = LIST;
        L->tp = NULL;
        Substring(sub, S, 1, strlen(S) - 2);
        // 脱外层括号(去掉第1个字符和最后1个字符)给串sub
        Sever(sub, hsub); // 从sub中分离出表头串hsub
        Create_GL2(L->a.hp, hsub);
        p = L->a.hp;
        while (*sub != '\0') { // 表尾不空，则重复建n个子表
            Sever(sub, hsub); // 从sub中分离出表头串hsub
            Create_GL2(p->tp, hsub);
            p = p->tp;
        };
    }
}

void Destroy_GL2(GList2 &L) {
    /* 初始条件：广义表L存在。操作结果：销毁广义表L */
    GList2 ph, pt;
    if (L) { /* L不为空表 */
        /* 由ph和pt接替L的两个指针 */
        if (L->tag) /* 是子表 */
            ph = L->a.hp;
        else /* 是原子 */
            ph = NULL;
        pt = L->tp;
        Destroy_GL2(ph); /* 递归销毁表ph */
        Destroy_GL2(pt); /* 递归销毁表pt */
        free(L); /* 释放L所指结点 */
        L = NULL; /* 令L为空 */
    }
}

void Copy_GL2(GList2& T, GList2 L) {
    /* 初始条件：广义表L存在。操作结果：由广义表L复制得到广义表T */
    T = NULL;
    if (L) { /* L不空 */
        T = (GList2)malloc(sizeof(GLNode2));
        if (!T)
            exit(OVERFLOW);
        T->tag = L->tag; /* 复制枚举变量 */
        if (L->tag == ATOM) /* 复制共用体部分 */
            T->a.atom = L->a.atom; /* 复制单原子 */
        else
            Copy_GL2(T->a.hp, L->a.hp); /* 复制子表 */
        if (L->tp == NULL) /* 到表尾 */
            T->tp = L->tp;
        else
            Copy_GL2(T->tp, L->tp); /* 复制子表 */
    }
}

int Length_GL2(GList2 L) {
    /* 初始条件：广义表L存在。操作结果：求广义表L的长度，即元素个数 */
    int len = 0;
    GList2 p = L->a.hp; /* p指向第1个元素 */
    while (p) {
        len++;
        p = p->tp;
    };
    return len;
}

int Depth_GL2(GList2 L) {
    /* 初始条件：广义表L存在。操作结果：求广义表L的深度 */
    int max, dep;
    GList2 pp;
    if (!L|| L->tag == LIST && !L->a.hp)
        return 1; /* 空表深度为1 */
    else if (L->tag == ATOM)
        return 0; /* 单原子表深度为0，只会出现在递归调用中 */
    else /* 求一般表的深度 */
        for (max = 0, pp = L->a.hp; pp; pp = pp->tp) {
            dep = Depth_GL2(pp); /* 求以pp为头指针的子表深度 */
            if (dep > max)
                max = dep;
        }
    return max + 1; /* 非空表的深度是各元素的深度的最大值加1 */
}

bool Empty_GL2(GList2 L) {
    /* 初始条件：广义表L存在。操作结果：判定广义表L是否为空 */
    return !L || L->tag == LIST && !L->a.hp;
}

GList2 GetHead_GL2(GList2 L) {
    /* 生成广义表L的表头元素，返回指向这个元素的指针 */
    GList2 h, p;
    if (!L || L->tag == LIST && !L->a.hp) /* 空表无表头 */
        return NULL;
    p = L->a.hp->tp; /* p指向L的表尾 */
    L->a.hp->tp = NULL; /* 截去L的表尾部分 */
    Copy_GL2(h, L->a.hp); /* 将表头元素复制给h */
    L->a.hp->tp = p; /* 恢复L的表尾(保持原L不变) */
    return h;
}

GList2 GetTail_GL2(GList2 L) {
    // 将广义表L的表尾生成为广义表，返回指向这个新广义表的指针
    GList2 t, p;
    if (!L || L->tag == LIST && !L->a.hp) // 空表无表尾
        return NULL;
    p = L->a.hp; // p指向表头
    L->a.hp = p->tp; // 在L中删去表头
    Copy_GL2(t, L); // 将L的表尾拷给t
    L->a.hp = p; // 恢复L的表头(保持原L不变)
    return t;
}

void InsertFirst_GL2(GList2 &L, GList2 e) {
    // 初始条件：广义表存在。操作结果：插入元素e(也可能是子表)作为广义表L的第1元素(表头)
    GList2 p = L->a.hp;
    L->a.hp = e;
    e->tp = p;
}

void DeleteFirst_GL2(GList2 &L, GList2& e) {
    // 初始条件：广义表L存在。操作结果：删除广义表L的第一元素，并用e返回其值
    if (L && L->a.hp) {
        e = L->a.hp;
        L->a.hp = e->tp;
        e->tp = NULL;
    }
    else
        e = L;
}

void Traverse_GL2(GList2 L, void(*visit)(DataType_GL2)) {
    // 利用递归算法遍历广义表L
    GList2 hp;
    if (L) { // L不空
        if (L->tag == ATOM) { // L为单原子
            visit(L->a.atom);
            hp = NULL;
        }
        else // L为子表
            hp = L->a.hp;
        Traverse_GL2(hp, visit);
        Traverse_GL2(L->tp, visit);
    }
}

void Substring(char* sub, char* s, int pos, int len)
{
    s = s + pos;
    while (len > 0)
    {
        *sub = *s;
        sub++;
        s++;
        len--;
    }
    *sub = '\0';
}

void Sever(char* str, char* hstr)
{
    int n, i, k;
    char ch[50];
    n = strlen(str);
    i = k = 0;
    do
    {
        Substring(ch, str, i++, 1);
        if (*ch == '(')
            k++;
        else if (*ch == ')')
            k--;
    } while (i < n && (*ch != ',' || k != 0));

    if (i < n)
    {
        Substring(hstr, str, 0, i - 1);
        Substring(str, str, i, n - i);
    }
    else
    {
        strcpy(hstr, str);
        str[0] = '\0';
    }
}