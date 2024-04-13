#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
    void push(const T& data)
    {
        // �켱 �� �������� �����ش�(�� �������� push_back)
        _heap.push_back(data);

        // ������� ����
        int now = static_cast<int>(_heap.size()) - 1;
        // ��Ʈ ������
        while (now > 0)
        {
            // �θ� ���� ���ؼ� �� �۰ų� ũ�� �й�
            int next = (now - 1) / 2;
            // if (_heap[now] < _heap[next]) // �� ��� ��ü�� _predicate�� less�϶��� ����
            if (_predicate(_heap[now], _heap[next]))
                break;

            // ������ ��ü
            // STL swap ���
            ::swap(_heap[now], _heap[next]);
            now = next;
        }
    }

    void pop()
    {
        _heap[0] = _heap.back();
        _heap.pop_back();

        int now = 0;

        while (true)
        {
            int left = 2 * now + 1;
            int right = 2 * now + 2;

            // ������ ������ ���
            if (left >= (int)_heap.size())
                break;

            int next = now;

            // ���ʰ� ��
            if (_predicate(_heap[next], _heap[left]))
                next = left;

            // �� �� ���ڸ� �����ʰ� ��
            if (right < (int)_heap.size() && _predicate(_heap[next], _heap[right]))
                next = right;

            // ����/������ �� �� ���� ������ ������ ����
            if (next == now)
                break;

            ::swap(_heap[now], _heap[next]);
            now = next;
        }
    }

    T& top()
    {
        return _heap[0];
    }

    bool empty()
    {
        return _heap.empty();
    }

private:
    Container _heap = {};
    Predicate _predicate = {};
};


int main()
{
    // ������������
    PriorityQueue<int, vector<int>, greater<int>> pq;
    // ������������
    // priority_queue<int> pq;
    // PriorityQueue<int, vector<int>, less<int>> pq;
    pq.push(100);
    pq.push(300);
    pq.push(200);
    pq.push(500);
    pq.push(400);

    while (pq.empty() == false)
    {
        int value = pq.top();
        pq.pop();

        cout << value << endl;
    }
}