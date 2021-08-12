#include "dependencies.hpp"

class UDPServer{
private:
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
public:
    UDPServer(const char*);
    ~UDPServer();
    string receiveMessage();
};
