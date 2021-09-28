#include<stdio.h>
#include<stdarg.h>

static float average(int n, ...) {
	va_list var_arg;
	float sum = 0;

	va_start(var_arg, n);//...前最后一个有名字的参数

	for (int count = 0;count < n;count++) {
		//访问参数
		sum += va_arg(var_arg, int);//va_list变量，列表中下一个参数类型
		//va_arg返回这个参数的值，并使var_arg指向下一个可变参数
	}

	va_end(var_arg);//完成处理

	return sum / n;
}

int main5() {
	float result = average(3, 2, 1, 22, 2);
	printf("average value = %g\n", result);
}