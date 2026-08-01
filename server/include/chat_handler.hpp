#include <iostream>

#include "./client.hpp"
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ChatHandler {
public:
  json handleChatRequest(std::shared_ptr<Client> client, const json &payload);

private:
};