#ifndef DEPENDENCIES_HPP
#define DEPENDENCIES_HPP

#define PORT_SERVER 8080
#define PORT_CLIENT 8080
#define MAX_MESSAGE_LEN 1024
#define SECONDS 0.1
#define SLOPE 0.8
#define MS_KMH 3.6

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

double kmh_to_ms(double kmh){
    return kmh * (1.0 / MS_KMH);
}

double ms_to_kmh(double ms){
    return ms * MS_KMH;
}

using namespace std;

#endif