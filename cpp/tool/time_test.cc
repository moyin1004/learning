#include <iostream>
#include <chrono>
using namespace std;

int main() {
    chrono::sys_days t = chrono::sys_days{chrono::February/25/2022};
    t += chrono::days{7};
    auto d = chrono::year_month_day(t);
    cout << d << endl;
    cout << format("{:%B}/{}/{}\n", d.month(), d.day(), d.year()) << endl;
    return 0;
}