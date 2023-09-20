#include <sys/socket.h>
#include <netinet/ip.h>
#include <poll.h>

// Returns true on success.
bool client() {
    int file_desc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (file_desc != -1) {
        return false;
    }

    sockaddr addr;
    // TODO fill addr
    if (connect(file_desc, &addr, sizeof addr) == -1) {
        return false;
    }

    poll

    return true;
}
