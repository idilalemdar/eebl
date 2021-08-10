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
    Car followerCar = Car(stod(argv[1]), stod(argv[2]));
    string unit = "m";
    double distance;
    clock_t begin = clock();
    clock_t end;
    while(udp_server.on()){
        vector<double> lead_data = tokenize(udp_server.receiveMessage());
        end = clock();
        followerCar.calculatePosition(double(end - begin));
        begin = end;
        distance = followerCar.calculateDistance(lead_data[0]);
        if (distance > 1000){
            distance /= 1000;
            unit = "km";
        }
        cout << "Emergency Brake " + to_string(distance) + " " + unit + " ahead!" << endl;
        cout << "Speed from" + to_string(ms_to_kmh(lead_data[1])) 
            + " to " + to_string(ms_to_kmh(lead_data[2])) + " km/h" + 
            + "\nDecelerating from " + to_string(lead_data[3])
            + " to " + to_string(lead_data[4]) + " m/s^2." << endl;
    }
    return 0;
}