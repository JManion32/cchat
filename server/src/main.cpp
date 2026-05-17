#include "../include/server.hpp"

int main() {
    Server server;
    return 0;
}

/*

THE TO-DO LIST
x 1. Implement C++ mutexes instead of pthreads for global array and client functions [OPTIONAL]
x 2. Add default parameters to broadcast to allow for conditional messaging.
Functions should call this with a json and, if necessary, the sock_fd of the client they wish not to send to.
x 3. Complete the AuthHandler implementation
x 4. Complete the ChatHandler implementation
5. Complete the ShopHandler implementation
6. Project runs with standard Makefiles
7. Add CMakeLists.txt (WITHOUT CHAT) and learn how to run it with a nested structure

NOTES:
- GET IT RUNNING!!! We can examine absolute best practices later
- shared_ptrs seem to be helpful
- CLI implementation would be amazing
- CMake now, then best practices, then new features

LET'S GRADUATE TOMORROW!!!

*/