#include "UDPClient.hpp"

UDPClient::UDPClient(){
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
    
    memset(&server_address, 0, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    cout << "server address: " << server_address.sin_addr.s_addr << endl;
    cout << "port: " << PORT << endl;
}

void UDPClient::sendMessage(char* message){
    size_t num_bytes = sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
                (const struct sockaddr *) &server_address, sizeof(server_address));
    cout << "num_bytes sent: " << num_bytes << endl;
}


UDPClient::~UDPClient(){
    close(sockfd);
}