#include "dependencies.h"

double calculateDistance(int x1, int y1, int x2, int y2){
    int x_distance = x1 - x2;
    int y_distance = y1 - y2;
    return sqrt(x_distance * x_distance + y_distance * y_distance);
}

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[MAXLEN];
      
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
      
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
      
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
      
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
      
    int len, n;
    len = sizeof(cliaddr);
    while(1){
        n = recvfrom(sockfd, (char *)buffer, MAXLEN, 
                MSG_WAITALL, (struct sockaddr *) &cliaddr, (socklen_t *)&len);
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }
}