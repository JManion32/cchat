#include "../../include/models/client.hpp"

Client::Client(SocketType sockfd, std::string name) {
    setSockfd(sockfd);
    setName(name);
    setToken(generateToken());
    setCredits(0);
}

std::string Client::generateToken() {
        int len = 24;
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        std::string tmp_s;
        tmp_s.reserve(len);

        for (int i = 0; i < len; ++i) {
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        
        return tmp_s;
}