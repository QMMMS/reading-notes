#pragma warning(disable:4996)
#include <stdio.h>

int layer = 0;


void hanoi(int n,char x,char y,char z) {
	if (n == 1) {
		printf("%c------>%c\n", x, z);
	}
	else {
		hanoi(n - 1, x, z, y);
		hanoi(1, x, y, z);
		hanoi(n - 1, y, x, z);
	}
}


void indent(int layer){
	for (int i = 1;i <= 2 * layer;++i) {
		printf("%c",' ');
	}
}

void hanoi_in_detail(int n, char x, char y, char z) {
	void indent(int layer);
	if (n == 1) {
		indent(layer);
		printf("hanoi(%d,%c,%c,%c) move: ", n, x, y, z);
		printf("%c------>%c\n", x, z);
		indent(layer);
		printf("hanoi(%d,%c,%c,%c) return \n", n, x, y, z);
		layer--;
	}
	else {
		indent(layer);
		printf("hanoi(%d,%c,%c,%c) invoke hanoi(%d,%c,%c,%c)\n", n, x, y, z, n - 1, x, z, y);
		layer++;
		hanoi_in_detail(n - 1, x, z, y);
		///////////////////////////////////////////////////////////////
		hanoi_in_detail(1, x, y, z);
		layer++;
		///////////////////////////////////////////////////////////////
		indent(layer);
		printf("hanoi(%d,%c,%c,%c) invoke hanoi(%d,%c,%c,%c)\n", n, x, y, z, n - 1, y, x, z);
		layer++;
		hanoi_in_detail(n - 1, y, x, z);

		indent(layer);
		printf("hanoi(%d,%c,%c,%c) return \n", n, x, y, z);
		layer--;
	}
}


int main6() {
	printf("please input number of disc:");
	int i;
	scanf_s("%d", &i);
	printf("start moving.......\n");
	hanoi(i, 'A', 'B', 'C');
	printf("*************************************\n");
	hanoi_in_detail(i, 'A', 'B', 'C');


	printf("\n\npress any key to continue...");getch();
	return 0;
}
