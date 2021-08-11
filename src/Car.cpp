#include "Car.hpp"


Car::Car(vector<double> brakePositions, double init_speed, double init_pos){
    this->brakePositions = brakePositions;
    speed.push_back(kmh_to_ms(init_speed));
    coordinates.push_back(init_pos);
    index = 0;
}

Car::~Car(){}

bool Car::engineOn(){
    return index < brakePositions.size();
}

double Car::getNextBrakePosition(){
    return brakePositions[index++];
}

double Car::calculateDistance(int x){
    double lastPoint = coordinates[coordinates.size() - 1];
    return x - lastPoint;
}

pair<double, double> Car::getSpeed() const{
    pair<double, double> start_end;
    start_end.first = index >= 4 ? speed[index - 4] : speed[index];
    start_end.second = speed[index];
    return start_end;
}

pair<double, double> Car::getDeceleration() const{
    pair<double, double> start_end;
    start_end.first = deceleration[index - 4];
    start_end.second = deceleration[index];
    return start_end;
}

double Car::getCoordinate() const{
    return coordinates[coordinates.size() - 1];
}

void Car::calculateDeceleration(){
    deceleration.push_back(brakePositions[index] * 10);
}

void Car::calculateSpeed(){
    double last_speed = speed[index];
    speed.push_back(last_speed - deceleration[index] * SECONDS);
}

void Car::setFollowerSpeed(double lead_speed){
    speed.push_back(lead_speed);
}

void Car::setFollowerCoordinate(){
    double last_position = coordinates[coordinates.size() - 1];
    coordinates.push_back(last_position + speed[speed.size() - 1] * SECONDS);
}

void Car::calculatePosition(){
    double last_position = coordinates[index];
    coordinates.push_back(last_position + speed[index] * SECONDS);
}
