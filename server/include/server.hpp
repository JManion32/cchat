#pragma once
#include <vector>
#include <string>

#include "./models/client.hpp"

#include "../../shared/include/socket_handler.hpp"
#include "../../shared/include/thread_handler.hpp"
#include "../../shared/include/protocol.hpp"

void* client_thread(void* arg);

// Global list of connected clients
extern std::vector<Client> global_clients;
extern pthread_mutex_t global_clients_mutex;

void broadcastMessage(const Message& msg);
void removeClient(SocketType sock);

//====================================================
// AUTH REQUEST
//====================================================
void handleAuthRequest(SocketType client_fd, const std::string& username);
std::string generateToken();

//====================================================
// SEND CHAT
//====================================================
void handleChatSend(SocketType client_fd, const std::string& payload);

//====================================================
// PURCHASE REQUEST
//====================================================
void handlePurchaseRequest(SocketType client_fd, const std::string& payload);
