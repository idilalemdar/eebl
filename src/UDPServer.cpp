#include "UDPServer.hpp"

UDPServer::UDPServer(){
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
      
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.43.228");
    servaddr.sin_port = htons(PORT);

    if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

UDPServer::~UDPServer(){
    close(sockfd);
}

string UDPServer::receiveMessage(){
    socklen_t len = sizeof(cliaddr);
    char buffer[MAX_MESSAGE_LEN];
    int n = recvfrom(sockfd, (char *)buffer, MAX_MESSAGE_LEN, 
                MSG_WAITALL, (struct sockaddr *) &cliaddr, (socklen_t *)&len);
    buffer[n] = '\0';
    string msg = buffer;
    return msg;
}