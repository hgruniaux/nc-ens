#ifndef NC_COMMON_H
#define NC_COMMON_H

#include <optional>
#include <string>

std::optional<int> create_socket();

void log(const std::string &data);

#endif //NC_COMMON_H


