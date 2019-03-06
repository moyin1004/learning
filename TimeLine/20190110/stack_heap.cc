/// @file    stack_heap.cc
/// @data    2019-01-10 20:16:21
 
#include<cstring>
#include <iostream>
 
using std::cout;
using std::endl;

class StackStu {
public:
//    StackStu(const char *name, int id)
//    : _name(name)
//    , _id(id)
//    {}    //新开空间，拷贝更好

    StackStu(const char *name, int id)
    : _name(new char[strlen(name) + 1]())
    , _id(id)
    {
        strcpy(_name, name);
    }

    void print() const {
        cout << "Student name: " << _name << endl;
        cout << "Student id: " << _id  << endl;
    }

private:
    void *operator new(size_t);
    void operator delete(void *);
//    const char *_name;
    char *_name;
    int _id;
};

class HeapStu {
public:
//    HeapStu(const char *name, int id)
//    : _name(name)
//    , _id(id)
//    {}

    HeapStu(const char *name, int id)
    : _name(new char[strlen(name) + 1]())
    , _id(id)
    {
        strcpy(_name, name);
    }

    void print() const {
        cout << "Student name: " << _name << endl;
        cout << "Student id: " << _id  << endl;
    }

private:
//    const char *_name;
    char *_name;
    int _id;
    ~HeapStu() {}
};

void test() {
    //HeapStu stu1("xiaoming", 11);  //error
    HeapStu *stu2 = new HeapStu("mingming", 22);  //这是字符串常量，在文字常量区
    stu2->print();

    //StackStu *stu3 = new StackStu("xiaohong", 33); //error
    StackStu stu4("honggong", 44);
    stu4.print();
}

int main() {
    test();
    return 0;
}
