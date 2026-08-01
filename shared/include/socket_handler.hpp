#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET SocketType;
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int SocketType;
#endif
#include <string>

// Client
bool socket_connect(SocketType sock, const char *ip, int port);

// Server
SocketType socket_create();
bool socket_bind(SocketType sock, int port);
bool socket_listen(SocketType sock);
SocketType socket_accept(SocketType server);

// Both
int socket_recv(SocketType sock, void *buffer, int len);
int socket_send(SocketType sock, const void *data, int len);
void socket_close(SocketType sock);

// Length-prefixed JSON send
bool sendDirectMsg(SocketType sock, const std::string &json);