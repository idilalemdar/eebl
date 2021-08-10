#include "dependencies.hpp"

class UDPServer{
private:
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    string msg;
public:
    UDPServer(const char*);
    ~UDPServer();
    bool on();
    string receiveMessage();
};
