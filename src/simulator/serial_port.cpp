#include "simulator/serial_port.hpp"

#include <array>
#include <cerrno>
#include <cstddef>
#include <utility>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

namespace simulator {
namespace {

std::error_code last_error()
{
    return {errno, std::system_category()};
}

}

SerialPort::SerialPort(FileDescriptor file)
    : file_{std::move(file)}
{
}

std::expected<SerialPort, std::error_code> SerialPort::open(const char* path)
{
    const int fd = ::open(path, O_RDONLY | O_NOCTTY | O_NONBLOCK | O_CLOEXEC);
    if (fd < 0) {
        return std::unexpected{last_error()};
    }
    FileDescriptor file{fd};

    termios options{};
    if (::tcgetattr(file.get(), &options) != 0) {
        return std::unexpected{last_error()};
    }
    ::cfmakeraw(&options);
    ::cfsetspeed(&options, B115200);
    options.c_cflag |= CLOCAL | CREAD;
    if (::tcsetattr(file.get(), TCSANOW, &options) != 0) {
        return std::unexpected{last_error()};
    }
    return SerialPort{std::move(file)};
}

std::optional<std::vector<std::string>> SerialPort::read_lines()
{
    std::array<char, 256> buffer{};
    while (true) {
        const ssize_t count = ::read(file_.get(), buffer.data(), buffer.size());
        if (count > 0) {
            pending_.append(buffer.data(), static_cast<std::size_t>(count));
            continue;
        }
        if (count < 0 && (errno == EAGAIN || errno == EINTR)) {
            break;
        }
        return std::nullopt;
    }

    std::vector<std::string> lines;
    std::size_t start = 0;
    for (std::size_t end = pending_.find('\n'); end != std::string::npos; end = pending_.find('\n', start)) {
        lines.push_back(pending_.substr(start, end + 1 - start));
        start = end + 1;
    }
    pending_.erase(0, start);
    return lines;
}

}