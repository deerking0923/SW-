#ifndef __MAP_H__
#define __MAP_H__

#include "../define_state.h"

extern char mapModel[HEIGHT][WIDTH];

int *output_random_5_num_arr();
void resetMap();
void generateMap();
void drawMaps();
void draw_3_3maps(int x, int y, int cursX, int cursY);

int checkObject_can_go(int x, int y); // 인자로 주어진 좌표로 이동할 수 있는지
int checkObject_bomb(int x, int y);   // 인자로 주어진 좌표가 폭발범위인지
int checkObject_box(int x, int y);    // 인자로 주어진 좌표에 부실 수 있는 장애물이 있는지
int checkObject_wall(int x, int y);   // 인자로 주어진 좌표에 부실 수 없는 장애물이 있는지

#endif
