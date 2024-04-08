#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	// RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},	// RIGHT
	};

	while (pos != dest)
	{
		// 1. 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;

		if (CanGo(pos + front[newDir]))
		{
			// 오른쪽 방향으로 90도 회전.
			_dir = newDir;
			// 앞으로 한 보 전진.
			pos += front[_dir];

			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진.
			pos += front[_dir];

			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향으로 90도 회전.
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	// 오른손법칙 stack사용
	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			// 지나왔던 길이라면, 삭제
			s.pop();
		else
			s.push(_path[i]);
	}

	// 목적지 도착
	if (_path.empty() == false) // 데이터가 있다면
		s.push(_path.back()); // 마지막 좌표 = 목적지

	// stack특성상 뒤집혀서 나오기 때문에 

	// 1. 먼저 임시 path에 데이터를 저장하고,
	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	// 2. path는 현재 목적지~출발지 역순이므로 바꿔준다.
	std::reverse(path.begin(), path.end());

	_path = path;
}

void Player::Bfs()
{
	Pos pos = _pos;

	// 목적지 도착하기 전에는 계속 실행
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},	// RIGHT
	};

	// 발견했는지 여부
	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	
	// 최단거리를 파악하기 위해 부모정점을 넣는 벡터 설정
	// vector<vector<Pos>> parent; = parent[A] = B; A(자식, 본인)는 B(부모)로인해 발견됨
	map<Pos, Pos> parent;

	// 정점들의 좌표
	queue<Pos> q;

	// 초기 설정
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();	// firstin firstout
		q.pop();

		// 방문!
		// 최종 목적지라면
		if (pos == dest)
			break;
		
		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];
			// 갈 수 있는 지역인지 파악
			if (CanGo(nextPos) == false)
				continue;
			// 이미 발견한 지역인지 확인
			if (discovered[nextPos.y][nextPos.x] == true)
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			// 내 좌표 pos를 기준으로 동서남북으로 찾은 nextPos
			parent[nextPos] = pos;
		}
	}

	_path.clear();
	// 거꾸로 거슬러 올라가야함
	pos = dest;	// 현재 위치는 종착지

	while (true)
	{
		_path.push_back(pos);
		// 시작점은 자신이 부모임
		// 만약 시작점까지 왔다면
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
}
