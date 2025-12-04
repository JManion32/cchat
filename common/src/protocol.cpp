#include "../include/protocol.hpp"

// Build wire bytes: 4-byte length (network order) + body
// body = [4 bytes type] [1 byte user] [payload]
std::vector<uint8_t> Protocol::serialize(const Message& m) {
    uint32_t body_len = 4 + 1 + static_cast<uint32_t>(m.payload.size());
    if (body_len < 5) throw std::runtime_error("invalid message size");

    std::vector<uint8_t> out;
    out.reserve(4 + body_len);

    uint32_t len_be = htonl(body_len);
    out.insert(out.end(), reinterpret_cast<uint8_t*>(&len_be), reinterpret_cast<uint8_t*>(&len_be) + 4);

    uint32_t type_num = static_cast<uint32_t>(m.type);
    uint32_t type_be = htonl(type_num);
    out.insert(out.end(), reinterpret_cast<uint8_t*>(&type_be), reinterpret_cast<uint8_t*>(&type_be) + 4);

    out.push_back(static_cast<uint8_t>(m.user));

    if (!m.payload.empty()) {
        out.insert(out.end(), m.payload.begin(), m.payload.end());
    }

    return out;
}

// Deserialize body (NOT including 4-byte length). buffer points to the first body byte.
// 'bytes' must equal the body length. Returns true if parsed successfully.
bool Protocol::deserialize(const uint8_t* buffer, size_t bytes, Message& curMessage) {
    if (bytes < 5) return false;

    uint32_t type_be = 0;
    std::memcpy(&type_be, buffer, 4);
    uint32_t type_num = ntohl(type_be);
    curMessage.setMessageType(static_cast<MessageType>(type_num));

    uint8_t rawUser = buffer[4];
    curMessage.setUser(static_cast<User>(rawUser));

    size_t payload_len = bytes - 5;
    if (payload_len > 0) {
        curMessage.payload.assign(reinterpret_cast<const char*>(buffer + 5), payload_len);
    } else {
        curMessage.payload.clear();
    }

    return true;
}