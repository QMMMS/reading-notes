#include<stdio.h>
#include<stdlib.h>   //malloc
#include<time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20

#define MAIN_DEBUG if(i==ERROR) exit(1)
#define FUNC_DEBUG if(i==ERROR) return ERROR

typedef int Status;
typedef int ElemType;


typedef struct Node{
	ElemType data;
	struct Node* next;
}Node;
typedef struct Node* LinkList;


Status visit(ElemType c)
{
	printf("%d ", c);
	return OK;
}


//访问链表的所有数据值
Status VisitList(LinkList L) {
	LinkList p = L->next;

	printf("List value members:");
	while (p != NULL) {
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");

	return OK;
}


//初始化
Status InitList(LinkList* L) {
	*L = (LinkList)malloc(sizeof(Node));
	if (!(*L)) return ERROR;
	(*L)->next = NULL;
	return OK;
}


//得值
Status GetElem(LinkList L, int i, ElemType* e) {
	LinkList p = L->next;
	int j = 1;
	while (p && j != i) {
		p = p->next;
		++j;
	}

	if (!p || j > i) return ERROR;
	*e = p->data;

	return OK;
}


//插入
Status ListInsert(LinkList* L, int i, ElemType e) {
	LinkList p = *L;
	int j = 1;
	while (p && j != i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	LinkList s = (LinkList)malloc(sizeof(Node));
	if (s == NULL) return ERROR;
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}


//得长度
int ListLength(LinkList L) {
	LinkList p = L->next;
	int len = 0;
	while (p) {
		p = p->next;
		++len;
	}
	return len;
}


//删除节点
Status ListDelete(LinkList* L, int i, ElemType* e) {
	LinkList p = *L;
	int j = 1;
	while (p->next && j < i) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i) return ERROR;
	LinkList q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}


//整表创建，头插法
Status CreateListHead(LinkList* L, int n) {
	LinkList p;
	int i;
	srand((unsigned int)time(0));//主要是不让警告BB

	*L = (LinkList)malloc(sizeof(Node));
	if (L == NULL) return ERROR;
	(*L)->next = NULL;//VS!你要我怎样！

	for (i = 0;i != n;++i) {
		p = (LinkList)malloc(sizeof(Node));
		if (p == NULL) return ERROR;
		p->data = rand() % 100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
	return OK;
}


//自己写的头插法
Status my_CreateListHead(LinkList* L, int n) {
	Status i = InitList(L);
	FUNC_DEBUG;

	srand((unsigned int)time(0));
	int j;
	for (j = 0; j != n;++j) {
		i = ListInsert(L, 1, rand() % 100 + 1);
	}
	FUNC_DEBUG;
	return OK;
}


//尾插法
Status CreateListTail(LinkList* L, int n) {
	LinkList p, r;
	int j;
	srand((unsigned int)time(0));
	*L = (LinkList)malloc(sizeof(Node));
	if (L == NULL) return ERROR;

	r = *L;
	for (j = 0;j != n;++j) {
		p = (LinkList)malloc(sizeof(Node));
		if (p == NULL) return ERROR;
		p->data = rand() % 100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
	return OK;
}


Status ClearList(LinkList* L) {
	LinkList p, q;
	p = (*L)->next;

	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}


int main() {
	LinkList L,L1,L2,L3;
	Status i;

	i = InitList(&L);
	MAIN_DEBUG;
	printf("初始化L后：ListLength(L)=%d\n", ListLength(L));

	i = CreateListHead(&L1, 4);
	MAIN_DEBUG;
	VisitList(L1);
	i = my_CreateListHead(&L2, 5);
	MAIN_DEBUG;
	VisitList(L2);
	i = CreateListTail(&L3, 4);
	MAIN_DEBUG;
	VisitList(L3);

	i = ListInsert(&L3, 2, 23);
	MAIN_DEBUG;

	int e = 0;
	ElemType* ep=&e;
	i = ListDelete(&L3, 3, ep);
	MAIN_DEBUG;
	VisitList(L3);

	i = ClearList(&L3);
	if (i == OK) printf("L3 cleared successfully!\n");
	
	return 0;
}