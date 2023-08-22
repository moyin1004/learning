#include <iostream>
using namespace std;

class ZooShow {
public:
    // 单一职责
    void Show() {
        Show0();
        Show1();
        Show2();
        Show3();
    }

protected:
    // 接口隔离
    virtual void Show0() { cout << "show0" << endl; }
    virtual void Show1() { cout << "show1" << endl; }
    virtual void Show2() { cout << "show2" << endl; }
    virtual void Show3() { cout << "show3" << endl; }
};

/*
变化的依赖稳定的
反向调用
应用程序 框架（nginx、skynet）：框架调用应用程序
*/
class ZooShowEx : public ZooShow {
public:
    // 依赖倒置
    virtual void Show1() override { cout << "Ex::show1" << endl; }
    virtual void Show3() override { cout << "Ex::show3" << endl; }
};
class ZooShowEx1 : public ZooShow {
public:
    // 依赖倒置
    virtual void Show0() override { cout << "Ex1::show0" << endl; }
    virtual void Show2() override { cout << "Ex1::show2" << endl; }
};

int main() {
    ZooShow *zs = new ZooShowEx;
    zs->Show();
    delete zs;
    zs = new ZooShowEx1;
    zs->Show();
    delete zs;
    return 0;
}