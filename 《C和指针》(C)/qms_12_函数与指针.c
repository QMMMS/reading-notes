#include<stdio.h>


int* f1();//f1是函数，返回指向整型的指针

int (*f2)();//f2是函数指针，指向的函数返回整型

int* (*f3)();//f3是函数指针，指向的函数返回指向整型的指针

int* f4[];//f4是数组，元素类型是指向整型的指针

//int f5()[];//f5是函数，返回元素类型是整型的数组
//非法！函数只能返回标量值，不能返回数组

//int f6[]();//f6是数组，元素类型是返回整型的函数
//非法！数组元素必须具有相同的长度，不同函数的长度很可能不同

int (*f7[])();//f7是数组，元素类型是指向返回整型的函数的指针
//清晰地说，元素类型是指针，指针指向函数，函数返回整型

int *(*f8[])();//f8是数组，元素类型是指向返回指向整型的指针的函数的指针
//清晰地说，元素类型是指针，指针指向函数，函数返回指针，指针指向整型



/*****************************************************************************************/

int f9(int n) { return n; }


int main121() {
	int(*pf)(int) = &f9;
	//&可以不写，函数名被调用时由编译器自动转换为函数指针

	//下面三个赋值语句在结果上相同
	int ans1 = f9(25);
	int ans2 = (*pf)(25);
	int ans3 = pf(25);
	printf("ans1 = %d\nans2 = %d\nans3 = %d\n", ans1, ans2, ans3);

	return 0;
}

/*****************************************************************************************/

typedef struct Node {
	struct Node* link;
	int value;
}Node;


int compare_ints(void const* a, void const* b) {
	if (*(int*)a == *(int*)b) return 0;
	return 1;
}


Node* search_list(Node* node, void const* value, 
	int (*compare)(void const*, void const*)) {
	while (node != NULL) {
		if (compare(&node->value, value) == 0) break;
		node = node->link;
	}
	return node;
}
