
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// Stack (LIFO Last-In-First-Out 후입선출)
// 메모리에 가장 나중에 들어간 데이터가 먼저 출력되는 형식
// 게임으로 치면 되돌리기 (ctrl+z)

template<typename T, typename Container = vector<T>>
// 컨테이너의 기본 타입은 벡터이지만, main에서 변수선언할 때 바꿔줄 수 있다.
class Stack
{
public:
    void push(const T& value)
    {
        _container.push_back(value);
    }

    /*
    // 이 방법은 사용하지 않음
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

// Queue (FIFO First-In-First-Out 선입선출)
// 게임 대기열
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
        // _container.pop_front();  이런건 없음
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
        // 할당받은 메모리가 다 찾는지 체크
        if (_size == _container.size())
        {
            // 메모리 추가
            int newSize = max(1, _size * 2);
            vector<T> newData;
            newData.resize(newSize);

            // 데이터 복사
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
        // 만약 back이 맨 마지막 메모리를 벗어나지 않도록 나머지 연산자를 활용해서 다시 앞쪽으로 순환하도록 구현
        _back = (_back + 1) % _container.size();
        _size++; // 데이터의 개수

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

    // 삽입
    s.push(1);
    s.push(2);
    s.push(3);

    while (s.empty() == false)
    {
        // 최상위 데이터 출력
        int data = s.top();

        // 최상위 데이터 삭제
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
