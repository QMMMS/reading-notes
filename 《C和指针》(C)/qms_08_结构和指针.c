#include<stdio.h>

typedef struct {
	int a;
	short b[2];
}Ex2;


typedef struct Ex_tag{
	int a;
	char b[3];
	Ex2 c;
	struct Ex_tag* d;
}Ex;


int main8() {
	Ex x = { 10,"hi",{5,{-1,25}},NULL };
	Ex* px;

	//px
	px = &x;//左px是指针自己地址
	int address = px;//右px表示x地址
	printf("address = %d\n", address);

	//px+1
	//右px+1表示x后一个的地址，非法
	//左px+1自身不是地址，非法

	//*px
	Ex y = *px;//右*px表示整个x结构
	printf("(*px).a = %d\n", y.a);
	(*px).a = 10;//左*px是x的地址

	//*px+1、*(px+1)
	//表达式*px+1非法，结构与整型加法未定义
	//表达式*(px+1)表示x后一个结构，非法

	//px,&px->a
	//右px,&px->a表示同一个地址,但类型不同
	int* ip = &px->a;//注意类型
	Ex* px_2 = px;//注意类型
	int address1 = ip;
	int address2 = px_2;
	printf("ip = %d\npx_2 = %d\n", address1, address2);

	//*(px->b),px->b[1],*((px->b)+1)
	//说明略
	char c1 = *(px->b), c2 = px->b[1], c3 = *((px->b) + 1);
	printf("*(px->b) = %c\n", c1);
	printf("px->b[1] = %c\n", c2);
	printf("*((px->b)+1) = %c\n", c3);

	//px->c.a
	//说明略
	int i1 = px->c.a;
	printf("px->c.a = %d\n", i1);

	//*px->c.b
	//相当于*((px->c).b)
	int i2 = *px->c.b;
	printf("*px->c.b = %d\n", i2);

	//*px->d
	Ex z = { 100,"by",{50,{-10,250}},NULL };
	x.d = &z;
	Ex z_2 = *px->d;//右*px->d表示一个结构
	printf("z_2.a = %d\n", z_2.a);

	//px->d->c.b[1]
	int i3 = px->d->c.b[1];
	printf("*px->d->c.b[1] = %d\n", i3);

	return 0;
}