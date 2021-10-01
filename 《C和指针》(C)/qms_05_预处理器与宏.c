#//无效指令，突出作用
#include<stdio.h>
#include<stdarg.h>
#

//有点牛逼
#define reg register
#define do_forever for(;;)
#define CASE break;case


//写反斜线来换行
//注意define部分不写分号，使用时就要写分号，若全写会出现空语句
#define DEBUG_PRINT printf("File %s \nline %d\ndate %s\ntime %s\n"\
											"x = %d,y = %d,z = %d\n",\
											__FILE__,__LINE__,__DATE__,__TIME__, \
											x,y,z)


int main() {
	int x = 12, y = 4, z = 3;
	x *= 2;
	y += x;
	z = y * x;
	DEBUG_PRINT;
	return 0;
}


#define BAD_SQUARE(x) x*x
#define SQUARE(x) (x)*(x)


int main52() {
	int a = 5;
	printf("6*6 = %d\n", BAD_SQUARE(a + 1));//输出什么？
	//相当于printf("6*6 = %d\n",a+1*a+1)
	printf("6*6 = %d\n", SQUARE(a + 1));//输出什么？
	return 0;
}


#define BAD_DOUBLE(x) (x)+(x)
#define DOUBLE(x) ((x)+(x))


int main53() {
	int a = 5;
	printf("10*10 = %d\n", 10 * BAD_DOUBLE(5));//说明略
	printf("10*10 = %d\n", 10 * DOUBLE(5));

	return 0;
}


#define repeat do
#define until(x) while(!(x))


int main54() {
	int a = 0;

	//类似其他语言
	repeat{
		printf("I love C!\n");
		a++;
	}until(a == 10);

	return 0;
}


#define PRINT_1(FOMAT,VALUE) printf("the value is " FOMAT "\n",VALUE)
//#将宏参数转换为一个字符串
#define PRINT_2(FOMAT,VALUE) printf("the value of "#VALUE" is "FOMAT"\n",VALUE)
//##将两边的符号转换成一个符号
#define ADD_TO_SUM(sum_number,value) \
			sum ## sum_number += value


int main55() {
	int x = 3;
	PRINT_1("%d", x + 3);
	PRINT_2("%d", x + 3);

	int sum5 = 5;
	ADD_TO_SUM(5, 25);
	PRINT_2("%d", sum5);

	return 0;
}


//宏适用于频繁且十分简单的计算
//适当的宏比函数在程序规模和速度方面都更胜一筹
//宏与类型无关，比函数更具灵活性
#define MAX(a,b) ((a)>(b)?(a):(b))
//宏可以实现函数无法实现的功能，如下，传递了type
#define MALLOC(num,type) (type*)alloc((num)*sizeof(type))
#define DEGUG 1


#if DEGUG==1
//条件编译
	#if defined(DEGUG)
		#ifdef DEGUG
		int main56() {
			int x = 5, y = 8;
			int z = MAX(x++, y++);
			printf("x = %d\ny = %d\nz = %d\n", x, y, z);//输出什么？说明略

			return 0;
		}
		#endif//DEGUG
	#endif//defined(DEGUG)
#elif DEBUG==-1
int main() {
	printf("this can't be seen.");
	return 0;
}
#error DEBUG==-1!
//#error指令允许生成错误信息
#else
int main() {
	printf("this can't be seen,too.");
	return 0;
}
#error something went wrong!
#endif



//实现不固定参数个数的函数
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


int main510000() {
	float result = average(3, 2, 1, 22, 2);
	printf("average value = %g\n", result);
	return 0;
}