#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <Windows.h>

void SetCurrentCursorPos(int x, int y); // 원하는 좌표값으로 커서 이동
COORD GetCurrentCursorPos(void);        // 현재 커서 위치 반환
void RemoveCursor(void);                // 커서 출력 없애기

#endif // !__CURSOR_H__
