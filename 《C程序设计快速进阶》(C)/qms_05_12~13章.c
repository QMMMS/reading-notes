//概览：
//struct嵌套
//指向结构体的指针
//枚举
// 文件操作基础
//fgetc,putchar,fputc


#pragma warning(disable:4996)
#include <stdio.h>


struct Date{
	int month;
	int day;
	int year;
};


//struct嵌套
struct DUTer{
	int num;
	char name[20];
	char sex;
	struct Date birthday;
	float score;
};


int main51() {
	struct DUTer QMMMS;
	struct DUTer SMQ;
	
	QMMMS.birthday.year = 2002;
	SMQ = QMMMS;

	struct DUTer students[2] = {
		{001,"xa",'M',{1,2,2009},100},
		{002,"xb",'F',{1,2,2077},100},
	};
	//注意赋值方式

	printf("%d\n", students[1].birthday.year);

	//指向结构体的指针
	struct DUTer* erpi = &students[0];
	for (;erpi != &students[2];++erpi) {
		printf("%d\n", erpi->birthday.year);
		//等价于（*erpi）.birthday.year
	}
	

	printf("\n\npress any key to continue...");getch();
	return 0;
}


//枚举（感觉没什么用？）
enum my_scores {
	excellent, perfect, good, normal 
};


int main52() {
	enum my_scores sco[3];
	sco[0] = excellent;
	sco[1] = perfect;
	sco[2] = good;

	printf("%d\t%d\t%d", sco[0], sco[1], sco[2]);


	printf("\n\npress any key to continue...");getch();
	return 0;
}


//fgetc,putchar
int main53() {
	FILE* fp = fopen("file1.txt", "r");
	if (fp == NULL) {
		printf("can not open file!");
		getch();
		exit(1);
	}
	char ch = fgetc(fp);//??????待解决
	while (ch != EOF) {
		if (ch != " ") {
			putchar(ch);
		}
			ch = fgetc(fp);
	}
	fclose(fp);


	printf("\n\npress any key to continue...");getch();
	return 0;
}


//fputc
int main54() {
	FILE* fp = fopen("file2.txt", "w");
	if (fp == NULL) {
		printf("can not open file!");
		getch();
		exit(1);
	}
	char ch = getchar();
	while (ch != '\n') {
		fputc(ch, fp);
		ch = getchar();
	}
	fclose(fp);
	printf("file saved successfully!");


	printf("\n\npress any key to continue...");getch();
	return 0;
}
