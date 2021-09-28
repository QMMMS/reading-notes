#include<stdio.h>
#include<string.h>
char const *keyword[] = {
	//指针数组
	"do",
	"for",
	"if",
	"return"
};
#define N_KEYWORD (sizeof(keyword)/sizeof(keyword[0]))
//自动计算数组元素个数


//将多维数组作为参数
void print_test(int(*mat)[10], int num) {
	//相当于 int mat[][10]
	for (int i = 0;i != num;++i) {
		int* np = *mat;
		for (int j = 0;j != 10;++j) {
			printf("%d\t", *np++);
		}
		printf("\n");
		mat++;
	}
}


//指针练习
int main61() {
	int matrix[3][10] = {
		{10},
		{1,2,3,4,5,6},
		{0},
	};
	print_test(matrix, 3);


	int (*p1)[10] = matrix + 1;//p1指向matrix第二个子数组
	//虽然int* p1 = matrix + 1;可以编译通过（VS），但不严谨，p1指向了int，其实应该是数组
	printf("matrix[1][0] = %d\n", **p1);//注意双层数组，输出matrix[1][0]


	int* p2 = *(matrix + 1);//p2指向matrix第二个子数组的元素
	//相当于int* p2 = matrix[1];
	//相当于int* p2 = &matrix[1][0];
	printf("matrix[1][0] = %d\n", *p2);


	int* p3 = *(matrix + 1) + 5;//+5在子数组地址中进行
	printf("matrix[1][5] = %d\n", *p3);


	int num = *(*(matrix + 1) + 5);
	//相当于*(matrix[1]+5)
	//相当于matrix[1][5]
	printf("matrix[1][5] = %d\n", num);


	return 0;
}


//多维数组初始化
void init_test() {
	int four_d[2][2][3][3] = {
		{
			{
				{1,2,3},
				{4,5,6},
				{7,8,9}
			},
			{
				{10,11,12},
				{13,14,15},
				{16,17,18}
			}
		},
		{
			{
				{1,2,3},
				{4,5,6},
				{7,8,9}
			},
			{
				{10,11,12},
				{13,14,15},
				{16,17,18}
			}
		}
	};

	int another_4d[2][2][3][3] = {
		{
			{
				{100}
			}
		},
		{
			{
				{200}
			}
		}
	};
}


int lookup_keyword(char const* const desired_word, 
	char const* keyword_table[], int const size) {
	char const** kwp;
	for (kwp = keyword_table;kwp < keyword_table + size;++kwp) {
		if (strcmp(desired_word, *kwp) == 0) {
			return kwp - keyword_table;
		}
	}
	return -1;
}


int main62() {
	init_test();
	printf("\"if\"所在位置：%d\n", lookup_keyword("if", keyword, N_KEYWORD));

	return 0;
}