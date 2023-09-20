#include <string_view>
#include <string>

int main(int argc, char* argv[]) {
    int port = 8888;
    std::string_view host;
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
        printf("Creating server at localhost:%d\n", port);
        if (!server()) {
            fprintf(stderr, "Failed to create server...");
        }
    } else { // is_client
        printf("Connecting to server at %s:%d\n", host.data(), port);
        if (!client(host.data(), port)) {
            fprintf(stderr, "Failed to create client...");
        }
    }

    return 0;
}
