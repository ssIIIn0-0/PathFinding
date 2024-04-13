
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// Stack (LIFO Last-In-First-Out ���Լ���)
// �޸𸮿� ���� ���߿� �� �����Ͱ� ���� ��µǴ� ����
// �������� ġ�� �ǵ����� (ctrl+z)

template<typename T, typename Container = vector<T>>
// �����̳��� �⺻ Ÿ���� ����������, main���� ���������� �� �ٲ��� �� �ִ�.
class Stack
{
public:
    void push(const T& value)
    {
        _container.push_back(value);
    }

    /*
    // �� ����� ������� ����
    T pop()
    {
        T ret = _data[_size - 1];
        _size--;
        return ret; // T(const T&)
    }*/

    void pop()
    {
        _container.pop_back();
    }

    T& top()
    {
        return _container.back();
    }

    bool empty() { return _container.empty(); }
    int size() { return _container.size(); }
private:
    // vector<T> _container;
    // list<T> _container;
    Container _container;
};

// Queue (FIFO First-In-First-Out ���Լ���)
// ���� ��⿭
template<typename T>
class ListQueue
{
public:
    void push(const T& value)
    {
        _container.push_back(value);
    }

    void pop()
    {
        // _container.pop_front();  �̷��� ����
        // _container.erase(_container.begin());
        _container.pop_front();
    }

    T& front()
    {
        return _container.front();
    }

    bool empty() { return _container.empty(); }
    int size() { return _container.size(); }

private:
    // vector<T> _container;
    list<T> _container;
};


template<typename T>
class ArrayQueue
{
public:
    ArrayQueue()
    {
        //_container.resize(100);
    }

    void push(const T& value)
    {
        // �Ҵ���� �޸𸮰� �� ã���� üũ
        if (_size == _container.size())
        {
            // �޸� �߰�
            int newSize = max(1, _size * 2);
            vector<T> newData;
            newData.resize(newSize);

            // ������ ����
            for (int i = 0; i < _size; i++)
            {
                int index = (_front + i) % _container.size();
                newData[i] = _container[index];
            }

            _container.swap(newData);
            _front = 0;
            _back = _size;
        }

        _container[_back] = value;
        // ���� back�� �� ������ �޸𸮸� ����� �ʵ��� ������ �����ڸ� Ȱ���ؼ� �ٽ� �������� ��ȯ�ϵ��� ����
        _back = (_back + 1) % _container.size();
        _size++; // �������� ����

    }

    void pop()
    {
        _front = (_front + 1) % _container.size();
        _size--;
    }

    T& front()
    {
        return _container[_front];
    }

    bool empty() { return _size == 0; }
    int size() { return _size; }

private:
    vector<T> _container;

    int _front = 0;
    int _back = 0;
    int _size = 0;
};

int main()
{
    Stack<int, list<int>> s;

    // ����
    s.push(1);
    s.push(2);
    s.push(3);

    while (s.empty() == false)
    {
        // �ֻ��� ������ ���
        int data = s.top();

        // �ֻ��� ������ ����
        s.pop();

        cout << data << endl;
    }

    // int size = s.size();

    ArrayQueue<int> q;

    for (int i = 0; i < 100; i++)
        q.push(i);

    while (q.empty() == false)
    {
        int value = q.front();
        q.pop();
        cout << value << endl;
    }

    int size = q.size();

}
