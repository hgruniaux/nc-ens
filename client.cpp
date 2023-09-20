#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

void populate_sockaddr(int port, const char* addr,
                       sockaddr_storage *dst, socklen_t *addrlen) {
    sockaddr_in *dst_in4 = (sockaddr_in *) dst;

    *addrlen = sizeof(*dst_in4);
    memset(dst_in4, 0, *addrlen);
    dst_in4->sin_family = AF_INET;
    dst_in4->sin_port = htons(port);
    inet_pton(AF_INET, addr, &dst_in4->sin_addr);
}

// Returns true on success.
bool client(const char* addr, int port) {
    int file_desc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (file_desc != -1) {
        return false;
    }

    sockaddr_storage addr_storage;
    socklen_t addrlen;
    populate_sockaddr(port, addr, &addr_storage, &addrlen);

    if (connect(file_desc, (const sockaddr*)&addr_storage, addrlen) == -1) {
        return false;
    }

    // Start listening stdin and the server
    pollfd fds[] = { { 0, POLLIN }, { file_desc, POLLIN }};
    while (poll(fds, ARRAY_SIZE(fds), -1) >= 0) {
        char buffer[4096] = {0};

        // Events from stdin
        if (fds[0].revents & POLLIN) {
            size_t read_bytes = 0;
            while ((read_bytes = fread(buffer, sizeof(char), ARRAY_SIZE(buffer), stdin)) > 0) {
                write(file_desc, buffer, read_bytes);
            }
        }

        // Events from remote server
        if (fds[1].revents & POLLIN) {
            while (read(file_desc, buffer, sizeof(buffer)) > 0) {
                fwrite(buffer, sizeof(char), ARRAY_SIZE(buffer), stdout);
            }
        }
    }

    return true;
}
