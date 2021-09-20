#pragma warning(disable:4996)
#include <stdio.h>
#define N 6


int main3() {
	int array[N] = { 8,4,3,9,6,2 };
	for (int j = N - 1;j >= 0;--j) {
		for (int i = 0;i != j;++i) {
			if (array[i] > array[i + 1]) {
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}

	for (int i = 0;i != N;++i) {
		printf("%d\t", array[i]);
	}


	printf("\n\npress any key to continue...");getch();
	return 0;
}