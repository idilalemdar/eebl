#include "UDPClient.hpp"

UDPClient::UDPClient(){
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
    
    memset(&server_address, 0, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.43.228");
    server_address.sin_port = htons(PORT);
}

size_t UDPClient::sendMessage(char* message){
    size_t num_bytes = sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
                (const struct sockaddr *) &server_address, (socklen_t)sizeof(server_address));
    return num_bytes;
}


UDPClient::~UDPClient(){
    close(sockfd);
}