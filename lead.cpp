#include "UDPClient.hpp"
#include "RoadMonitor.hpp"
#include "Car.hpp"

vector<double> readFile(string fname){
    ifstream datafile(fname);
    vector<double> tokens;
    string line;
    if (datafile.is_open()){
        while (getline(datafile,line)){
            tokens.push_back(stod(line));
        }
        datafile.close();
    }
    return tokens;
}

int main(int argc, char *argv[]){
    char off[4] = "OFF";
    UDPClient udp_client = UDPClient("server_ip");
    RoadMonitor road_monitor = RoadMonitor();
    char *fname = argv[1];
    Car leadCar = Car(readFile(fname));
    while(leadCar.engineOn()){
        road_monitor.push_new_data(leadCar.getNextBrakePosition());
        leadCar.calculateDeceleration();
        leadCar.calculateSpeed();
        leadCar.calculatePosition();
        if(road_monitor.emergencyBrake()){
            char location[MAX_MESSAGE_LEN];
            pair<int, int> coordinates = leadCar.getCoordinates();
            sprintf(location, "%d %d", coordinates.first, coordinates.second);
            udp_client.sendMessage(location);
            
            char message[MAX_MESSAGE_LEN];
            double speed = leadCar.getSpeed();
            pair<double, double> deceleration = leadCar.getDeceleration();
            sprintf(message, "%f %f % f", speed, deceleration.first, deceleration.second);
            udp_client.sendMessage(message);
        }
        usleep(MILLISECS);
    }
    udp_client.sendMessage(off);
    return 0;    
}