#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

struct Vertex
{
    // int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent; // ���� ���

void CreateGraph()
{
    vertices.resize(6);
    // ����ġ
    adjacent = vector<vector<int>>(6, vector<int>(6, -1));

    adjacent[0][1] = 15;
    adjacent[0][3] = 35;
    adjacent[1][0] = 15;
    adjacent[1][2] = 5;
    adjacent[1][3] = 10;
    adjacent[3][4] = 5;
    adjacent[5][4] = 5;
}

// DFS�� ����ġ�� ���� ������ �� ����. �׷��� ���� �˰����� ���ͽ�Ʈ��
void Dijikstra(int here)    // here : ����, ������
{
    struct VertexCost
    {
        int vertex;
        int cost;
    };

    list<VertexCost> discovered; // �߰� ���
    // ������ ť�� �����ߴµ�(����ã�� ��带 ���� �����ϱ� ����)
    // ���ͽ�Ʈ��� ���� ã�� �ͺ��� ����ġ�� ���� ������ �����ؾ��ؼ� list�� ���

    vector<int> best(6, INT32_MAX); // �� �������� ���ݱ��� �߰��� �ּ� �Ÿ� (�ణ DP��������)
    vector<int> parent(6, -1);      // �� ������ �θ�

    // �ʱⰪ(0)
    discovered.push_back(VertexCost{ here, 0 });
    best[here] = 0;
    parent[here] = here;

    while (discovered.empty() == false)
    {
        // ���� ���� �ĺ��� ã�´�
        // ����Ʈ ��� �켱���� ť(priority_queue�� ����� �� ����(�̰� �� ȿ����))
        list<VertexCost>::iterator bestIt;
        int bestCost = INT32_MAX;

        for (auto it = discovered.begin(); it != discovered.end(); it++)
        {
            if (it->cost < bestCost)
            {
                bestCost = it->cost;
                bestIt = it;
            }
        }

        // �� for���� ���� ã�� bestIt�� �湮
        int cost = bestIt->cost;
        here = bestIt->vertex;
        discovered.erase(bestIt);   // �湮�ҰŴϱ� discovered���� ����

        // �湮�ϱ��� �� ª�� ��θ� �ڴʰ� ã�Ҵٸ� ��ŵ.
        if (best[here] < cost)
            continue;

        // �湮!
        for (int there = 0; there < 6; there++)
        {
            // ������� �ʾ����� ��ŵ.
            if (adjacent[here][there] == -1)
                continue;

            // �� ���� ��θ� ���ſ� ã������ ��ŵ.
            int nextCost = best[here] + adjacent[here][there];
            if (nextCost >= best[there])
                continue;

            discovered.push_back(VertexCost{ there, nextCost });
            best[there] = nextCost;
            parent[there] = here;
        }
    }
}

int main()
{
    CreateGraph();

    Dijikstra(0);
}