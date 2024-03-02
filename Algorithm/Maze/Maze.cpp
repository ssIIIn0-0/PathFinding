#include "pch.h"
#include "ConsoleHelper.h"
#include <iostream>
#include "Board.h"
#include "Player.h"

Board board;
Player player;

int main()
{
    ::srand(static_cast<unsigned>(time(nullptr)));

    board.Init(25, &player);
    player.Init(&board);

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
        player.Update(deltaTick);

        // 렌더링 : 게임 세상을 그려주는
        board.Render();
    }
}

