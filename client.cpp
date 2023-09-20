#include <sys/socket.h>

#include "common.hpp"

void client() {
    int file_desc = socket(AF_INET, SOCK_STREAM, TCP_PROTOCOL);
    if (file_desc) {}

    sockaddr addr;
    connect(file_desc, &addr, sizeof addr);
}
