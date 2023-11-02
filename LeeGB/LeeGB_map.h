#ifndef __MAP_H__
#define __MAP_H__

#define WIDTH 9
#define HEIGHT 9

#define GBOARD_ORIGIN_X 0
#define GBOARD_ORIGIN_Y 0

extern char mapModel[HEIGHT][WIDTH];

int* output_random_5_num_arr();
void resetMap();
void generateMap();
void drawMaps();
void draw_3_3maps(int x, int y, int cursX, int cursY);

#endif
