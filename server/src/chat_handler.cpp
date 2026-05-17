#include "../include/chat_handler.hpp"

json ChatHandler::handleChatRequest(std::shared_ptr<Client> client, const json& payload) {

    // Validate token exists in payload
    if (!payload.contains("token") || !payload["token"].is_string()) {
        std::cerr << "[CHAT] ERROR: missing or invalid token in payload" << std::endl;
        return json();
    }

    if (client->getToken() != payload["token"]) {
        std::cerr << "[CHAT] ERROR: Invalid token" << std::endl;
        return json();
    }

    // Validate content exists in payload
    if (!payload.contains("content") || !payload["content"].is_string()) {
        std::cerr << "[CHAT] ERROR: missing or invalid content in payload" << std::endl;
        return json();
    }

    std::string username = client->getName();

    std::cout << "[CHAT] SUCCESS: from " << username << std::endl;

    std::string content = payload["content"];

    // Build CHAT_RESPONSE JSON
    json response = {
        {"type", "chat.response"},
        {"payload", {
            {"server", false},
            {"name", client->getName()},
            {"content", content}
        }}
    };

    return response;
}