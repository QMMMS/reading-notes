#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_COLS 20
#define MAX_INPUT 1000


//从命令行读取字符串
int read_column_numbers(int columns[], int max) {
	int num = 0;
	int ch;/*防止输入的字符意外被解释成EOF，声明成int类型*/
	while (num < max && scanf("%d", &columns[num]) == 1 
		&& columns[num] >= 0) {
		//对于scanf,失败返回0，成功返回1
		num++;
	}
		if (num % 2 != 0) {
			puts("Last column number is not paired.");//from stdio.h
			exit(EXIT_FAILURE);//from stdlib.h
			/*直接退出无返回值*/
		}
	
		while ((ch = getchar()) != EOF && ch != '\n');/*找到行尾，过滤掉负数后面的数*/
		//getchar从输入中读取一个值，若不存在，返回EOF，表示文件末尾
		return num;
}


//处理输入的字符串
void rearrange(char* output, char* const input, 
	int const columns[], int num_column) {
	int length = strlen(input);//string.h
	int output_column = 0;     /*output数组的下标*/
	for (int column = 0; column < num_column; column += 2) {
		//第二部分在每次循环之前执行
		 //第三部分在每次循环之后执行
		int nchars = columns[column + 1] - columns[column] + 1;
		if (output_column == MAX_INPUT - 1 || columns[column] >= length) break;
		if (nchars + output_column > MAX_INPUT - 1) {
			//输出的数组的空间不够，能存多少就存多少
			nchars = MAX_INPUT - output_column - 1;
		}
		strncpy(output + output_column, input + columns[column], nchars);
		output_column += nchars;
	}
	output[output_column] = '\0';/*字符串结束NUL*/
	
		

}



int main1() {
	int columns[MAX_COLS];
	char input[MAX_INPUT];
	char output[MAX_INPUT];

	int num = read_column_numbers(columns, MAX_COLS);

	while (fgets(input, sizeof(input), stdin) != NULL && input[0] != '\n')
	{
		printf("输入字符串：%s\n", input);
		rearrange(output, input, columns, num);
		printf("输出字符串：%s\n", output);
	}
	return EXIT_SUCCESS;
}

