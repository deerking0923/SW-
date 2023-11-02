#include "LeeGB_map.h"

#include <stdio.h>	//디버그용
#include <stdlib.h> //rand(), srand() 함수
#include <time.h>	//time(NULL) 사용하기 위해

#include "LeeGB_cursor.h"

char mapModel[9][9] =
	{
		{1, 0, 1, 0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 1, 0, 0, 0, 1, 0, 1},

		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},

		{1, 0, 1, 0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 1, 0, 0, 0, 1, 0, 1}};

int *output_random_5_num_arr()
{
	int test[10] = {
		0,
	};
	int *num = (int *)malloc(sizeof(int) * 5);
	int random_num;
	int i = 0;

	// 중복된 값을 확인하기 위해 test[10]배열을 만듦
	// random_num 이 하나 나오면 test배열을 확인
	// test[random_num]의 값이 1이 아니면
	// test[random_num]의 값에 1대입 후 num배열에 random_num 값 추가
	// num 배열을 다 채울때 까지 위 과정 반복

	while (i < 5)
	{
		random_num = (rand() % 9); // 0 ~ 8 중에 랜덤한 수
		if (test[random_num] == 0)
		{
			test[random_num] = 1;
			num[i] = random_num;
			++i;
		}
	}

	// 디버그용
	/*for (i = 0; i < 5; ++i)
		printf(" %d", num[i]);
	printf("\n");*/

	return num;
}

void resetMap() // 왼쪽 위, 왼쪽 아래, 오른쪽 위, 오른쪽 아래 처음 시작할때, 십자가로 움직일 수 있도록 초기화
{
	mapModel[1 - 1][1 - 1] = 1;
	mapModel[1 - 1][1 + 1] = 1;
	mapModel[1 + 1][1 - 1] = 1;
	mapModel[1 + 1][1 + 1] = 1;

	mapModel[7 - 1][1 - 1] = 1;
	mapModel[7 - 1][1 + 1] = 1;
	mapModel[7 + 1][1 - 1] = 1;
	mapModel[7 + 1][1 + 1] = 1;

	mapModel[1 - 1][7 - 1] = 1;
	mapModel[1 - 1][7 + 1] = 1;
	mapModel[1 + 1][7 - 1] = 1;
	mapModel[1 + 1][7 + 1] = 1;

	mapModel[7 - 1][7 - 1] = 1;
	mapModel[7 - 1][7 + 1] = 1;
	mapModel[7 + 1][7 - 1] = 1;
	mapModel[7 + 1][7 + 1] = 1;
}

void generateMap() // 맵생성
{
	resetMap();

	srand(time(NULL));
	int *num = output_random_5_num_arr();
	/*
	0 = 0			/ 1 = 1				/ 2 = 2
	3 = 1 * 3 + 0	/ 4 = 1 * 3 + 1		/ 5 = 1 * 3 + 2
	6 = 2 * 3 + 0	/ 7 = 2 * 3 + 1		/ 8 = 2 * 3 + 2
	*/

	/*
	map의 구역을
	1 2 3
	4 5 6
	7 8 9 로 나누었을때
	*/
	// 4번구역 채우기
	for (int i = 0; i < 5; ++i)
	{
		mapModel[(num[i] / 3)][3 + num[i] % 3] = 1;
	}

	// 2번구역 채우기
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3)][num[i] % 3] = 1;
	}
	free(num);

	// 5번구역 채우기
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3)][3 + num[i] % 3] = 1;
	}
	free(num);

	// 8번구역 채우기
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[3 + (num[i] / 3)][6 + num[i] % 3] = 1;
	}
	free(num);

	// 6번구역 채우기
	num = output_random_5_num_arr();
	for (int i = 0; i < 5; ++i)
	{
		mapModel[6 + (num[i] / 3)][3 + num[i] % 3] = 1;
	}
	free(num);

	// debug
	/*for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j)
			printf(" %d", mapModel[i][j]);
		printf("\n");
	}*/
}

void drawMaps() // 맵을 화면에 출력
{
	int x, y;
	int cursX, cursY;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			cursX = x * 2 + GBOARD_ORIGIN_X; /*GBOARD_ORIGIN_X*/
			;
			cursY = y + GBOARD_ORIGIN_Y; /*GBOARD_ORIGIN_Y*/
			;

			SetCurrentCursorPos(cursX, cursY);

			if (mapModel[y][x] == 1)
			{
				printf("■");
			}
			else
			{
				printf("");
			}

			// draw_3_3maps(x, y, cursX, cursY);		//배열의 1칸을 화면의 3*3 크기로 표현
		}
	}
	SetCurrentCursorPos((GBOARD_ORIGIN_X /*BOARD_ORIGIN_X*/ + WIDTH * 2 + 1), HEIGHT + 1);
}

void draw_3_3maps(int x, int y, int cursX, int cursY)
{
	for (int yy = 0; yy < 3; ++yy)
	{
		for (int xx = 0; xx < 3; ++xx)
		{
			SetCurrentCursorPos(cursX + xx * 2, cursY + yy); // 네모 한칸이 커서 2개를 차지하므로 2 * xx를 하며 커서위치 변경

			if (mapModel[y][x] == 1)
			{
				printf("■");
			}
			else
			{
				printf("  ");
			}
		}
	}
}
