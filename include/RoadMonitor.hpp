#include "dependencies.hpp"

class RoadMonitor{
private:
    list<double> last_five;
    int i;
    double speed;
public:
    RoadMonitor();
    double least_square_sum();
    bool emergencyBrake();
    void push_new_data(double, double);
};