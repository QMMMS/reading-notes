//概览：
//将数组作为参数
//递归
//静态函数
//指针与（二维）数组
//指针嵌套
//指针形参
//返回指针函数
//指向函数的指针
//string基础
//空间分配


#pragma warning(disable:4996)
#include <stdio.h>
#include<string.h>
#include<stdlib.h>


void add_arr(int arr[], int num) {
	for (int i = 0;i != num;++i) {
		arr[i]++;
	}
}


void print_arr(int arr[], int num) {
	//传入数组形参时保存的是地址
	for (int i = 0;i != num;++i) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}


//将数组作为参数
int main41() {
	int my_arr[3] = { 4,3,6 };
	int my_arr2[5] = { 2,66,4,3,2 };

	add_arr(my_arr, 3);
	add_arr(my_arr2, 5);

	print_arr(my_arr, 3);
	print_arr(my_arr2, 5);


	printf("\n\npress any key to continue...");getch();
	return 0;
}


//递归
//静态函数，调用范围本文件
static int fact(int num) {
	if (num == 1 || num == 0) return 1;
	else if (num < 0) return 0;
	return (num * fact(num - 1));
}


int main42() {
	for (int i = 0;i != 11;++i) {
		printf("%d!=%d\n", i, fact(i));
	}

	printf("\n\npress any key to continue...");getch();
	return 0;
}


//指针与数组
int main43() {
	int my_arr[] = { 1,3,6,3,9 };
	int* pi = &my_arr[0];//等价于int pi = my_arr;
	printf("%d\n", *pi);
	for (int i = 0;i != 5;++i) {
		printf("my_arr[%d]=%d\n", i, pi[i]);
	}
	for (int i = 0;i != 5;++i) {
		printf("my_arr[%d]=%d\n", i, *(pi+i));
	}
	//pi[i]和my_arr[i]和*(pi+i)和*(my_arr+i)等价

	printf("*****************************************\n");
	for (int j = 0;j != 5;++j) {
		*pi = j;
		++pi;
	}
	pi = &my_arr[0];
	int* end = &my_arr[5];
	for (;pi != end;++pi) {
		printf("%d\t", *pi);
	}
	//迭代器思想（my_arr[5]是否安全？？？）

	printf("\n\npress any key to continue...");getch();
	return 0;
}


//指针与二维数组
int main44() {
	int my_arr[3][4] = { {1,2,3,4},{8,9,0,3},{4,3,2,1} };

	//++pi不是对于外部数组而言的
	for (int* pi = my_arr;pi != &my_arr[3];++pi) {
		//!!!!以下注释是错误示范
		

		//*pi为内部数组
		/*for (int* ipi = *pi;ipi != (*pi) + 4;++ipi) {
			printf("%d\t", *ipi);
		}*/
		printf("%d\t", (*pi));
	}


	printf("\n\npress any key to continue...");getch();
	return 0;
}


//指针嵌套
//相比于移动数据，移动指针开销小
int main45() {
	int my_arr[5] = { 1,5,7,9,0 };
	int* pa[5] = { &my_arr[0],&my_arr[1], &my_arr[2],&my_arr[3],&my_arr[4] };
	int** ppi = pa;

	for (int i = 0;i != 4;++i) {
		printf("%d\t", **ppi);
		ppi++;
	}

	ppi = pa;
	//++ppi 指的是pa递增,
	//但使用*ppi != &my_arr[5]会出错（为什么迭代器不会？）
	//所以不推荐
	for (;*ppi != &my_arr[4];++ppi) {
		printf("%d\t", **ppi);
	}

	printf("\nafter processing...\n");
	my_arr[4] = 3;
	pa[1] = &my_arr[4];
	pa[2] = &my_arr[1];
	pa[3] = &my_arr[2];
	pa[4] = &my_arr[3];

	ppi = pa;
	for (int i = 0;i != 5;++i) {
		printf("%d\t", **ppi);
		ppi++;
	}


	printf("\n\npress any key to continue...");getch();
	return 0;
}


//指针形参
void swap(int* pi1, int* pi2) {
	int temp = 0;
	temp = *pi1;
	*pi1 = *pi2;
	*pi2 = temp;
}


int main46() {
	int i1 = 3, i2 = 4;
	int* pi1 = &i1, pi2 = &i2;
	printf("i1=%d,i2=%d\n", i1, i2);
	swap(pi1, pi2);
	printf("i1=%d,i2=%d\n", i1, i2);


	printf("\n\npress any key to continue...");getch();
	return 0;
}


//返回指针函数
int* max_number(int* arr, int num) {
	int* pi = &arr[0];
	for (int i = 0;i != num;++i) {
		if (arr[i] > *pi) {
			pi = &arr[i];
		}
	}
	return pi;
}


int main47() {
	int my_arr[5] = { 6,3,6,2,8 };
	int* pi = max_number(my_arr, 5);
	printf("%d", *pi);


	printf("\n\npress any key to continue...");getch();
	return 0;
}


//!!!!!!!变量a在函数结束时释放，返回指针是错误的
char* lost() {
	char a = 'a';
	return &a;
}


int max_int(int i1, int i2) {
	if (i1 > i2) return i1;
	return i2;
}


//指向函数的指针
int main48() {
	int(*pi)(int, int);
	pi = max_int;
	int i1, i2, i3;
	printf("input 2 numbers:\n");
	scanf_s("%d", &i1);
	scanf_s("%d", &i2);
	i3 = (*pi)(i1, i2);
	printf("max:%d", i3);

	printf("\n\npress any key to continue...");getch();
	return 0;
}


//string基础
int main49() {
	char sentence[11] = "C language",input[11];
	//!!!!! 11=10+1(\0)
	printf("%s\n", sentence);
	printf("please input:");
	scanf("%s", input);//!!!!传入数组本身就是引用
	//input中不能有空格
	printf("%s\n", input);
	printf("*********************************\n");
	//puts usage
	puts(sentence);//or pointer
	puts("hello!");
	printf("****************\n");
	printf("valid lebgth of sentence is %d\n", strlen(sentence));
	//strlen记到\0为止

	char my_arr[20] = "I love ";
	strcat(my_arr, sentence);
	puts(my_arr);
	strcpy(my_arr, sentence);
	puts(my_arr);

	//为什么下面这个gets失效？待解决
	char input1[10];
	gets(input1);
	puts(input1);


	printf("\n\npress any key to continue...");getch();
	return 0;
}


int main410() {

	char input1[10];
	gets(input1);
	puts(input1);//???????待解决

	printf("\n\npress any key to continue...");getch();
	return 0;
}


//空间分配
int main411() {
	float* fpi = (float*)malloc(sizeof(float) * 2);
	if (fpi == NULL) exit(0);
	float* temp = fpi;
	*fpi = 1.2;
	*(fpi + 1) = 2.4;
	fpi = temp;
	printf("%f,%f", &fpi[0], &fpi[1]);
	//?????????为什么是0？待解决
	free(fpi);
	int* ipi = (int*)calloc(2, sizeof(int));
	if (ipi == NULL) exit(0);
	free(ipi);


	printf("\n\npress any key to continue...");getch();
	return 0;
}