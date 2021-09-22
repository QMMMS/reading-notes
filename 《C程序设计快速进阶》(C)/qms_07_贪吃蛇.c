//将胜利分数改为16以上大概率出现bug,
// 理论能到20
//待解决

#pragma warning(disable:4996)
#include <stdio.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>


int head, tail;
int score = 0;
int gamespeed = 300;//游戏速度
int win = 16;//胜利分数

int main() {
	//初始化//////////////////////////////////////
	



	int tcsZB[2][20];
	for (int i = 0;i <= 3;++i) {
		tcsZB[0][i] = 1;//y
		tcsZB[1][i] = i + 1;//x
	}
	head = 3;
	tail = 0;
	
	char tcsQipan[22][22];
	for (int i = 1;i <= 20;++i) {
		for (int j = 1;j <= 20;++j) {
			tcsQipan[i][j] = ' ';
		}
	}

	for (int i = 0;i <= 21;++i) {
		tcsQipan[0][i] = '-';
		tcsQipan[21][i] = '-';
	}

	for (int i = 1;i <= 20;++i) {
		tcsQipan[i][0] = '|';
		tcsQipan[i][21] = '|';
	}

	for (int i = 1;i <= 3;++i) {
		tcsQipan[1][i] = '*';
	}
	tcsQipan[1][4] = '#';

	give_food(tcsQipan);
	//输出/////////////////////////////////////////////////////////////
	int direction = 77;

	while (direction != 'Q') {
		system("cls");

		for (int i = 0;i <= 21;++i) {
			for (int j = 0;j <= 21;++j) {
				printf("%c", tcsQipan[i][j]);
			}
			printf("\n");
		}
		printf("your score is:%d", score);
		if (score == win) {
			direction = 'Q';
			printf("\n\nCongratulations!\nYou win the game!\n");
		}

		//按键/////////////////////////////////////////////////////////////
		int timeover = 1;
		long start = clock();
		while (!kbhit() && (timeover = clock() - start<= gamespeed));

		if (timeover) {
			getch();
			direction = getch();
		}
		/*else {
			direction = direction;
		}*/

		if (!change_model(tcsQipan, tcsZB, direction)) {
			direction = 'Q';
		}
		
	}

	


	system("pause");
	return 0;
}


int change_model(char qi[22][22], int zb[2][20], char dir) {
	int x=0, y=0;
	if (dir == 72) {
		//up
		x = zb[0][head] - 1;
		y = zb[1][head];
	}
	else if (dir == 80) {
		//down
		x = zb[0][head] + 1;
		y = zb[1][head];
	}
	else if (dir == 75) {
		//left
		x = zb[0][head];
		y = zb[1][head] - 1;
	}
	else if (dir == 77) {
		x = zb[0][head];
		y = zb[1][head] + 1;
	}
	//检测碰撞///////////////////////////////////////

	if (qi[x][y] == 'o') {
		give_food(qi);
		if (tail == 0) {
			tail = 19;
		}
		else { tail = (tail - 1) % 20; }
		score++;
	}

	if (qi[x][y] == '-'|| qi[x][y] == '*'||qi[x][y] == '|') return 0;

	/////////////////////////////////////////
	qi[zb[0][tail]][zb[1][tail]] = ' ';
	tail = (tail + 1) % 20;
	qi[zb[0][head]][zb[1][head]] = '*';
	head = (head + 1) % 20;
	zb[0][head] = x;
	zb[1][head] = y;
	qi[zb[0][head]][zb[1][head]] = '#';
	return 1;

}

int give_food(char qi[22][22]) {
	srand(time(0));
	int x = rand() % 20 + 1;
	int y = rand() % 20 + 1;
	if (qi[x][y] = ' ') {
		qi[x][y] = 'o';
	}
	else {
		give_food(qi);
	}
	return 0;
}

