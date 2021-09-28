#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>


//递归版本fibonacci
//递归更清晰，但性能可能偏弱
unsigned long fib_rec(int n) {
	if (n <= 2) return 1;
	else return fib_rec(n - 1) + fib_rec(n - 2);
}


//迭代版本fibonacci
//略复杂，但性能值得
unsigned long fib_iter(int n) {
	unsigned long result, father_result, grandfa_result;
	result = father_result = 1;
	while (n > 2) {
		--n;
		grandfa_result = father_result;
		father_result = result;
		result = grandfa_result + father_result;
	}
	return result;
}


int main4() {
	int n;
	printf("please input a number(推荐值42):");
	int i = scanf("%d", &n);
	printf("迭代版本fibonacci开始计算...\n");
	printf("迭代版本fibonacci( %d ) = %d\n", n, fib_iter(n));
	printf("递归版本fibonacci开始计算...\n");
	printf("递归版本fibonacci( %d ) = %d\n", n, fib_rec(n));
	
	return 0;
}