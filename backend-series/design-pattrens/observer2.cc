#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class IDDisplay {
public:
    virtual void Show(float temperature) = 0;
    virtual ~IDDisplay();
};

// 放到其他文件
class DisplayA : public IDDisplay {
public:
    void Show(float temperature);
};
class DisplayB : public IDDisplay{
public:
    void Show(float temperature);
};

class WeatherData {

};

class DataCenter {
public:
    void Attach(IDDisplay *ob) {
        _obs.push_back(ob);
    }
    void Detach(IDDisplay *ob) {
        auto it = find(_obs.begin(), _obs.end(), ob);
        if (it != _obs.end()) {
            _obs.erase(it);
        }
    }
    void Notify() {
        float temper = CalcTemperature();
        for (auto it = _obs.begin(); it != _obs.end(); ++it) {
            (*it)->Show(temper);
        }
    }

protected:
    virtual float CalcTemperature() {
        WeatherData *data = GetWeatherData();
        float temper = 10;
        return temper;
    }

private:
    WeatherData *GetWeatherData();
    list<IDDisplay*> _obs;
};

int main() {
    DataCenter *center = new DataCenter;
    DisplayA *da = new DisplayA;
    DisplayB *db = new DisplayB;
    center->Attach(da);
    center->Attach(db);
    center->Notify();
    delete center;
    delete da;
    delete db;

    return 0;
}