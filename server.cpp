#include <optional>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.hpp"


std::optional<unsigned short> m_bind(int fd, const std::optional<unsigned short> &port) {
    struct sockaddr_in addr = {};

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    if (port.has_value()) {
        addr.sin_port = htons(port.value());
    } else {
        addr.sin_port = 0;
    }

    if (bind(fd, reinterpret_cast<const sockaddr *>(&addr), sizeof(addr)) < 0) {
        return {};
    }

    return addr.sin_port;
}

[[maybe_unused]] bool server(const std::optional<unsigned short> &port) {
    auto fd = create_socket();

    if (!fd.has_value()) {
        return false;
    }

    auto p = m_bind(fd.value(), port);

    if (!p.has_value()) {
        log("Error in bind");
        return false;
    }

    log("Socket bind to " + std::to_string(p.value()));

    if (listen(fd.value(), 1)) {
        log("Error in listen");
        return false;
    }

    log("Socket listen for 1 connection");

    sockaddr_in client = {};
    int size = sizeof(client);
    int client_fd = accept(fd.value(), reinterpret_cast<sockaddr *>(&client), reinterpret_cast<socklen_t *>(&size));
    log("Client Connection ?");

    if (client_fd < 0) {
        log("Client Connection Error (connect)");
        return false;
    }

    log("Client Connected");


    return true;
}