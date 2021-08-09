#include "dependencies.h"
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
    char message[MAXLEN];
    UDPClient udp_client = UDPClient();
    RoadMonitor road_monitor = RoadMonitor();

    vector<double> brakePositions = readFile("brake_positions.txt");
    int i = 0;
    int sz = brakePositions.size();
    
    while(engineOn(i, sz)){
        if(road_monitor.emergencyBrake()){
            sprintf(message, );
            sendto(udp_client.getSocket(), (const char *)message, strlen(message), MSG_CONFIRM,
                (const struct sockaddr *) udp_client.getServerAddress(), *udp_client.getServerAddress());
        }
        usleep(MILLISECS);
    }
    close(sockfd);
    return 0;    
}