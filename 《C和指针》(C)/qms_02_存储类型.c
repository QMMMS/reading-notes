#include<stdio.h>


int a = 5;//extern
extern int b;//可在其他文件访问
static int c;//internal,这个文件访问
//a,b,c静态（static）变量：在任何代码块之外声明的变量为静态变量，总是存储在静态内存中，
//这样的变量在程序运行之前就创建，在整个程序运行期间都存在，直到程序结束。


	//external
int d(int e) {
	//参数e自动存储类型
	//自动（auto）变量：在代码块内部声明的变量为自动变量，存储在堆栈中，在执行到代码块中
	//声明变量的时候创建，在代码块执行完毕之后被销毁。
	int f = 15;//自动存储类型
	register int b;//寄存器变量，初始值是垃圾
	//寄存器（register）变量：使用关键字register声明的自动变量，
	//创建时间和销毁时间与自动变量相同，但是使用寄存器变量的函数在返回之前，原来存储在寄存器中的值必须要恢复，确
	//保调用者的寄存器变量未被破坏。
	static int g = 20;//静态,当函数每次被调用时，不会重新初始化
	extern int a;//这行声明没有必要

	{
		int e;//参数e被隐藏
		int a;//隐藏了同名的静态变量
		//e,a自动存储类型
		extern int h;//表示来自全局变量,必要
	}

	{
		int x;
		int e;
		//隐藏了代码块外的同名变量
	}
}


//internal，静态
static int i(){
	printf("from i");
	return 0;
}


int main2() {
	i();
	return 0;
}