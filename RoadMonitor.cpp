#include "dependencies.h"
#include "RoadMonitor.hpp"

RoadMonitor::RoadMonitor(){
    this->i = 0;
}

double RoadMonitor::least_square_sum(){
    double sum_x, sum_xy, sum_x_square, sum_y;
    sum_x = sum_xy = sum_x_square = sum_y = 0;
    int i = 0;
    double x, y;
    for (list<double>::iterator it = last_five.begin(); it != last_five.end(); ++it){
        x = *it;
        y = (0.1 * i++);
        sum_x += x;
        sum_xy += x * y;
        sum_x_square = x * x;
        sum_y += y;
    }
    return (5 * sum_xy - sum_x * sum_y) / 
        (5 * sum_x_square - sum_x * sum_x);
}

bool RoadMonitor::emergencyBrake(){
    return this->least_square_sum() >= SLOPE;
}

void RoadMonitor::push_new_data(double brake_position){
    last_five.push_back(brake_position);
    if(i++ > 4)
        last_five.pop_front();
}