#ifndef NC_COMMON_H
#define NC_COMMON_H

#include <optional>
#include <string_view>

std::optional<int> create_socket();

void log(std::string_view message);

bool server(const std::optional<unsigned short> &port);
bool client ( const char *addr, int port );

#endif //NC_COMMON_H


