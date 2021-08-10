#include "UDPServer.hpp"
#include "Car.hpp"

vector<double> tokenize(string original){
    vector<double> tokens;
    int index;
    int start = 0;
    while ((index = original.find(" ", start)) > 0){
        string sub = original.substr(start, index);
        tokens.push_back(stod(sub));
        start += sub.size() + 1;
    }
    return tokens;
}

int main(int argc, char *argv[]){
    
    UDPServer udp_server = UDPServer("server ip");
    Car followerCar = Car();
    string unit = "m";
    double distance;
    while(udp_server.on()){
        vector<double> lead_coordinates = tokenize(udp_server.receiveMessage());
        vector<double> lead_speed_deceleration = tokenize(udp_server.receiveMessage());
        distance = followerCar.calculateDistance(lead_coordinates[0], lead_coordinates[1]);
        if (distance > 1000){
            distance /= 1000;
            unit = "km";
        }
        cout << "Emergency Brake " + to_string(distance) + " " + unit + " ahead!" << endl;
        cout << "Speed:" + to_string(lead_speed_deceleration[0]) + 
            " decelerating from " + to_string(lead_speed_deceleration[1]) + 
            " to " + to_string(lead_speed_deceleration[2]) + " m/s^2." << endl;
    }
    return 0;
}