#ifndef __MAP_H__
#define __MAP_H__

#include "../define_state.h"

extern char mapModel[HEIGHT][WIDTH];

int *output_random_5_num_arr();                        // 랜덤 맵 생성할때 사용 (랜덤한 숫자 5개 반환) (generateMap 함수에서 호출 함)
void resetMap();                                       // 초기 맵 상태로 초기화 (generateMap 함수에서 호출 함)
void generateMap();                                    // 맵 생성
void drawMaps();                                       // 맵 출력
void draw_3_3maps(int x, int y, int cursX, int cursY); // 1 : 3 비율로 크기 늘리기

int checkObject_can_go(int x, int y); // 인자로 주어진 좌표로 이동할 수 있는지
int checkObject_bomb(int x, int y);   // 인자로 주어진 좌표가 폭발범위인지
int checkObject_box(int x, int y);    // 인자로 주어진 좌표에 부실 수 있는 장애물이 있는지
int checkObject_wall(int x, int y);   // 인자로 주어진 좌표에 부실 수 없는 장애물이 있는지

#endif
