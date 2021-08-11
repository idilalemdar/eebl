#include "RoadMonitor.hpp"

RoadMonitor::RoadMonitor(){
    this->i = 0;
}

double RoadMonitor::least_square_sum(){
    int i = 0;
    double x, y;
    double numerator, denominator;
    numerator = denominator = 0;
    double mean_y;
    double sum = 0;
    for (list<double>::iterator it = last_five.begin(); it != last_five.end(); ++it){
        sum += *it;
    }
    mean_y = sum / 5;
    for (list<double>::iterator it = last_five.begin(); it != last_five.end(); ++it){
        y = *it;
        x = (SECONDS * i++);
        numerator += (x - 0.2) * (y - mean_y);
        denominator += (x - 0.2) * (x - 0.2);
    }
    double slope = numerator / denominator;
    cout << "slope: " << slope << endl;
    return slope;
}

bool RoadMonitor::emergencyBrake(){
    cout << "road monitor speed: " << speed * MS_KMH << endl;
    return this->least_square_sum() >= SLOPE && this->speed >= 4.166666666666667;
}

void RoadMonitor::push_new_data(double brake_position, double new_speed){
    last_five.push_back(brake_position);
    if(last_five.size() == 6){
        last_five.pop_front();
    }
    speed = new_speed;
}