#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	// RightHand();
	// Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	/*if (_pathIndex >= _path.size())
		return;*/
	if (_pathIndex >= _path.size())
	{
		_board->GenerateMap();
		Init(_board);
		return;
	}


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

struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int32 f;	// f = g + h
	int32 g;
	Pos pos;
};

void Player::AStar()
{
	// 점수 매기기 (다익스트라의 가중치)
	// 최종점수 F = G + H
	// F : 최종점수 (작을 수록 좋고, 경로에 따라서 달라짐)
	// G : 시작점에서 목적지까지 이동하는데 드는 비용 (작을 수록 좋고, 경로에 따라서 달라짐)
	// H : 목적지에서 얼마나 가까운지 (작을 수록 좋고, 고정 : 같은 좌표일 경우 H값은 똑같음)

	Pos start = _pos;
	Pos dest = _board->GetExitPos();	// 도착지

	enum
	{
		DIR_COUNT = 4	// 상하좌우만 할경우 4, 대각선 포함이면 8
	};

	Pos front[] =
	{
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},		// RIGHT
		Pos {-1, -1},	// UP_LEFT
		Pos {1, -1},	// DOWN_LEFT
		Pos {1, 1},		// DOWN_RIGHT
		Pos {-1, 1},	// UP_RIGHT
	};

	// cost는 1이 기본인데 대각선의 경우 1.4가 되서 10으로 기본값 설정
	int32 cost[] =
	{
		10,		// UP
		10,		// LEFT
		10,		// DOWN
		10,		// RIGHT
		14,		// UP_LEFT
		14,		// DOWN_LEFT
		14,		// DOWN_RIGHT
		14		// UP_RIGHT
	};

	// 발견했는지 여부
	const int32 size = _board->GetSize();

	// 1) 발견 시스템 구현
	// - 이미 더 좋은 경ㅇ로를 찾았다면 스킵
	// 2) 뒤늦게 더 좋은 경로가 발견될 수 있음 -> 이 경우에 대한 예외 처리 필수
	// - openList에서 찾아서 제거 or
	// - pq에서 pop한 다음에 무시
	
	// ClosedList (방문을 끝낸 노드)
	// close[y][x] : (y, x)에 방문했는지 여부
	vector<vector<bool>> closed(size, vector<bool>(size, false));
	// best[y][x] : 지금까지 (y, x)에 대한 가장 좋은 비용 (작을수록 좋음)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));
	//부모 추적
	map<Pos, Pos> parent;

	// OpenList (아직 방문은 안했지만 발견한 노드)
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// 초기값 설정
	{
		int32 g = 0;
		// 출발점부터 도착지까지의 단순 거리 (피타고라스 정리써도 됨)
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));

		pq.push(PQNode{ g + h, g, start });
		best[start.y][start.x] = g + h;
		parent[start] = start;
	}

	while (pq.empty() == false)
	{
		// 제일 좋은 후보 (F값이 가장 작은 노드)
		PQNode node = pq.top();
		pq.pop();

		// 동일한 좌표를 여러 경로를 찾아서
		// 더 빠른 경로로 인해서 이미 방문(closed)된 경우 스킵

		if (closed[node.pos.y][node.pos.x])
			continue;
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// 방문
		closed[node.pos.y][node.pos.x] = true;

		// 목적지에 도착하면 종료
		if (node.pos == dest)
			break;


		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			// 갈 수 있는 지역이 맞는지 확인
			if (CanGo(nextPos) == false)
				continue;
			// 이미 방문한 곳이면 스킵
			if (closed[nextPos.y][nextPos.x])
				continue;

			// 비용 계산
			// g : 시작점을 기준으로 이동하는 비용
			int32 g = node.g + cost[dir];
			// h : 목적지를 기준으로 얼마만큼 떨어져 있는지에 대한 비용
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			// 다른 경로에서 더 빠른 길을 찾았으면 스킵
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// 예약 진행
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode{ g + h, g, nextPos });
			parent[nextPos] = node.pos;
		}
	}


	// 거꾸로 올라가는 부분
	Pos pos = dest;

	_path.clear();
	_pathIndex = 0;

	while (true)
	{
		_path.push_back(pos);

		if (pos == parent[pos])
			break;

		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
}

