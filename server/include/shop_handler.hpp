#include <iostream>

#include "./client.hpp"
#include <memory>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ShopHandler {
public:
  void handlePurchaseRequest(std::shared_ptr<Client> client,
                             const json &payload);

private:
};