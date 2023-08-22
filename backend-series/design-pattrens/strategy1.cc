#include <iostream>
using namespace std;

class Context {};

class ProStrategy {
public:
    virtual double CalcPro(const Context &ctx) = 0;
    virtual ~ProStrategy(){};
};

class Promotion {
public:
    Promotion(ProStrategy *) {}
    ~Promotion() {}
    double CalcPromotion(const Context &ctx) { return strategy->CalcPro(ctx); }

private:
    ProStrategy *strategy;
};
