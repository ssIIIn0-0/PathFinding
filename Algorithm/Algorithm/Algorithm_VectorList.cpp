/*
#include <iostream>
#include <vector>
#include <list>
using namespace std;

////// 동적배열, 벡터 //////
template<typename T>
class Vector
{
public:
    Vector()    // 생성자
    {

    }
    ~Vector()   // 소멸자
    {
        if (_data)
            delete[] _data;
    }

    void push_back(const T& value)
    {
        if (_size == _capacity)
        {
            int newCapacity = static_cast<int>(_capacity * 1.5);
            if (newCapacity == _capacity)
                newCapacity++;

            reserve(newCapacity);
        }

        // 데이터 저장
        _data[size] = value;

        // 데이터 개수 증가
        _size++;
    }
    void reserve(int capacity)
    {
        if (_capacity >= capacity)
            return;

        _capacity = capacity;

        T* newData = new T[_capacity];

        // 데이터 복사
        for (int i = 0; i < _size; i++)
            newData[i] = _data[i];

        if (_data)
            delete[] _data;

        // 교체
        _data = newData;
    }

    T& operator[](const int pos) { return _data[pos]; }

    int size() { return _size; }
    int capacity() { return _capacity; }

    void clear()
    {
        if (_data)
        {
            delete[] _data;
            _data = new T[_capacity];
        }
        _size = 0;
    }
private:
    T*      _data = nullptr; // 동적배열의 시작위치
    int     _size = 0;      // 실질적으로 사용하는 메모리 크기
    int     _capacity = 0; // 할당받은 총 메모리 크기

};

////// 연결 리스트 //////
template<typename T>
class Node
{
public:
    Node() : _prev(nullptr), _next(nullptr), _data(T())
    {

    }

    Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
    {

    }

public:
    Node* _prev;
    Node* _next;
    T     _data;
};

template<typename T>
class Iterator
{
public:
    Iterator() : _node(nullptr)
    {

    }

    Iterator(Node<T>* node) : _node(node)
    {

    }

    // ++it
    Iterator& operator++()
    {
        _node = _node->_next;
        return *this;
    }
    // it++
    Iterator operator++(int)
    {
        Iterator<T> temp = *this;
        _node = _node->_next;
        return temp;
    }
    // --it
    Iterator& operator--()
    {
        _node = _node->_prev;
        return *this;
    }
    // it--
    Iterator operator--(int)
    {
        Iterator<T> temp = *this;
        _node = _node->_prev;
        return temp;
    }

    // *it
    T& operator*()
    {
        return _node->_data;
    }

    bool operator==(const Iterator& other)
    {
        return _node == other._node;
    }

    bool operator!=(const Iterator& other)
    {
        return _node != other._node;
    }


public:
    Node<T>* _node;
};

template<typename T>
class List
{
public:
    List() : _size(0)
    {
        _head = new Node<T>();
        _tail = new Node<T>();

        _head->_next = _tail;
        _tail->_prev = _head;
    }

    ~List()
    {
        while (_size > 0)
            pop_back();

        delete _head;
        delete _tail;
    }

    void push_back(const T& value) // tail바로 앞에 데이터 추가
    {
        AddNode(_tail, value);
    }

    void pop_back()
    {
        RemoveNode(_tail->_prev);
    }

private:
    Node<T>* AddNode(Node<T>* before, const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* prevNode = before->_prev;

        prevNode->_next = newNode;
        newNode->_prev = prevNode;

        newNode->_next = before;
        before->_prev = newNode;

        _size++;

        return newNode;
    }

    Node<T>* RemoveNode(Node<T>* node)
    {
        Node<T>* prevNode = node->_prev;
        Node<T>* nextNode = node->_next;

        prevNode->_next = nextNode;
        nextNode->_prev = prevNode;

        delete node;

        _size--;

        return nextNode;
    }

    int size() { return _size; }

public:
    using iterator = Iterator<T>;

    iterator begin() { return iterator(_head->_next); }
    iterator end() { return iterator(_tail); }

    iterator insert(iterator it, const T& value)
    {
        Node<T>* node = AddNode(it._node, value);
        return iterator(node);
    }
    iterator erase(iterator it)
    {
        Node<T>* node = RemoveNode(it._node);
        return iterator(node);
    }


private:
    Node<T>* _head;
    Node<T>* _tail;
    int      _size;
};


int main()
{
    ////// 동적배열, 벡터 //////
    vector<int>v;

    v.resize(10);   // 실제 데이터 개수(_size)를 조정
    v.reserve(100); // capacity를 조절, 처음부터 100정도로 지정을 해두면, size가 100이 될때까지는 capacity가 안정적이라 좋음
    for (int i = 0; i < 100; i++)
    {
        v.push_back(i);
        cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
    }

    v.clear();
    cout << v.size() << " " << v.capacity() << endl;
 
    ////// 연결 리스트 //////
    List<int> li;

    List<int>::iterator eraselt;

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            eraselt = li.insert(li.end(), i);
        }
        else
        {
            li.push_back(i);
        }
    }

    li.pop_back();

    li.erase(eraselt);

    for (List<int>::iterator it = li.begin(); it != li.end(); it++)
    {
        cout << (*it) << endl;
    }
}
*/
