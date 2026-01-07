#include "../../include/models/client.hpp"

Client::Client(SocketType sockfd, std::string name, std::string token, int credits) {
    setSockfd(sockfd);
    setName(name);
    setToken(token);
    setCredits(credits);
}