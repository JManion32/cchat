#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <iostream>
#include <mutex>
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "./client.hpp"
#include "./auth_handler.hpp"
#include "./chat_handler.hpp"
#include "./shop_handler.hpp"
#include "socket_handler.hpp"
#include "../../shared/include/thread_handler.hpp"

// The central coordinator
class Server {
public:
    Server(int port);
    void handleEvent(SocketType client_fd, const json& msg);

private:
    AuthHandler auth_handler;
    ChatHandler chat_handler;
    ShopHandler shop_handler;

    std::vector<std::shared_ptr<Client>> global_clients;
    std::mutex global_clients_mutex;
    int SERVER_PORT;

    std::shared_ptr<Client> getClientByFD(SocketType fd);
    void* addClient(void* arg);
    void removeClient(SocketType sock);
    int getActiveCount();
    void clientThread(SocketType client_fd);
    void broadcastMessage(json& msg);
};

