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
    Car leadCar = Car(readFile(fname), stod(argv[2]), stod(argv[3]));
    while(leadCar.engineOn()){
        leadCar.calculateDeceleration();
        leadCar.calculateSpeed();
        leadCar.calculatePosition();
        road_monitor.push_new_data(leadCar.getNextBrakePosition());
        pair<double, double> speed = leadCar.getSpeed();
        if(road_monitor.emergencyBrake()){
            char message[MAX_MESSAGE_LEN];
            double coordinate = leadCar.getCoordinate();
            pair<double, double> deceleration = leadCar.getDeceleration();
            sprintf(message, "%d %lf %lf %lf %lf", coordinate, speed.first, speed.second, deceleration.first, deceleration.second);
            udp_client.sendMessage(message);
        }
        else{
            char v[MAX_MESSAGE_LEN];
            sprintf(v, "%lf", speed);
            udp_client.sendMessage(v);
        }
        sleep(SECONDS);
    }
    udp_client.sendMessage(off);
    return 0;    
}