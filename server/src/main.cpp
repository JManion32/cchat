#include "../include/server.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "[SERVER] Usage: " << argv[0] << " <port>" << std::endl;
        return EXIT_FAILURE;
    }

    int port;

    try
    {
        port = std::stoi(argv[1]);

        if (port < 1 || port > 65535)
        {
            throw std::out_of_range("Port out of range");
        }
    }
    catch (const std::exception&)
    {
        std::cerr << "[SERVER] Invalid port: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    Server server(port);
    return 0;
}
