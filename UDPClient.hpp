#include "dependencies.h"

class UDPClient{
    private:
        int sockfd;
        struct sockaddr_in server_address;
    public:
        UDPClient();
        int getSocket();
        struct sockaddr_in* getServerAddress();
};