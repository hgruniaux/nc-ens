#ifndef NC_COMMON_H
#define NC_COMMON_H

#include <optional>
#include <string>

std::optional<int> create_socket();

void log(std::string_view message);

bool server(unsigned short port);

bool client(const char *addr, int port);

#endif //NC_COMMON_H


