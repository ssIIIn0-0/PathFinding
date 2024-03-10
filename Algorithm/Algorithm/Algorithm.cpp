#include <iostream>
#include <vector>
#include <list>
#include <stack>
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

    T pop()
    {
        T ret = _data[_size - 1];
        _size--;
        return ret; // T(const T&)
    }

    void pop()
    {
        _container.pop_back();
    }

    T& top()
    {
        return _container.back();
    }

    bool empty() { return _container.empty(); }
    bool size() { return _container.size(); }
private:
    // vector<T> _container;
    // list<T> _container;
    Container _container;
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

    int size = s.size();

}