#include <time.h>
#include <stdio.h>

int current_game_time;

int main(void)
{
    current_game_time = clock(); // main문 실행 후 시간을 current_game_time 에 저장, 시간을 알고 싶을때마다 current_game_time = clock()을 사용해서 게임 시간을 알 수 있다.
}