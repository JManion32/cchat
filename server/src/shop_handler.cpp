#include "../include/shop_handler.hpp"

void ShopHandler::handlePurchaseRequest(std::shared_ptr<Client> client,
                                        const json &payload) {
  std::cout << "[SHOP] Not currently available!" << std::endl;
  /*
      const int prices[9] = {0, 0, 25, 50, 75, 100, 150, 200, 100000};

      if (payload["index"] < 0 || payload["index"] >= 9) {
          std::cerr << "[PURCHASE] ERROR: Invalid itemIndex" << std::endl;
          return;
      }

      Client* client = getClientByFD(client_fd);
      if (!client) {
          std::cerr << "[PURCHASE] ERROR: Client not found" << std::endl;
          return;
      }

      // Validate token
      if (client->getToken() != payload["token"]) {
          std::cerr << "[PURCHASE ERROR: Token mismatch" <<std::endl;
          return;
      }

      // Validate credits
      if (client->getCredits() != payload["credits"]) {
          std::cerr << "[PURCHASE] ERROR: Credit mismatch" << std::endl;
          return;
      }

      // Check if already owned
      if (client->isThemeOwned(payload["index"])) {
          json response = {
              {"type", "purchase.response"},
              {"payload", {
                  {"success", false}
              }}
          };
          std::string out = response.dump();
          sendDirectMsg(client_fd, out);
          return;
      }

      if (!payload.contains("index") || !payload["index"].is_number_integer()) {
          std::cerr << "[PURCHASE] ERROR: Invalid index" <<std::endl;
          return;
      }

      int index = payload["index"];

      if (index < 0 || index >= 9) {
          std::cerr << "[PURCHASE] ERROR: Index out of bounds" << std::endl;
          return;
      }

      if (client->getCredits() < prices[index]) {
          std::cerr << "[PURCHASE] ERROR: Not enough credits" << std::endl;
          return;
      }

      // Check affordability
      if (client->getCredits() < prices[index]) {
          pthread_mutex_unlock(&global_clients_mutex);
          json response = {
              {"type", "purchase.response"},
              {"payload", {
                  {"success", false}
              }}
          };
          std::string out = response.dump();
          sendDirectMsg(client_fd, out);
          return;
      }

      // SUCCESS: deduct credits and mark owned
      client->subtractPrice(prices[index]);
      client->ownTheme(payload["index"]);

      int newCredits = client->getCredits();

      pthread_mutex_unlock(&global_clients_mutex);

      std::cout << "[PURCHASE] SUCCESS: item=" << payload["index"] << " new
     credits=" << newCredits << std::endl;

      // SUCCESS PAYLOAD
      json response = {
          {"type", "purchase.response"},
          {"payload", {
              {"success", true},
              {"index", payload["index"]},
              {"credits", newCredits}
          }}
      };

      std::string out = response.dump();
      sendDirectMsg(client_fd, out);
  */
}
