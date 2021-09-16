#include "stdio.h"
//#include "stdlib.h"  
//#include "math.h"  
//#include "time.h"


#define OK 1
#define ERROR 0
#define TURE 1
#define FALSE 0

#define MAXSIZE 20

typedef int ElemType;
typedef int Status;


typedef struct {
	ElemType data[MAXSIZE];
	int length;
}Sqlist;


Status visit(ElemType c) {
	printf("%d ", c);
	return OK;
}


int ListLength(Sqlist L)
{
	return L.length;
}


Status InitList(Sqlist* L) {
	L->length = 0;
	return OK;
}


Status EmptyList(Sqlist*L){
	if (L->length == 0) {
		printf("my_list是空的\n");
		return TURE;
	}
	else {
		printf("my_list有东西\n");
		return FALSE;
	}
}


Status GetElem(Sqlist L, int i, ElemType* e) {
	if (L.length == 0 || i<1 || i>L.length) {
		return ERROR;
	}
	*e = L.data[i - 1];
	return OK;
}

Status ListInsert(Sqlist* L, int i, ElemType e) {
	int k;
	if (L->length == MAXSIZE) {
		return ERROR;
	}
	if (i<0 || i>L->length + 1) {
		return ERROR;
	}
	if (i <= L->length) {
		for (k = L->length - 1;k >= i - 1;--k) {
			L->data[k + 1] = L->data[k];
		}
	}
	L->data[i - 1] = e;
	L->length++;
	return OK;
}


Status ListDelete(Sqlist* L, int i, ElemType* e) {
	int k;
	if (L->length == 0) {
		return ERROR;
	}
	if (i<1 || i>L->length) {
		return ERROR;
	}
	*e = L->data[i - 1];
	if (i < L->length) {
		for(k = i;k < L->length;++k) {
			L->data[k - 1] = L->data[k];
		}
	}
	L->length--;
	return OK;
}


int LocateElem(Sqlist L, ElemType e) {
	int i;
	if (L.length == 0) {
		return 0;
	}
	for (i = 0;i < L.length;++i) {
		if (L.data[i] == e) {
			break;
		}
	}
	if (i >= L.length) {
		return 0;
	}
	else {
		return i + 1;
	}
}


Status ListPrint(Sqlist L) {
	int i;
	for (i = 0;i < L.length;i++) {
		visit(L.data[i]);
	}
	printf("\n");
	return OK;

}


Status ClearList(Sqlist* L) {
	L->length = 0;
	return OK;
}


void CombineList(Sqlist* la, Sqlist lb) {
	ElemType e;
	int la_len = ListLength(*la);
	int lb_len = ListLength(lb);
	for (int i=1;i != lb_len+1;++i) {
		GetElem(lb, i, &e);
		if (!LocateElem(*la, e)) {
			ListInsert(la, ++la_len, e);
		}
	}
}


int main() {

	Sqlist my_list;
	Status i;
	ElemType e;

	InitList(&my_list);
	printf("my_list.length=%d\n",my_list.length);

	i = EmptyList(&my_list);

	for (int j = 0;j != 6;++j) {
		ListInsert(&my_list, 1, j);
	}
	printf("what's in the list?\n");
	printf("aha! ");
	ListPrint(my_list);
	printf("my_list.length=%d\n", my_list.length);

	i = EmptyList(&my_list);

	ClearList(&my_list);
	printf("清空……\n");
	i = EmptyList(&my_list);

	for (int j = 1;j <= 10;++j) {
		ListInsert(&my_list, j, j);
	}
	ListPrint(my_list);

	ListInsert(&my_list, 1, 0);
	ListPrint(my_list);

	GetElem(my_list, 5, &e);
	printf("%d\n",e);

	for (int num_for_search = 10;
		num_for_search != 12;++num_for_search) {
		int location = LocateElem(my_list, num_for_search);
		if (location) {
			printf("%d\n", location);
		}
		else {
			printf("没有找到！\n");
		}
	}
	
	Sqlist another_list;
	i = InitList(&another_list);
	for (int j = 11; j != 16;++j) {
		ListInsert(&another_list, 1, j);
	}
	printf("another list:");
	ListPrint(another_list);


	CombineList(&my_list, another_list);
	printf("结合后的my_list:");
	ListPrint(my_list);

	return 0;
}