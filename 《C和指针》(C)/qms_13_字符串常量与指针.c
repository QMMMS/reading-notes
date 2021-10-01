#include<stdio.h>


//神秘函数
//0<n<100
void mystery(int n) {
	n += 5;
	n /= 10;
	printf("%s\n", "**********" + 10 - n);
}


int main131() {
	//字符串出现在表达式中时，值是指针常量
	char* c1 = "xyz" + 2;//c1指向'z'
	char c2 = *"xyz";//c2='x'
	char c3 = "xyz"[1];//c3='y
	char c4 = *("xyz" + 2);//c4='z'
	printf("*c1 = %c\n", *c1);
	printf("c2 = %c\n", c2);
	printf("c3 = %c\n", c3);
	printf("c4 = %c\n", c4);
	mystery(56);
	return 0;
}
