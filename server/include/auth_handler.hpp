#include <iostream>
#include <string>

#include "./client.hpp"
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class AuthHandler {
public:
    std::string generateToken();
    json handleAuthRequest(std::shared_ptr<Client> client, const json& payload);
    void sendAuthResponse(std::shared_ptr<Client> client);
};