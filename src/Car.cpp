#include "Car.hpp"

Car::Car(){}

Car::Car(vector<double> brakePositions){
    this->brakePositions = brakePositions;
    index = 0;
}

Car::~Car(){}

bool Car::engineOn(){
    return index < brakePositions.size();
}

double Car::getNextBrakePosition(){
    return brakePositions[index++];
}

double Car::calculateDistance(int x, int y) const{
    pair<int, int> lastPoint = coordinates[coordinates.size() - 1];
    int x_distance = lastPoint.first - x;
    int y_distance = lastPoint.second - y;
    return sqrt(x_distance * x_distance + y_distance * y_distance);
}

double Car::getSpeed() const{
    return speed[speed.size() - 5];
}

pair<double, double> Car::getDeceleration() const{
    pair<double, double> start_end;
    start_end.first = deceleration[deceleration.size() - 5];
    start_end.second = deceleration[deceleration.size() - 1];
    return start_end;
}

pair<int, int> Car::getCoordinates() const{
    return coordinates[coordinates.size() - 1];
}

void Car::calculateDeceleration(){

}

void Car::calculateSpeed(){

}

void Car::calculatePosition(){

}