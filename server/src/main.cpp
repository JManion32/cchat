// The APIs are pretty similar, we just need to conditionally use them depending on the OS

#include <iostream>
#include <string>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef SOCKET SocketType;

#else
    #include <arpa/inet.h>
    #include <pthread.h>
    #include <unistd.h>
    typedef int SocketType;

#endif

static const int SERVER_PORT = 5000;

// ===========================================
// Thread logic
// ===========================================
#ifdef _WIN32
DWORD WINAPI client_thread(LPVOID arg) {
    SocketType client_fd = *(SocketType*)arg;
    delete (SocketType*)arg;

    closesocket(client_fd);
    return 0;
}
#else
void* client_thread(void* arg) {
    SocketType client_fd = *(SocketType*)arg;
    delete (SocketType*)arg;

    close(client_fd);
    return nullptr;
}
#endif


// ===========================================
// Main Server
// ===========================================
int main() {
    std::cout << "[SERVER] Starting server..." << std::endl;

#ifdef _WIN32
    // Initialize WinSock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

    // 1. Create socket
    SocketType server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        return -1;
    }

    // Allow reuse
    int opt = 1;
#ifdef _WIN32
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
#else
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

    // 2. Bind
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        return -1;
    }

    // 3. Listen
    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        return -1;
    }

    std::cout << "[SERVER] Listening on port " << SERVER_PORT << "...\n";

    // 4. Accept loop
    while (true) {
        sockaddr_in client_addr{};
#ifdef _WIN32
        int client_len = sizeof(client_addr);
#else
        socklen_t client_len = sizeof(client_addr);
#endif

        SocketType client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        std::cout << "[SERVER] Client connected\n";

        // allocate fd for thread
        SocketType* thread_fd = new SocketType(client_fd);

#ifdef _WIN32
        // Windows thread
        HANDLE thread = CreateThread(
            nullptr, 0, client_thread, thread_fd, 0, nullptr
        );
        CloseHandle(thread);

#else
        // Linux pthread
        pthread_t tid;
        pthread_create(&tid, nullptr, client_thread, thread_fd);
        pthread_detach(tid);
#endif
    }

    return 0;
}
