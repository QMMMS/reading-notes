//概览：
//随机数、seed
//char 灵活转换
//显式转换
// switch example
//guess number
//数组入门
//统计字母


#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>//随机数
#include <time.h>//for seed
#define N 30


//char example
int main21() {
	int i;
	scanf("%d", &i);
	printf("%d\n", i);
	char enter = getchar();// get "Enter"
	char c = getchar();
	printf("%c\n", c);
	enter = getchar();
	putchar(getchar());
	printf("\n");

	char ch1 = 81;
	char ch2 = 77;
	char ch3 = 83;//char 可以灵活转换

	printf("From %c%c%c%c%c", ch1, ch2, ch2, ch2, ch3);

	printf("\n\npress any key to continue...");
	getch();
	return 0;
}


//transition example
int main22() {

	int n1 = 23, n2 = 2;
	double f1 = (n1 / n2);
	double f2 = (float)(n1) / n2;//显式转换,n1仍为int

	printf("%f\n", f1);
	printf("%f\n", f2);


	printf("\n\npress any key to continue...");
	getch();
	return 0;
}


// switch example
int main23() {
	char c;
	printf("input one character:");
	scanf("%c", &c);

	switch (c) {
	case 'a': case 'o': case 'i': case 'e': case 'u':
		printf("小写元音\n");
		break;
	case 'A': case 'E': case 'I': case 'O': case 'U':
		printf("大写元音\n");
		break;
	default:
		break;
		printf("其他字符\n");
	}


	printf("\n\npress any key to continue...");
	getch();
	return 0;
}


//do example
int main24() {
	int i = 1, sum = 0;
	do {
		sum += i;
		i++;
	} while (i != 101);
	printf("%d", sum);


	printf("\n\npress any key to continue...");
	getch();
	return 0;
}


//guess number
int main25() {
	printf("game start!");

	srand(time(0));
	int magic = rand() % 100 + 1;
	int guess,i=0;
	do{
		++i;
		printf("guess a nmber!(between1~100):");
		scanf("%d", &guess);
		if (guess > magic) {
			printf("too big!");
		}
		else if(guess < magic) {
			printf("too small!");
		}
	} while (guess != magic && i != 11);

	printf("\nyou have tried %d times\n", i);
	
	switch (i) {
	case 1: case 2:
		printf("OHHHHHHHHHHHHHH! you are a genius!!!!!");
		break;
	case 3: case 4:
		printf("smart!");
		break;
	case 5: case 6:
		printf("not bad!");
		break;
	case 7: case 8: case 9: case 10:
		printf("pass!");
		break;
	default:
		printf("you lose!");
		break;
	}
	


	printf("\n\npress any key to continue...");
	getch();
	return 0;
}


//数组入门
int main26() {
	int nums[5] = { 1,2,3,4,5 };
	char word1[] = "hello";
	for (int i = 0;i != 5;++i) {
		printf("%d\n", nums[i]);
		printf("%c\n", word1[i]);
	}


	printf("\n\npress any key to continue...");
	getch();
	return 0;
}


//统计字母
int main27() {
	char chars[N];
	int num[26] = { 0 };
	for (int i = 0;i != N;++i) {
		scanf("%c", &chars[i]);
	}

	for (int i = 0;i != N;++i) {
		if (chars[i] >= 'A' && chars[i] <= 'Z') {
			num[chars[i] - 'A']++;
		}
		if (chars[i] >= 'a' && chars[i] <= 'z') {
			num[chars[i] - 'a']++;
		}
	}

	for (int i = 0;i != 26;++i) {
		printf("%c:%d\t", 'A' + i, num[i]);
	}

	printf("\n\npress any key to continue...");getch();
	return 0;
}