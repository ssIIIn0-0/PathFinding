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
vector<vector<int>> adjacent; // 인접 행렬

void CreateGraph()
{
    vertices.resize(6);
    // 가중치
    adjacent = vector<vector<int>>(6, vector<int>(6, -1));

    adjacent[0][1] = 15;
    adjacent[0][3] = 35;
    adjacent[1][0] = 15;
    adjacent[1][2] = 5;
    adjacent[1][3] = 10;
    adjacent[3][4] = 5;
    adjacent[5][4] = 5;
}

// DFS는 가중치에 대해 대응할 수 없다. 그래서 생긴 알고리즘이 다익스트라
void Dijikstra(int here)    // here : 본인, 정점값
{
    struct VertexCost
    {
        int vertex;
        int cost;
    };

    list<VertexCost> discovered; // 발견 목록
    // 원래는 큐로 구현했는데(먼저찾은 노드를 먼저 구현하기 위해)
    // 다익스트라는 먼저 찾은 것보다 가중치가 낮은 순서로 구현해야해서 list를 사용

    vector<int> best(6, INT32_MAX); // 각 정점별로 지금까지 발견한 최소 거리 (약간 DP같은거지)
    vector<int> parent(6, -1);      // 각 정점의 부모

    // 초기값(0)
    discovered.push_back(VertexCost{ here, 0 });
    best[here] = 0;
    parent[here] = here;

    while (discovered.empty() == false)
    {
        // 제일 좋은 후보를 찾는다
        // 리스트 대신 우선순위 큐(priority_queue를 사용할 수 있음(이게 더 효율적))
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

        // 위 for문을 통해 찾은 bestIt를 방문
        int cost = bestIt->cost;
        here = bestIt->vertex;
        discovered.erase(bestIt);   // 방문할거니까 discovered에서 삭제

        // 방문하기전 더 짧은 경로를 뒤늦게 찾았다면 스킵.
        if (best[here] < cost)
            continue;

        // 방문!
        for (int there = 0; there < 6; there++)
        {
            // 연결되지 않았으면 스킵.
            if (adjacent[here][there] == -1)
                continue;

            // 더 좋은 경로를 과거에 찾았으면 스킵.
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