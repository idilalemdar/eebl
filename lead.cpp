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

void monitor(Car& leadCar){
    char off[4] = "OFF";
    UDPClient udp_client = UDPClient();
    RoadMonitor road_monitor = RoadMonitor();
    while(leadCar.engineOn()){
        leadCar.calculateDeceleration();
        leadCar.calculateSpeed();
        leadCar.calculatePosition();
        pair<double, double> speed = leadCar.getSpeed();
        road_monitor.push_new_data(leadCar.getNextBrakePosition(), speed.second);
        if(road_monitor.emergencyBrake()){
            char message[MAX_MESSAGE_LEN];
            double coordinate = leadCar.getCoordinate();
            pair<double, double> deceleration = leadCar.getDeceleration();
            sprintf(message, "%f %lf %lf %lf %lf", coordinate, speed.first, speed.second, deceleration.first, deceleration.second);
            udp_client.sendMessage(message);
        }
        else {
            char v[MAX_MESSAGE_LEN];
            sprintf(v, "%lf", speed.first); // send data from 500 ms ago, as it is the minimal human reaction time
            udp_client.sendMessage(v);
        }
        usleep(SECONDS * 1000000);
    }
    udp_client.sendMessage(off);
}

int main(int argc, char *argv[]){
    char *fname = argv[1];
    Car leadCar = Car(readFile(fname), stod(argv[2]), stod(argv[3]));
    
    monitor(leadCar);
    
    return 0;    
}