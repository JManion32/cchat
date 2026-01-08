#include "../include/protocol.hpp"
#include <iostream>

std::vector<uint8_t> Protocol::serialize(const Message& m) {
    std::string payload = m.getPayload();
    uint32_t body_len = 1 + static_cast<uint32_t>(payload.size());

    std::vector<uint8_t> out;
    out.reserve(4 + body_len);

    // length prefix
    uint32_t len_be = htonl(body_len);
    out.insert(out.end(),
               reinterpret_cast<uint8_t*>(&len_be),
               reinterpret_cast<uint8_t*>(&len_be) + 4);

    // 1-byte type
    out.push_back(static_cast<uint8_t>(m.getType()));

    // payload
    out.insert(out.end(), payload.begin(), payload.end());

    return out;
}

bool Protocol::deserialize(const uint8_t* body, size_t bytes, Message& out) {
    if (bytes < 1) return false;

    out.setType(static_cast<MessageType>(body[0]));

    if (bytes > 1) {
        out.assignPayload(reinterpret_cast<const char*>(body + 1), bytes - 1);
    } else {
        out.clearPayload();
    }

    return true;
}