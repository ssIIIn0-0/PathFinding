/*
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// ������ �������� �������� ����
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

	// Q) 0�� -> 3�� ����?
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

// 2���� �迭ó�� ���Ϳ� ���͸� �־ ������ ���Ե� ���� �ѹ��� ����
// ������ ���� ��쿡 ����
void CreateGraph_2()
{
	struct Vertex
	{
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	// ����� ����� ���� ����
	// adjacent[n] : n��° ������ ����� ���� ���
	vector<vector<int>> adjacent(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// Q) 0�� -> 3�� ����?
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


// ���� ��ü�� ����
// ������ ���� ����� ����
// (2���Լ�ó�� �� ���, ���� ��� ��Ұ� ���� ����Ǿ� ������ �� ����� �迭�� ��� ��Ұ��� ������)
void CreateGraph_3()
{
	struct Vertex
	{
		// int data;
	};

	vector<Vertex> v;
	v.resize(6);

	// �д� ��� : adjacent[from][to]
	// ����� �̿��� �׷��� ǥ�� (2���� �迭)
	// �޸� �Ҹ� ��������, ���� ������ ����
	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// Q) 0�� -> 3�� ����?
	bool connected = adjacent[0][3];

	// ����ġ ���� ����
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


//#include <iostream>
//#include <iostream>
//#include <vector>
//#include <list>
//#include <stack>
//#include <queue>
//using namespace std;
//
//// DFS (Depth First Search) ���� �켱 Ž��
//// BFS (Breadth First Search) �ʺ� �켱 Ž��
//
//struct Vertex
//{
//    // int data;
//};
//
//vector<Vertex> vertices;
//vector<vector<int>> adjacent;
//// DFS �湮�� ����
//vector<bool> visited;
//// BFS �߰��� ����
//vector<bool> discovered;
//
//void CreateGraph()
//{
//    vertices.resize(6);
//    adjacent = vector<vector<int>>(6);
//
//    // ���� ����Ʈ
//    /*adjacent[0].push_back(1);
//    adjacent[0].push_back(3);
//    adjacent[1].push_back(0);
//    adjacent[1].push_back(2);
//    adjacent[1].push_back(3);
//    adjacent[3].push_back(4);
//    adjacent[5].push_back(4);*/
//
//    // ���� ���
//    adjacent = vector<vector<int>>
//    {
//       { 0, 1, 0, 1, 0, 0},
//       { 1, 0, 1, 1, 0, 0},
//       { 0, 0, 0, 0, 0, 0},
//       { 0, 0, 0, 0, 1, 0},
//       { 0, 0, 0, 0, 0, 0},
//       { 0, 0, 0, 0, 1, 0},
//    };
//}
//
//void Dfs(int here)
//{
//    // �湮!
//    visited[here] = true;
//    cout << "Visited : " << here << endl;
//
//    // ���� ����Ʈ version
//    // ��� ���� ������ ��ȸ�Ѵ�
//    //for (int i = 0; i < adjacent[here].size(); i++)
//    //{
//    //   int there = adjacent[here][i];
//    //   if (visited[there] == false)
//    //      Dfs(there);
//    //}
//
//    // ���� ��� version
//    // ��� ���� ������ ��ȸ�Ѵ�
//    for (int there = 0; there < 6; there++)
//    {
//        if (adjacent[here][there] == 0)
//            continue;
//
//        // ���� �湮���� ���� ���� ������ �湮�Ѵ�
//        if (visited[there] == false)
//            Dfs(there);
//    }
//}
//
//void DfsAll()
//{
//    visited = vector<bool>(6, false);
//
//    for (int i = 0; i < 6; i++)
//        if (visited[i] == false)
//            Dfs(i);
//}
//
//void Bfs(int here)
//{
//    // ������ ���� �߰� �Ǿ�����?
//    vector<int> parent(6, -1);
//    // ���������� ��ŭ ������ �ִ���?
//    vector<int> distance(6, -1);
//
//    // �߰��� ����here �� ���� ť
//    queue<int> q;
//    q.push(here);
//    discovered[here] = true;
//
//    // �ʱ� ����
//    parent[here] = here;
//    distance[here] = 0;
//
//    // ���� ����Ʈ version
//    //while (q.empty() == false)
//    //{
//    //    here = q.front();
//    //    q.pop();
//
//    //    cout << "Visited : " << here << endl;
//
//    //    for (int there : adjacent[here])
//    //    {
//    //        if (discovered[there])
//    //            continue;
//
//    //        q.push(there);
//    //        discovered[there] = true;
//
//    //        // �θ� ���� = here
//    //        parent[there] = here;
//    //        // ���������κ��� �Ÿ� = �θ� ������ �Ÿ� + 1
//    //        distance[there] = distance[here] + 1;
//    //    }
//    //}
//
//
//    // ���� ��� version
//    while (q.empty() == false)
//    {
//        here = q.front();
//        q.pop();
//
//        cout << "Visited : " << here << endl;
//
//        for (int there = 0; there < 6; there++)
//        {
//            // ������ �ȵǾ��ִ� ���
//            if (adjacent[here][there] == 0)
//                continue;
//            if (discovered[there])
//                continue;
//
//            q.push(there);
//            discovered[there] = true;
//
//            // �θ� ���� = here
//            parent[there] = here;
//            // ���������κ��� �Ÿ� = �θ� ������ �Ÿ� + 1
//            distance[there] = distance[here] + 1;
//        }
//    }
//}
//
//void BfsAll()
//{
//    for (int i = 0; i < 6; i++)
//        if (discovered[i] == false)
//            Bfs(i);
//}
//
//int main()
//{
//    CreateGraph();
//
//    //visited = vector<bool>(6, false);
//    //Dfs(0);
//
//    DfsAll();
//}