#include "UDPServer.hpp"
#include "Car.hpp"


vector<double> tokenize(string original){
    vector<double> tokens;
    size_t index;
    size_t start = 0;
    while ((index = original.find(" ", start)) != string::npos){
        string sub = original.substr(start, index);
        tokens.push_back(stod(sub));
        start += sub.size() + 1;
    }
    return tokens;
}

void listen(Car& followerCar){
    UDPServer udp_server = UDPServer();
    string unit = "m";
    double distance;
    cout << "Follower car is listening..." << endl;
    while(true){
        string msg = udp_server.receiveMessage();
        if(msg == "OFF") break;
        vector<double> lead_data = tokenize(msg);
        if(lead_data.size() == 0){
            followerCar.setFollowerSpeed(stod(msg));
            followerCar.setFollowerCoordinate();
        }
        else {
            distance = followerCar.calculateDistance(lead_data[0]);
            if (distance > 1000){
                distance /= 1000;
                unit = "km";
            }
            cout << "Emergency Brake " + to_string(distance) + " " + unit + " ahead!" << endl;
            cout << "Speed from" + to_string(followerCar.ms_to_kmh(lead_data[1])) 
                + " to " + to_string(followerCar.ms_to_kmh(lead_data[2])) + " km/h" + 
                + "\nDecelerating from " + to_string(lead_data[3])
                + " to " + to_string(lead_data[4]) + " m/s^2." << endl;
            followerCar.setFollowerSpeed(lead_data[1]);
            followerCar.setFollowerCoordinate();
        }
    }
}
int main(int argc, char *argv[]){
    Car followerCar = Car(stod(argv[1]), stod(argv[2]));

    listen(followerCar);

    return 0;
}