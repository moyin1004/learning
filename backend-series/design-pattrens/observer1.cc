#include <iostream>
using namespace std;

class DisplayA {
public:
    void Show(float temperature) {}
};
class DisplayB {
public:
    void Show(float temperature) {}
};
class DisplayC {
public:
    void Show(float temperature) {}
};

class WeatherData {};

class DataCenter {
public:
    float CalcTemperature() {
        WeatherData *data = GetWeatherData();
        float temper;
        return temper;
    }

private:
    WeatherData *GetWeatherData() {}
};

int main() {
    DataCenter *centor = new DataCenter;
    DisplayA *da = new DisplayA;
    DisplayB *db = new DisplayB;
    DisplayC *dc = new DisplayC;
    float temper = centor->CalcTemperature();
    da->Show(temper);
    db->Show(temper);
    dc->Show(temper);
    return 0;
}