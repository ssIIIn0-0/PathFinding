#include "pch.h"
#include "ConsoleHelper.h"
#include <iostream>

int main()
{
    uint64 lastTick = 0;
    while (true)
    {
#pragma region 프레임 관리
        const uint64 currentTick = ::GetTickCount64();
        const uint64 deltaTick = currentTick - lastTick;
        lastTick = currentTick;
#pragma endregion

        // 입력 : 마우스 입력

        // 로직 : 플레이어 움직임, 몬스터 이동

        // 렌더링 : 게임 세상을 그려주는

        ConsoleHelper::SetCursorPosition(0, 0);
        ConsoleHelper::ShowConsoleCursor(false);
        ConsoleHelper::SetCursorColor(ConsoleColor::RED);

        const char* TILE = "■";
        for (int32 y = 0; y < 25; y++)
        {
            for (int32 x = 0; x < 25; x++)
            {
                cout << TILE;
            }

            cout << endl;
        }
    }
}

