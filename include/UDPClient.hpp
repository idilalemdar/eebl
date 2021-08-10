#include "dependencies.hpp"

class UDPClient{
    private:
        int sockfd;
        struct sockaddr_in server_address;
    public:
        UDPClient();
        void sendMessage(char*);
        void close_socket();
};