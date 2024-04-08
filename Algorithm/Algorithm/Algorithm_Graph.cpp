/*
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// 정점을 기준으로 간선관계 구현
void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*> edges;
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// Q) 0번 -> 3번 연결?
	bool connected = false;
	for (Vertex* edge : v[0].edges)
	{
		if (edge == &v[3])
		{
			connected = true;
			break;
		}
	}
}

// 2차원 배열처럼 벡터에 벡터를 넣어서 정점에 포함된 간선 한번에 구현
// 연결이 적은 경우에 유리
void CreateGraph_2()
{
	struct Vertex
	{
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	// 연결된 목록을 따로 관리
	// adjacent[n] : n번째 정점과 연결된 정점 목록
	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// Q) 0번 -> 3번 연결?
	bool connected = false;
	for (int vertex : adjacent[0])
	{
		if (vertex == 3)
		{
			connected = true;
			break;
		}
	}

	// STL
	vector<int>& adj = adjacent[0];
	bool connected2 = (std::find(adj.begin(), adj.end(), 3) != adj.end());
}


// 간선 자체를 구현
// 연결이 많은 경웅에 유리
// (2번함수처럼 할 경우, 거의 모든 요소가 서로 연결되어 있으면 각 요소의 배열에 모든 요소값이 들어가야함)
void CreateGraph_3()
{
	struct Vertex
	{
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	// 읽는 방법 : adjacent[from][to]
	// 행렬을 이용한 그래프 표현 (2차원 배열)
	// 메모리 소모가 심하지만, 빠른 접근이 가능
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// Q) 0번 -> 3번 연결?
	bool connected = adjacent[0][3];

	// 가중치 관련 벡터
	vector<vector<int>> adjacent2 =
	{
		vector<int> { -1, 15, -1, 35, -1, -1 },
		vector<int> { 15, -1, +5, 10, -1, -1 },
		vector<int> { -1, -1, -1, -1, -1, -1 },
		vector<int> { -1, -1, -1, -1, +5, -1 },
		vector<int> { -1, -1, -1, -1, -1, -1 },
		vector<int> { -1, -1, -1, -1, +5, -1 },
	};
}

int main()
{
	CreateGraph_1();
	CreateGraph_2();
	CreateGraph_3();
}
*/