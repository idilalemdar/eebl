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

void UDPClient::sendMessage(char* message){
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
                (const struct sockaddr *) &server_address, sizeof(server_address));
}

void UDPClient::close_socket(){
    close(sockfd);
}