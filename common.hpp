#ifndef NC_COMMON_H
#define NC_COMMON_H

#include <optional>
#include <string_view>

std::optional<int> create_socket();

void log(std::string_view message);

#endif //NC_COMMON_H


