#include <iostream>
using namespace std;

class Context {};

class CalcBouns {
public:
    CalcBouns(CalcBouns *c = nullptr) : cc(c) {}
    virtual ~CalcBouns() {}
    virtual double Calc(Context &ctx) { return 0.0; }

protected:
    CalcBouns *cc;
};

class MonthBouns : public CalcBouns {
public:
    MonthBouns(CalcBouns *c) : CalcBouns(c) {}
    ~MonthBouns() {}

    virtual double Calc(Context &ctx) override {
        double bouns = 1.0;
        return bouns += cc->Calc(ctx);
    }
};

class GroupBouns : public CalcBouns {
public:
    GroupBouns(CalcBouns *c) : CalcBouns(c) {}
    ~GroupBouns() {}

    virtual double Calc(Context &ctx) override {
        double bouns = 1.0;
        return bouns += cc->Calc(ctx);
    }
};

int main() {
    Context ctx1;
    CalcBouns *base = new CalcBouns();
    CalcBouns *month = new MonthBouns(base);
    month->Calc(ctx1);

    Context ctx2;
    GroupBouns *group = new GroupBouns(month);
    group->Calc(ctx2);
}