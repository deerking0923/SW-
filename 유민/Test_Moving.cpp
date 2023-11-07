#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Test_Moving.h"
#include "LeeGB_cursor.h"
#include "LeeGB_map.h"
#include "block_model.h"
#include "calculatorDST.h"

void ShowDstBlock(int x, int y) {
	COORD curPos = GetCurrentCursorPos();

	SetCurrentCursorPos(x * 2, y);
	printf("☆");
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void ShowBlock()
{
	COORD curPos = GetCurrentCursorPos();
	int curPosX = curPos.X;
	int curPosY = curPos.Y;
	printf("★");
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void DeleteBlock()
{
	COORD curPos = GetCurrentCursorPos();
	int curPosX = curPos.X;
	int curPosY = curPos.Y;
	printf("  ");
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

int ShiftLeft() {

	COORD curPos = GetCurrentCursorPos();

	int curPosX = curPos.X;
	int curPosY = curPos.Y;
	
	DeleteBlock();
	curPosX -= 2;
	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock();
	return 0;
	
}

int ShiftRight() {

	COORD curPos = GetCurrentCursorPos();

	int curPosX = curPos.X;
	int curPosY = curPos.Y;
	
	DeleteBlock();
	curPosX += 2;
	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock();

	return 0;

}

int BlockUp() {
	
	COORD curPos = GetCurrentCursorPos();

	int curPosX = curPos.X;
	int curPosY = curPos.Y;

	DeleteBlock();
	curPosY -= 1;
	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock();

	return 0;
}

int BlockDown() {

	COORD curPos = GetCurrentCursorPos();

	int curPosX = curPos.X;
	int curPosY = curPos.Y;

	DeleteBlock();
	curPosY += 1;
	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock();

	return 0;
}

int FindDstX() {
	srand((unsigned int)time(NULL));
	int x = rand() % 9;
	return x;
}
int FindDstY() {
	srand((unsigned int)time(NULL));
	int y = rand() % 9;
	return y;
}

int NpcMoving() {

	COORD curPos = GetCurrentCursorPos();

	int curPosX = curPos.X;
	int curPosY = curPos.Y;

	int dstX, dstY;
	int npcX, npcY;

	while (1) {
		dstX = FindDstX();
		dstY = FindDstY();
		if (mapModel[dstY][dstX] == 1) {
			continue;
		}
		else {
			break;
		}
	}

	ShowDstBlock(dstX, dstY);

	npcX = curPosX / 2;
	npcY = curPosY;

	int dist = ShortestDistance(npcX, npcY, dstX, dstY);
	int dx = npcX;
	int dy = npcY;

	SetCurrentCursorPos(curPosX, curPosY);

	while (1) {
		if (one_srt_dist[dy][dx + 1] == 1) {
			one_srt_dist[dy][dx] = 0;
			ShiftRight();
			dx += 1;
			Sleep(200);
		}
		if (one_srt_dist[dy][dx - 1] == 1) {
			one_srt_dist[dy][dx] = 0;
			ShiftLeft();
			dx -= 1;
			Sleep(200);
		}
		if (one_srt_dist[dy + 1][dx] == 1) {
			one_srt_dist[dy][dx] = 0;
			BlockDown();
			dy += 1;
			Sleep(200);
		}
		if (one_srt_dist[dy - 1][dx] == 1) {
			one_srt_dist[dy][dx] = 0;
			BlockUp();
			dy -= 1;
			Sleep(200);
		}
		if (dx == dstX && dy == dstY) {
			break;
		}
	}

	return 0;
}
