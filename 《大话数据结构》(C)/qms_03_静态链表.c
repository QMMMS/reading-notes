#include<stdlib.h>
#include<stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 1000
#define MAIN_DEBUG if(i==ERROR) exit(1)

typedef int Status;
typedef char ElemType;


typedef struct {
	ElemType data;
	int cur;
}StaticLinkList[MAXSIZE];


Status visit(ElemType c){
	printf("%c ", c);
	return OK;
}


Status InitList(StaticLinkList space) {
	int i;
	for (i = 0;i != MAXSIZE-1;++i) {
		space[i].cur = i + 1;
	}
	space[MAXSIZE - 1].cur = 0;
	return OK;
}


int Malloc_SSL(StaticLinkList space) {
	int i = space[0].cur;
	if (i) space[0].cur = space[i].cur;
	//else?????
	return i;
}


int ListLength(StaticLinkList space) {
	int j = 0;
	int i = space[MAXSIZE - 1].cur;
	while (i) {
		i = space[i].cur;
		++j;
	}
	return j;
}


Status ListInsert(StaticLinkList L, int i, ElemType e) {
	int j, k, l;
	k = MAXSIZE - 1;
	if (i<1 || i>ListLength(L) + 1) return ERROR;

	j = Malloc_SSL(L);
	if (j) {
		L[j].data = e;
		for (l = 1;l <= i - 1;++l) {
			k = L[k].cur;
		}
		L[j].cur = L[k].cur;
		L[k].cur = j;
		return OK;
	}
	return ERROR;
}


void Free_SSL(StaticLinkList space, int k) {
	space[k].cur = space[0].cur;
	space[0].cur = k;
}


Status ListDelete(StaticLinkList L, int i) {
	int l, k;
	if (i<1 || i>ListLength(L) + 1) return ERROR;
	k = MAXSIZE - 1;

	for (l = 1;l <= i - 1;++l) {
		k = L[k].cur;
	}
	l = L[k].cur;
	L[k].cur = L[l].cur;
	Free_SSL(L, l);
	return OK;
}


void VisitList(StaticLinkList L) {
	int cur = L[MAXSIZE - 1].cur;
	printf("StaticLinkList data members:\t");
	while (cur != 0) {
		printf("%c\t", L[cur].data);
		cur = L[cur].cur;
	}
	printf("\n");
}


int main() {
	StaticLinkList L;
	Status i;
	i = InitList(L);
	MAIN_DEBUG;
	printf("初始化L后：L.length=%d\n", ListLength(L));

	i = ListInsert(L, 1, 'F');
	MAIN_DEBUG;
	i = ListInsert(L, 2, 'E');
	MAIN_DEBUG;
	i = ListInsert(L, 2, 'D');
	MAIN_DEBUG;
	i = ListInsert(L, 1, 'B');
	MAIN_DEBUG;
	i = ListInsert(L, 5, 'A');
	MAIN_DEBUG;
	printf("插入后：L.length=%d\n", ListLength(L));
	VisitList(L);

	i = ListDelete(L, 1);
	MAIN_DEBUG;
	i = ListDelete(L, 2);
	MAIN_DEBUG;
	printf("删除部分后：L.length=%d\n", ListLength(L));
	VisitList(L);

	return 0;
}