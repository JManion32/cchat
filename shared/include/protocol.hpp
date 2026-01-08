#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>

#ifdef _WIN32
  #include <winsock2.h>
#else
  #include <arpa/inet.h>
#endif

enum class MessageType : uint8_t {
    PLACEHOLDER = 24,
    AUTH_REQUEST = 0,
    AUTH_RESPONSE = 1,
    CHAT_SEND = 2,
    CHAT_DELIVER = 3,
    PURCHASE_REQUEST = 4,
    PURCHASE_RESPONSE = 5,
};

class Message {
public:
  // Constructors
  Message() { setType(MessageType::PLACEHOLDER); setPayload(""); } 
  Message(MessageType type, std::string payload) { setType(type); setPayload(payload); }

  // Getters
  MessageType getType() const { return type; }
  std::string getPayload() const { return payload; }

  // Setters
  void setType(MessageType type) { this->type = type; }
  void setPayload(std::string payload) { this->payload = payload; }

  // Member Functions
  void assignPayload(const char* a, size_t b) { payload.assign(a, b); }
  void clearPayload() { payload.clear(); }
private:
    MessageType type;
    std::string payload;
};

class Protocol {
public:
    static std::vector<uint8_t> serialize(const Message& m);
    static bool deserialize(const uint8_t* body, size_t bytes, Message& out);
};
