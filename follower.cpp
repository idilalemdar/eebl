#include "UDPServer.hpp"
#include "Car.hpp"


vector<double> tokenize(string original){
    vector<double> tokens;
    stringstream check1(original);
    string intermediate;
    while(getline(check1, intermediate, ' ')){
        tokens.push_back(stod(intermediate));
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
        if(lead_data.size() == 1){
            followerCar.setFollowerSpeed(stod(msg));
            followerCar.setFollowerCoordinate();
        }
        else {
            distance = followerCar.calculateDistance(lead_data[0]);
            if (distance > 1000){
                distance /= 1000;
                unit = "km";
            }
            cout << "Emergency Brake " << distance << " " << unit << " ahead!" << endl;
            cout << "Speed drops from " << followerCar.ms_to_kmh(lead_data[1])
                << " to " << followerCar.ms_to_kmh(lead_data[2]) << " km/h in half a second" << endl;
            cout << "Deceleration increases from " << lead_data[3] << " to " << lead_data[4] << " m/s^2." << endl;
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