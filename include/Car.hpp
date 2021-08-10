#include "dependencies.hpp"

class Car{
private:
    vector<double> brakePositions;
    vector<double> deceleration;
    vector<double> speed;
    vector<pair<int, int>> coordinates;
    size_t index;
public:
    Car();
    Car(vector<double>);
    ~Car();
    bool engineOn();
    double getNextBrakePosition();
    double getSpeed() const;
    pair<double, double> getDeceleration() const;
    pair<int, int> getCoordinates() const;
    double calculateDistance(int, int) const;
    void calculateDeceleration();
    void calculateSpeed();
    void calculatePosition();
};

