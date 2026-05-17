#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <mutex>

#include "../../shared/include/socket_handler.hpp"

class Client {
public:
    // Constructors
    Client(SocketType sockfd, std::string name, std::string token);

    // Setters
    void setSockfd(SocketType sockfd);
    void setName(std::string name);
    void setToken(std::string token);
    void setCredits(int credits);
    void ownTheme(int index);

    // Getters
    SocketType getSockfd() const { return sockfd; }
    std::string getName() const { return name; }
    std::string getToken() const { return token; }
    int getCredits() const { return credits; }
    bool isThemeOwned(int index) { return owned_themes[index]; }

    // Member Functions
    void incrementCredits();
    void subtractPrice(int price);

private:
    SocketType sockfd;
    std::string name;
    std::string token;
    int credits = 0;
    std::vector<bool> owned_themes = std::vector<bool>(9, false);

    std::mutex client_mutex;
};