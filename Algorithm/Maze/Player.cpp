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

	// ������ �����ϱ� ������ ��� ����
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
		// 1. ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;

		if (CanGo(pos + front[newDir]))
		{
			// ������ �������� 90�� ȸ��.
			_dir = newDir;
			// ������ �� �� ����.
			pos += front[_dir];

			_path.push_back(pos);
		}
		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��
		else if (CanGo(pos + front[_dir]))
		{
			// ������ �� �� ����.
			pos += front[_dir];

			_path.push_back(pos);
		}
		else
		{
			// ���� �������� 90�� ȸ��.
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	// �����չ�Ģ stack���
	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			// �����Դ� ���̶��, ����
			s.pop();
		else
			s.push(_path[i]);
	}

	// ������ ����
	if (_path.empty() == false) // �����Ͱ� �ִٸ�
		s.push(_path.back()); // ������ ��ǥ = ������

	// stackƯ���� �������� ������ ������ 

	// 1. ���� �ӽ� path�� �����͸� �����ϰ�,
	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}

	// 2. path�� ���� ������~����� �����̹Ƿ� �ٲ��ش�.
	std::reverse(path.begin(), path.end());

	_path = path;
}

void Player::Bfs()
{
	Pos pos = _pos;

	// ������ �����ϱ� ������ ��� ����
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1},	// RIGHT
	};

	// �߰��ߴ��� ����
	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false));
	
	// �ִܰŸ��� �ľ��ϱ� ���� �θ������� �ִ� ���� ����
	// vector<vector<Pos>> parent; = parent[A] = B; A(�ڽ�, ����)�� B(�θ�)������ �߰ߵ�
	map<Pos, Pos> parent;

	// �������� ��ǥ
	queue<Pos> q;

	// �ʱ� ����
	q.push(pos);
	discovered[pos.y][pos.x] = true;
	parent[pos] = pos;

	while (q.empty() == false)
	{
		pos = q.front();	// firstin firstout
		q.pop();

		// �湮!
		// ���� ���������
		if (pos == dest)
			break;
		
		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos + front[dir];
			// �� �� �ִ� �������� �ľ�
			if (CanGo(nextPos) == false)
				continue;
			// �̹� �߰��� �������� Ȯ��
			if (discovered[nextPos.y][nextPos.x] == true)
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			// �� ��ǥ pos�� �������� ������������ ã�� nextPos
			parent[nextPos] = pos;
		}
	}

	_path.clear();
	// �Ųٷ� �Ž��� �ö󰡾���
	pos = dest;	// ���� ��ġ�� ������

	while (true)
	{
		_path.push_back(pos);
		// �������� �ڽ��� �θ���
		// ���� ���������� �Դٸ�
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}

	std::reverse(_path.begin(), _path.end());
}
