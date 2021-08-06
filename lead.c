#include "include.h"

int engineOn(){
    return 1;
}

int emergencyBrake(){

}

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in server_address;
    char *message[MAXLEN];
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }
    memset(&server_address, 0, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    while(engineOn()){
        // get data from sensors
        // do necessary calculations and pass the result to emergencyBrake()
        if(emergencyBrake()){
            sprintf(message, );
            sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
                (const struct sockaddr *) &server_address, sizeof(server_address));
        }
        usleep(MILLISECS);
    }
    close(sockfd);
    return 0;    
}