// protocol.hpp - length-framed binary protocol
// Wire layout (body only):
// [4 bytes: uint32_t body_len in network order]  // NOT included in 'body' passed to deserialize
// [4 bytes: uint32_t type in network order]
// [1 byte : uint8_t  user]
// [N bytes : payload]   where N == body_len - 5

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>

#ifdef _WIN32
  #include <winsock2.h> // for htonl / ntohl on Windows
  // Link with Ws2_32.lib in your build when using winsock.
#else
  #include <arpa/inet.h> // htonl / ntohl on POSIX
#endif

// --- enums & message type ---
enum class MessageType: uint8_t {
    AUTHENTICATE = 0,
    CHAT = 1,
};

enum class User: uint8_t {
    person1 = 0,
    person2 = 1,
};

class Message {
public:
    MessageType type = MessageType::CHAT;
    User user = User::person1;
    std::string payload;

    void setMessageType(MessageType t) { type = t; }
    void setUser(User u) { user = u; }
};

class Protocol {
public:
    // Build wire bytes: 4-byte length (network order) + body
    // body = [4 bytes type] [1 byte user] [payload]
    static std::vector<uint8_t> serialize(const Message& m);

    // Deserialize body (NOT including 4-byte length). buffer points to the first body byte.
    // 'bytes' must equal the body length. Returns true if parsed successfully.
    static bool deserialize(const uint8_t* buffer, size_t bytes, Message& curMessage);
};
