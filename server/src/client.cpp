#include "../include/client.hpp"

Client::Client(SocketType sockfd, std::string name, std::string token) {
  this->sockfd = sockfd;
  this->name = name;
  this->token = token;
  this->credits = 0;
}

void Client::setSockfd(SocketType sockfd) {
  std::lock_guard<std::mutex> lock(client_mutex);
  this->sockfd = sockfd;
}

void Client::setName(std::string name) {
  std::lock_guard<std::mutex> lock(client_mutex);
  this->name = name;
}

void Client::setToken(std::string token) {
  std::lock_guard<std::mutex> lock(client_mutex);
  this->token = token;
}

void Client::setCredits(int credits) {
  std::lock_guard<std::mutex> lock(client_mutex);
  this->credits = credits;
}

void Client::ownTheme(int index) {
  std::lock_guard<std::mutex> lock(client_mutex);
  owned_themes[index] = true;
}

void Client::incrementCredits() {
  std::lock_guard<std::mutex> lock(client_mutex);
  credits++;
}

void Client::subtractPrice(int price) {
  std::lock_guard<std::mutex> lock(client_mutex);
  credits = credits - price;
}