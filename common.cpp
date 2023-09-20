#include "common.hpp"

#include <netinet/ip.h>
#include <iostream>

std::optional<int> create_socket() {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd == -1) {
        log("Error creating socket");
        return {};
    } else {
        log("Socket created");
        return fd;
    }
}

void log(std::string_view message) {
    std::cerr << "LOG : " << message << std::endl;
}
