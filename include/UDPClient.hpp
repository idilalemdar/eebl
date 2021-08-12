#include "dependencies.hpp"

class UDPClient{
private:
    int sockfd;
    struct sockaddr_in server_address;
public:
    UDPClient(const char*);
    ~UDPClient();
    size_t sendMessage(char*);
};