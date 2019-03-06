/// @file    queue_template.cc
/// @data    2019-01-09 18:13:49
 
#include <iostream>
 
using std::cout;
using std::endl;

template<class T, size_t kMax = 10>
class Queue {
public:
    Queue();
    ~Queue();
    void push(const T &);
    void pop();
    T front();
    T back();
    bool empty();
    bool full();
private:
    T *_data;
    size_t _front;
    size_t _rear;
};

template<class T, size_t kMax>
Queue<T, kMax>::Queue()  //这里也要有<T, kMax>
: _data(new T[kMax]())
, _front(0)
, _rear(0)
{}

template<class T, size_t kMax>
Queue<T, kMax>::~Queue() {
    delete []_data;
}

template<class T, size_t kMax>
void Queue<T, kMax>::push(const T &data) {
    if (!full()) {
        _data[_rear] = data;
        _rear = (_rear + 1) % kMax;
    }
    else
        cout << "队列满" << endl;
}

template<class T, size_t kMax>
void Queue<T, kMax>::pop() {
    if (!empty())
        _front = (_front + 1) % kMax;
    else
        cout << "队列空" << endl;
}

template<class T, size_t kMax>
T Queue<T, kMax>::front() {
    if (!empty())
        return _data[_front];
    else {
        cout << "队列空" << endl;
        T a;
        return a;
   }
}

template<class T, size_t kMax>
T Queue<T, kMax>::back() {
    if (!empty())
        return _data[(_rear + kMax -1) % kMax];
    else {
        cout << "队列空" << endl;
        T a;
        return a;
    }
}

template<class T, size_t kMax>
bool Queue<T, kMax>::empty() {
    return _front == _rear;
}

template<class T, size_t kMax>
bool Queue<T, kMax>::full() {
    return (_front == (_rear + 1) % kMax);
}

void test1() {
    Queue<int> q;
    q.pop();
    cout << q.front();
    q.back();
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);
    q.push(7);
    q.push(8);
    q.push(9);
    q.push(10);
    cout << "队头" << q.front() << endl;
    cout << "队尾" << q.back() << endl;
    q.push(100);
    q.pop();
    q.pop();
    q.push(10);
    q.push(11);
    cout << "push(11): " << endl;
    cout << "队头" << q.front() << endl;
    cout << "队尾" << q.back() << endl;
}

void test2() {
    Queue<char> q;
    q.pop();
    q.front();
    q.back();
    q.push('a');
    q.push('b');
    q.push('c');
    q.push('d');
    q.push('e');
    q.push('f');
    q.push('g');
    q.push('h');
    q.push('l');
    q.push('i');
    cout << "队头" << q.front() << endl;
    cout << "队尾" << q.back() << endl;
    q.push('z');
    q.pop();
    q.pop();
    q.push('i');
    q.push('z');
    cout << "push('z'): " << endl;
    cout << "队头" << q.front() << endl;
    cout << "队尾" << q.back() << endl;
}

int main() {
    cout << "test1:" << endl;
    test1();
    cout << endl;
    cout << "test2:" << endl;
    test2();
    cout << endl;

    return 0;
}
