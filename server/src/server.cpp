#include "../include/server.hpp"
#include <algorithm>
#include <string>
#include <iostream>

std::vector<Client> global_clients;
pthread_mutex_t global_clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Send message to all connected clients
void broadcastMessage(const Message& msg) {
    std::vector<uint8_t> data = Protocol::serialize(msg);

    pthread_mutex_lock(&global_clients_mutex);
    for (auto& c : global_clients) {
        socket_send(c.getSockfd(), reinterpret_cast<const char*>(data.data()), data.size());
    }
    pthread_mutex_unlock(&global_clients_mutex);
}

// When a client disconnects
void removeClient(SocketType sock) {
    pthread_mutex_lock(&global_clients_mutex);
    global_clients.erase(
        std::remove_if(global_clients.begin(), global_clients.end(),
            [sock](const Client& client) { return client.getSockfd() == sock; }),
        global_clients.end()
    );
    pthread_mutex_unlock(&global_clients_mutex);
}

Client* getClientByFD(SocketType fd) {
    for (auto& c : global_clients) {
        if (c.getSockfd() == fd)
            return &c;
    }
    return nullptr;
}

//====================================================
// AUTH REQUEST
//====================================================
void handleAuthRequest(SocketType client_fd, const std::string& username) {
    pthread_mutex_lock(&global_clients_mutex);

    Client* client = getClientByFD(client_fd);
    if (!client) {
        pthread_mutex_unlock(&global_clients_mutex);
        std::cerr << "[SERVER] AUTH_REQUEST: Client not found\n";
        return;
    }

    pthread_mutex_unlock(&global_clients_mutex);

    std::cout << "[SERVER] AUTH: user='" << username 
              << "' token=" << client->getToken() << " credits=" << client->getCredits() << "\n";

    // Build AUTH_RESPONSE
    Message resp(MessageType::AUTH_RESPONSE, client->getToken());
    auto bytes = Protocol::serialize(resp);
    socket_send(client_fd, (const char*)bytes.data(), bytes.size());
}

//====================================================
// SEND CHAT
//====================================================
void handleChatSend(SocketType client_fd, const std::string& payload) {
    // Expected payload format:
    // "<token>|<credits>|<message>"

    size_t pos1 = payload.find('|');
    size_t pos2 = payload.find('|', pos1 + 1);

    if (pos1 == std::string::npos || pos2 == std::string::npos) {
        std::cerr << "[SERVER] CHAT_SEND: Invalid payload\n";
        return;
    }

    std::string token  = payload.substr(0, pos1);
    int clientCredits  = std::stoi(payload.substr(pos1 + 1, pos2 - pos1 - 1));
    std::string message = payload.substr(pos2 + 1);

    pthread_mutex_lock(&global_clients_mutex);

    Client* client = getClientByFD(client_fd);
    if (!client) {
        pthread_mutex_unlock(&global_clients_mutex);
        std::cerr << "[SERVER] CHAT_SEND: Client not found\n";
        return;
    }

    // Validate token
    if (client->getToken() != token) {
        pthread_mutex_unlock(&global_clients_mutex);
        std::cerr << "[SERVER] CHAT_SEND: Invalid token\n";
        return;
    }

    // Validate credit count matches
    if (client->getCredits() != clientCredits) {
        pthread_mutex_unlock(&global_clients_mutex);
        std::cerr << "[SERVER] CHAT_SEND: Credit mismatch\n";
        return;
    }

    // OK — increase credits on server
    client->incrementCredits();

    std::string username = client->getName();

    pthread_mutex_unlock(&global_clients_mutex);

    std::cout << "[SERVER] CHAT from " << username << ": " << message
              << " (new credits=" << client->getCredits() << ")\n";

    // Build the message to broadcast
    Message outgoing(MessageType::CHAT_DELIVER, client->getToken() + "|" + username + "|" + message);

    broadcastMessage(outgoing);
}


//====================================================
// PURCHASE REQUEST
//====================================================
void handlePurchaseRequest(SocketType client_fd, const std::string& payload) {
    // Expected: "<token>|<credits>|<item_id>"
    std::vector<std::string> parts;
    size_t start = 0, end;

    while ((end = payload.find('|', start)) != std::string::npos) {
        parts.push_back(payload.substr(start, end - start));
        start = end + 1;
    }
    parts.push_back(payload.substr(start));

    if (parts.size() != 3) {
        std::cerr << "[SERVER] PURCHASE_REQUEST: Invalid payload format\n";
        return;
    }

    std::string token = parts[0];
    int clientCredits = std::stoi(parts[1]);
    int itemIndex     = std::stoi(parts[2]);

    // Prices (server authoritative)
    const int prices[9] = {0, 0, 25, 50, 75, 100, 150, 200, 100000};

    if (itemIndex < 0 || itemIndex >= 9) {
        std::cerr << "[SERVER] PURCHASE_REQUEST: Invalid itemIndex\n";
        return;
    }

    int price = prices[itemIndex];

    pthread_mutex_lock(&global_clients_mutex);

    Client* client = getClientByFD(client_fd);
    if (!client) {
        pthread_mutex_unlock(&global_clients_mutex);
        std::cerr << "[SERVER] PURCHASE: Client not found\n";
        return;
    }

    // Validate token
    if (client->getToken() != token) {
        pthread_mutex_unlock(&global_clients_mutex);
        std::cerr << "[SERVER] PURCHASE: Token mismatch\n";
        return;
    }

    // Validate credits
    if (client->getCredits() != clientCredits) {
        pthread_mutex_unlock(&global_clients_mutex);
        std::cerr << "[SERVER] PURCHASE: Credit mismatch\n";
        return;
    }

    // Check if already owned
    if (client->isThemeOwned(itemIndex)) {
        pthread_mutex_unlock(&global_clients_mutex);

        Message resp(MessageType::PURCHASE_RESPONSE, "NO|OWNED");

        auto data = Protocol::serialize(resp);
        socket_send(client_fd, (char*)data.data(), data.size());
        return;
    }

    // Check affordability
    if (client->getCredits() < price) {
        pthread_mutex_unlock(&global_clients_mutex);

        Message resp(MessageType::PURCHASE_RESPONSE, "NO|CREDITS");

        auto data = Protocol::serialize(resp);
        socket_send(client_fd, (char*)data.data(), data.size());
        return;
    }

    // SUCCESS: deduct credits and mark owned
    client->subtractPrice(price);
    client->ownTheme(itemIndex);

    int newCredits = client->getCredits();

    pthread_mutex_unlock(&global_clients_mutex);

    std::cout << "[SERVER] PURCHASE OK: item=" << itemIndex
              << " new credits=" << newCredits << "\n";

    // SUCCESS PAYLOAD: YES|itemIndex|newCredits
    Message resp(MessageType::PURCHASE_RESPONSE, "YES|" + std::to_string(itemIndex) + "|" + std::to_string(newCredits));

    auto data = Protocol::serialize(resp);
    socket_send(client_fd, (char*)data.data(), data.size());
}
