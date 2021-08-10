#include "dependencies.hpp"

class RoadMonitor{
    private:
        list<double> last_five;
        int i;
    protected:
        double least_square_sum();
    public:
        RoadMonitor();
        bool emergencyBrake();
        void push_new_data(double);
        double getInitialSpeed();
        vector<double> getDeceleration();
        vector<int> getCoordinates();
};