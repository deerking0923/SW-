#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "LeeGB_map.h"
#include "calculatorDST.h"
#include "LeeGB_cursor.h"
#include "Test_Moving.h"

int visited[101][101] = { 0, };
int weight[101][101] = { 0, };
int front = 0, rear = 0;
int one_srt_dist[101][101];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

void dfs(int x, int y, int npcX, int npcY) {
	one_srt_dist[y][x] = 1;

	if (one_srt_dist[npcY][npcX] == 1) return;
	if (y - 1 >= 0 && weight[y - 1][x] < weight[y][x] && one_srt_dist[y - 1][x] == 0
		&& weight[y - 1][x] != 0) dfs(x, y - 1, npcX, npcY);

	if (one_srt_dist[npcY][npcX] == 1) return;
	if (x - 1 >= 0 && weight[y][x - 1] < weight[y][x] && one_srt_dist[y][x - 1] == 0
		&& weight[y][x - 1] != 0) dfs(x - 1, y, npcX, npcY);

	if (one_srt_dist[npcY][npcX] == 1) return;
	if (y + 1 < HEIGHT && weight[y + 1][x] < weight[y][x] && one_srt_dist[y + 1][x] == 0
		&& weight[y + 1][x] != 0) dfs(x, y + 1, npcX, npcY);

	if (one_srt_dist[npcY][npcX] == 1) return;
	if (x + 1 < WIDTH && weight[y][x + 1] < weight[y][x] && one_srt_dist[y][x + 1] == 0
		&& weight[y][x + 1] != 0) dfs(x + 1, y, npcX, npcY);
}

void bfs(Queue* q, int x, int y, int dstX, int dstY) {

	rear++;
	q[rear].x = x;
	q[rear].y = y;
	q[rear].dist = 1;

	while (front < rear) {
		front++;
		for (int i = 0; i < 4; i++) {
			int nx = q[front].x + dx[i];
			int ny = q[front].y + dy[i];
			if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
				if (mapModel[ny][nx] == 0 && visited[ny][nx] == 0) {
					rear++;
					q[rear].x = nx;
					q[rear].y = ny;
					q[rear].dist = q[front].dist + 1;
					visited[ny][nx] = 1;
					weight[ny][nx] = q[rear].dist;
				}
			}
		}
		if (visited[dstY][dstX] == 1) { // 목표 위치의 visited의 좌표가 x좌표, y좌표가 1이면 bfs를 멈춤
			break;
		}
	}
}

int ShortestDistance(int npcX, int npcY, int dstX, int dstY) {

	//printf("[%d %d]", npcX, npcY);
	Queue* q = (Queue*)calloc(((WIDTH + 1) * (HEIGHT + 1)), sizeof(Queue));

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			one_srt_dist[i][j] = 0;
			weight[i][j] = 0;
			visited[i][j] = 0;
		}
	}
	weight[npcY][npcX] = 0;
	front = rear = 0;
	bfs(q, npcX, npcY, dstX, dstY); // 여기에 NPC의 (x,y)좌표를 집어넣는다.
	weight[npcY][npcX] = 1;
	int dist = q[rear].dist;
	free(q);

	dfs(dstX, dstY, npcX, npcY);

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (weight[i][j] == 0) {
				one_srt_dist[i][j] = -1;
			}
			if (weight[i][j] == 0 && mapModel[i][j] == 0) {
				one_srt_dist[i][j] = 0;
			}
		}
	}
	return dist;
}
