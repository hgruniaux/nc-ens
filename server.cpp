#include <optional>
#include <array>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/poll.h>
#include "common.hpp"

std::array<char, 4096> buffer = {};
size_t read_bytes = 0;


std::optional<unsigned short> m_bind(int fd, unsigned short port) {
    sockaddr_in addr = {};

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(fd, reinterpret_cast<const sockaddr *>(&addr), sizeof(addr)) < 0) {
        return {};
    }

    return port;
}

bool server(unsigned short port) {
    auto fd = create_socket();

    if (!fd.has_value()) {
        return false;
    }

    const int enable = 1;
    if (setsockopt(fd.value(), SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        log("setsockopt failed (SO_REUSEADDR)");
    }

    if (setsockopt(fd.value(), SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0) {
        log("setsockopt failed (SO_REUSEPORT)");
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

    pollfd fds[] = {{0,         POLLIN},
                    {client_fd, POLLIN}};

    while (poll(fds, 2, -1) >= 0) {
        // Events from stdin
        if (fds[0].revents & POLLIN) {
            while ((read_bytes = read(0, buffer.data(), buffer.size())) > 0) {
                write(client_fd, buffer.data(), read_bytes);
            }
        }

        // Events from remote client
        if (fds[1].revents & POLLIN) {
            while ((read_bytes = read(client_fd, buffer.data(), buffer.size())) > 0) {
                write(0, buffer.data(), read_bytes);
            }
        }
    }

    return true;
}