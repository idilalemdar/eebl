#include "dependencies.hpp"

class Car{
private:
    vector<double> brakePositions;
    vector<double> deceleration;
    vector<double> speed;
    vector<double> coordinates;
    size_t index;
public:
    Car(double, double);
    Car(vector<double>, double, double);
    ~Car();
    bool engineOn();
    double getNextBrakePosition();
    pair<double, double> getSpeed() const;
    pair<double, double> getDeceleration() const;
    double getCoordinate() const;
    double calculateDistance(int);
    void calculateDeceleration();
    void calculateSpeed();
    void setFollowerSpeed(double);
    void setFollowerCoordinate();
    void calculatePosition();
    double kmh_to_ms(double);
    double ms_to_kmh(double);
};

