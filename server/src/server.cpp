#include "../include/server.hpp"

Server::Server(int port) : auth_handler(), chat_handler(), shop_handler() {
  std::cout << "[SERVER] Starting server..." << std::endl;

  this->SERVER_PORT = port;

  SocketType server_fd = socket_create();
  if (server_fd < 0) {
    std::cerr << "[SERVER] socket_create() failed" << std::endl;
    return;
  }

  if (!socket_bind(server_fd, SERVER_PORT)) {
    std::cerr << "[SERVER] socket_bind() failed" << std::endl;
    return;
  }

  if (!socket_listen(server_fd)) {
    std::cerr << "[SERVER] socket_listen() failed" << std::endl;
    return;
  }

  std::cout << "[SERVER] Listening on port " << SERVER_PORT << "..."
            << std::endl;

  // Socket accept loop
  while (true) {
    SocketType client_fd = socket_accept(server_fd);
    if (client_fd < 0) {
      std::cerr << "[SERVER] socket_accept() failed" << std::endl;
      continue;
    }

    std::cout << "[SERVER] Client connected!" << std::endl;
    SocketType *fd_copy = new SocketType(client_fd);
    ThreadType t = thread_create(&Server::addClient, this, fd_copy);
    thread_detach(t);
  }

  socket_close(server_fd);
}

void Server::handleEvent(SocketType client_fd, const json &msg) {
  std::shared_ptr<Client> client;

  {
    std::lock_guard<std::mutex> lock(global_clients_mutex);
    client = getClientByFD(client_fd);
    if (!client) {
      std::cerr << "[AUTH] ERROR: Client not found" << std::endl;
      return;
    }

    // If Auth, verify the client doesn't already exist
    if (msg["type"] == "auth.request") {
      if (!msg["payload"].contains("name") ||
          !msg["payload"]["name"].is_string()) {
        std::cerr << "[AUTH] ERROR: missing name in payload" << std::endl;
        return;
      }
      const std::string req_name = msg["payload"]["name"];
      for (std::vector<std::shared_ptr<Client>>::size_type i = 0;
           i < global_clients.size(); i++) {
        if (global_clients[i]->getName() == req_name) {
          std::cout << global_clients[i]->getName() << " === " << req_name
                    << std::endl;
          std::cerr << "[AUTH] ERROR: Client name already used" << std::endl;
          json response = {
              {"type", "auth.response"},
              {"payload",
               {{"success", false}, {"name", req_name}, {"token", ""}}}};
          std::string out = response.dump();
          sendDirectMsg(client_fd, out);
          return;
        }
      }
    }
  } // Release lock before calling handlers

  std::cout << "[SERVER] Received message type: " << msg["type"] << std::endl;
  if (msg["type"] == "auth.request") {
    json response = auth_handler.handleAuthRequest(client, msg["payload"]);
    broadcastMessage(response);
  } else if (msg["type"] == "chat.request") {
    json response = chat_handler.handleChatRequest(client, msg["payload"]);
    if (!response.is_null() && response.contains("type")) {
      broadcastMessage(response);
    } else {
      std::cerr << "[SERVER] chat.request rejected or malformed response"
                << std::endl;
    }
  } else if (msg["type"] == "purchase.request") {
    shop_handler.handlePurchaseRequest(client, msg["payload"]);
    // broadcastMessage(response);
  } else {
    std::cout << "[SERVER] Unknown MessageType: " << msg["type"] << std::endl;
  }
}

void *Server::addClient(void *arg) {
  SocketType client_fd = *(SocketType *)arg;
  delete (SocketType *)arg;

  std::cout << "[SERVER] Client thread started" << std::endl;

  // Register client (use member mutex, and store shared_ptr to avoid pointer
  // invalidation)
  {
    std::lock_guard<std::mutex> lock(global_clients_mutex);
    global_clients.push_back(std::make_shared<Client>(client_fd, "", ""));
  }

  clientThread(client_fd);

  return nullptr;
}

void Server::removeClient(SocketType sock) {
  std::string name;
  bool was_authorized = false;

  std::lock_guard<std::mutex> lock(global_clients_mutex);

  auto it = std::find_if(global_clients.begin(), global_clients.end(),
                         [sock](const std::shared_ptr<Client> &c) {
                           return c->getSockfd() == sock;
                         });

  if (it == global_clients.end()) {
    return;
  }

  was_authorized = !(*it)->getToken().empty();
  name = (*it)->getName();
  global_clients.erase(it);

  if (!was_authorized) {
    return;
  }

  std::string name_msg = name + " left the chat";
  json response = {{"type", "chat.response"},
                   {"payload",
                    {{"server", true},
                     {"name", name},
                     {"content", name_msg},
                     {"activeCount", getActiveCount()}}}};
  broadcastMessage(response);
}

void Server::clientThread(SocketType client_fd) {

  std::vector<uint8_t> recv_buffer;
  recv_buffer.reserve(2048);
  uint8_t temp[1024];

  while (true) {
    int bytes =
        socket_recv(client_fd, reinterpret_cast<char *>(temp), sizeof(temp));
    if (bytes <= 0) {
      std::cout << "[SERVER] Client disconnected" << std::endl;
      break;
    }

    recv_buffer.insert(recv_buffer.end(), temp, temp + bytes);

    while (true) {
      if (recv_buffer.size() < 4)
        break;

      uint32_t body_len_be = 0;
      std::memcpy(&body_len_be, recv_buffer.data(), 4);
      uint32_t body_len = ntohl(body_len_be);

      if (body_len < 1 || body_len > 1024 * 1024) {
        std::cerr << "[SERVER] Invalid body length" << std::endl;
        goto disconnect;
      }

      size_t full_packet = 4 + body_len;
      if (recv_buffer.size() < full_packet)
        break;

      const char *json_ptr =
          reinterpret_cast<const char *>(recv_buffer.data() + 4);
      std::string json_str(json_ptr, body_len);

      try {
        json msg = json::parse(json_str);

        if (!msg.contains("type") || !msg["type"].is_string()) {
          std::cerr << "[SERVER] Missing or invalid type field" << std::endl;
        } else if (!msg.contains("payload") || !msg["payload"].is_object()) {
          std::cerr << "[SERVER] Missing or invalid payload field" << std::endl;
        } else {
          handleEvent(client_fd, msg);
        }

      } catch (const std::exception &e) {
        std::cerr << "[SERVER] JSON parse error: " << e.what() << std::endl;
      }

      recv_buffer.erase(recv_buffer.begin(), recv_buffer.begin() + full_packet);
    }
  }

disconnect:
  removeClient(client_fd);
  socket_close(client_fd);
}

int Server::getActiveCount() {
  std::lock_guard<std::mutex> lock(global_clients_mutex);
  int count = 0;
  for (const auto &c : global_clients) {
    if (!c->getToken().empty()) {
      count++;
    }
  }
  return count;
}

void Server::broadcastMessage(json &msg) {
  if (msg.is_null() || !msg.contains("type")) {
    std::cerr << "[SERVER] broadcastMessage called with invalid msg"
              << std::endl;
    return;
  }
  std::vector<SocketType> sockets;

  // Append activeCount to all broadcasts
  msg["payload"]["activeCount"] = getActiveCount();

  std::lock_guard<std::mutex> lock(global_clients_mutex);
  for (const auto &c : global_clients) {
    if (!c->getToken().empty()) {
      sockets.push_back(c->getSockfd());
    }
  }

  std::string out = msg.dump();
  for (SocketType sock : sockets) {
    sendDirectMsg(sock, out);
  }
}

std::shared_ptr<Client> Server::getClientByFD(SocketType fd) {
  for (auto &c : global_clients) {
    if (c->getSockfd() == fd)
      return c;
  }
  return nullptr;
}
