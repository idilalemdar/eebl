#include "dependencies.h"
#include "UDPClient.hpp"

UDPClient::UDPClient(){
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
    
    memset(&server_address, 0, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
}

int UDPClient::getSocket(){
    return this->sockfd;
}

struct sockaddr_in* UDPClient::getServerAddress(){
    return &server_address;
}
