#include "../include/auth_handler.hpp"

std::string AuthHandler::generateToken()
{
    int len = 24;
    static const char alphanum[] = "0123456789"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

json AuthHandler::handleAuthRequest(std::shared_ptr<Client> client, const json& payload)
{
    // Validate payload
    if (!payload.contains("name") || !payload["name"].is_string())
    {
        std::cerr << "[AUTH] ERROR: missing or invalid username" << std::endl;
        return json();
    }

    std::string token = generateToken();
    client->setName(payload["name"]);
    client->setToken(token);

    std::cout << "[AUTH] SUCCESS: user= " << client->getName() << " token= " << client->getToken()
              << std::endl;

    std::string server_msg = payload["name"].get<std::string>() + " joined the chat";

    // Send update to requesting client
    sendAuthResponse(client);

    // Broadcasted to all clients
    json chat_response = {{"type", "chat.response"},
                          {"payload",
                           {
                               {"server", true},
                               {"name", payload["name"]},
                               {"content", server_msg},
                           }}};

    return chat_response;
}

void AuthHandler::sendAuthResponse(std::shared_ptr<Client> client)
{
    // Build AUTH_RESPONSE JSON for requesting client
    json auth_response = {
        {"type", "auth.response"},
        {"payload",
         {
             {"success", true}, {"name", client->getName()}, {"token", client->getToken()}
             /* {"credits", client->getCredits()} */
         }}};

    std::string out = auth_response.dump();
    sendDirectMsg(client->getSockfd(), out);
}