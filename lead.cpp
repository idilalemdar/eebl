#include "UDPClient.hpp"
#include "RoadMonitor.hpp"

bool engineOn(int i, int sz){
    return i < sz;
}

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
    UDPClient udp_client = UDPClient();
    RoadMonitor road_monitor = RoadMonitor();

    vector<double> brakePositions = readFile("brake_positions.txt");
    int i = 0;
    int sz = brakePositions.size();
    while(engineOn(i, sz)){
        char message[MAXLEN];
        vector<int> coordinates = road_monitor.getCoordinates();
        sprintf(message, "%d %d", coordinates[0], coordinates[1]);
        udp_client.sendMessage(message);
        road_monitor.push_new_data(brakePositions[i++]);
        if(road_monitor.emergencyBrake()){
            double speed = road_monitor.getInitialSpeed();
            vector<double> deceleration = road_monitor.getDeceleration();
            sprintf(message, "Emergency Brake!\nBrake at speed:%f\nDeceleration rate:%f m/s^2 to %f m/s^2 in half a second",
                speed, deceleration[0], deceleration[1]);
            udp_client.sendMessage(message);
        }
        usleep(MILLISECS);
    }
    udp_client.close_socket();
    return 0;    
}