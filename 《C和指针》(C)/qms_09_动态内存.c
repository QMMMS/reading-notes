//玩不明白，待完善

#include <stdio.h>
#include "alloc.h"
#undef malloc//?????

//不易发生错误的内存分配器
void* alloc(size_t size) {
	void* new_mem;

	new_mem = malloc(size);
	if (new_mem == NULL) {
		printf("out of memery!");
		exit(1);
	}
	return new_mem;
}


void function() {
	int* new_memery;
	new_memery = MALLOC(25, int);
}


int main9() {
	/*.....玩不明白，待完善....*/
	return 0;
}