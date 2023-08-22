#include <iostream>
using namespace std;

class Context {
public:
    int day;
};

class IHandler {
public:
    virtual bool HandleRequest(const Context &ctx) = 0;
    virtual bool CanHandle(const Context &ctx) = 0;
    virtual ~IHandler(){};

    void SetNextHandle(IHandler *next) { this->next = next; }
    bool Handle(const Context &ctx) {
        if (CanHandle(ctx)) {
            return HandleRequest();
        } else if (GetNextHandle()) {
            return GetNextHandle()->HandleRequest(ctx);
        }
        return false;
    }

protected:
    IHandler *GetNextHandle() { return next; }

private:
    IHandler *next;
};

class A : public IHandler {
public:
    virtual bool HandleRequest(const Context &ctx) override {}
    virtual bool CanHandle(const Context &ctx) override { return ctx.day <= 3; }
};

class B : public IHandler {
public:
    virtual bool HandleRequest(const Context &ctx) override {}
    virtual bool CanHandle(const Context &ctx) override {}
};

class C : public IHandler {
public:
    virtual bool HandleRequest(const Context &ctx) override {}
    virtual bool CanHandle(const Context &ctx) override {}
};

int main() {
    IHandler *h1 = new A();
    IHandler *h2 = new B();
    IHandler *h3 = new C();
    h1->SetNextHandle(h2);
    h2->SetNextHandle(h3);
    Context ctx;
    h1->Handle(ctx);
    return 0;
}