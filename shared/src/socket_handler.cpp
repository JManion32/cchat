#include "../include/socket_handler.hpp"

SocketType socket_create()
{
#ifdef _WIN32
    static bool initialized = false;
    if (!initialized)
    {
        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);
        initialized = true;
    }
#endif

    return socket(AF_INET, SOCK_STREAM, 0);
}

bool socket_connect(SocketType sock, const char* host, int port)
{
    // getaddrinfo rather than inet_pton: inet_pton parses numeric addresses
    // only. It returns 0 for a name like "cchat.fun" and leaves the address
    // zeroed, which silently connects to 0.0.0.0 (localhost) instead of
    // failing.
    addrinfo hints{};
    hints.ai_family = AF_INET; // socket_create() makes an AF_INET socket
    hints.ai_socktype = SOCK_STREAM;

    const std::string port_str = std::to_string(port);

    addrinfo* res = nullptr;
    if (getaddrinfo(host, port_str.c_str(), &hints, &res) != 0)
    {
        return false;
    }

    bool connected = false;
    for (addrinfo* p = res; p != nullptr; p = p->ai_next)
    {
        if (connect(sock, p->ai_addr, static_cast<int>(p->ai_addrlen)) == 0)
        {
            connected = true;
            break;
        }
    }

    freeaddrinfo(res);
    return connected;
}

bool socket_bind(SocketType sock, int port)
{
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    return bind(sock, (sockaddr*)&addr, sizeof(addr)) == 0;
}

bool socket_listen(SocketType sock) { return listen(sock, 10) == 0; }

SocketType socket_accept(SocketType server)
{
    sockaddr_in addr{};
#ifdef _WIN32
    int len = sizeof(addr);
#else
    socklen_t len = sizeof(addr);
#endif
    return accept(server, (sockaddr*)&addr, &len);
}

int socket_send(SocketType sock, const void* data, int len)
{
#ifdef _WIN32
    return send(sock, (const char*)data, len, 0);
#else
    return send(sock, data, len, 0);
#endif
}

int socket_recv(SocketType sock, void* buffer, int len)
{
#ifdef _WIN32
    return recv(sock, (char*)buffer, len, 0);
#else
    return recv(sock, buffer, len, 0);
#endif
}

void socket_close(SocketType sock)
{
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
}

bool sendDirectMsg(SocketType sock, const std::string& json)
{
    uint32_t len = htonl(static_cast<uint32_t>(json.size()));

    // send length prefix
    if (socket_send(sock, &len, sizeof(len)) != sizeof(len))
        return false;

    // send JSON body
    if (socket_send(sock, json.data(), json.size()) != (int)json.size())
        return false;

    return true;
}