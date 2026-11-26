#pragma once

#include <expected>
#include <optional>
#include <string>
#include <system_error>
#include <vector>

#include "simulator/file_descriptor.hpp"

namespace simulator {

class SerialPort {
public:
    [[nodiscard]] static std::expected<SerialPort, std::error_code> open(const char* path);

    [[nodiscard]] std::optional<std::vector<std::string>> read_lines();

private:
    explicit SerialPort(FileDescriptor file);

    FileDescriptor file_;
    std::string pending_;
};

}