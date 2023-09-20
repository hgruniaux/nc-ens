#include <string_view>
#include <string>
#include <iostream>
#include "common.hpp"

int main(int argc, char *argv[]) {
    unsigned short port = 8888;
    std::string_view host = "localhost";
    bool is_server = false;

    for (int i = 0; i < argc; ++i) {
        std::string_view arg = argv[i];
        if (arg == "--port") {
            ++i;
            port = std::atoi(argv[i]);
        } else if (arg == "--host") {
            ++i;
            host = argv[i];
        } else if (arg == "--server") {
            is_server = true;
        }
    }

    if (is_server) {
        std::cout << "Creating server at localhost:" << port << std::endl;
        if (!server(port)) {
            std::cerr << "Failed to create server..." << std::endl;
        }
    } else { // is_client
        std::cout << "Connecting to server at " << host << ":" << port << std::endl;

        if (!client(host.data(), port)) {
            std::cerr << "Failed to create client..." << std::endl;
        }
    }

    return 0;
}
