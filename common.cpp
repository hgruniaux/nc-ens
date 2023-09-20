#include "common.hpp"

#include <netinet/ip.h>
#include <iostream>

std::optional<int> create_socket() {
    if (int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) != -1) {
        log("Error creating socket");
        return {};
    } else {
        log("Socket created");
        return fd;
    }
}

void log(const std::string &data) {
    std::cerr << "LOG : " << data << std::endl;
}