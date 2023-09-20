#include <sys/socket.h>
#include "common.hpp"

// Returns true on success.
bool client() {
    std::optional<int> file_desc = create_socket();
    if (!file_desc.has_value()) {
        return false;
    }

    sockaddr addr = {};
    // TODO fill addr
    if (connect(file_desc.value(), &addr, sizeof addr) == -1) {
        return false;
    }

//    poll

    return true;
}
