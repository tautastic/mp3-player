#pragma once

#include <utility>

#include <unistd.h>

namespace simulator {

class FileDescriptor {
public:
    explicit FileDescriptor(int fd) noexcept
        : fd_{fd}
    {
    }

    FileDescriptor(FileDescriptor&& other) noexcept
        : fd_{std::exchange(other.fd_, -1)}
    {
    }

    FileDescriptor& operator=(FileDescriptor&& other) noexcept
    {
        std::swap(fd_, other.fd_);
        return *this;
    }

    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;

    ~FileDescriptor()
    {
        if (fd_ >= 0) {
            ::close(fd_);
        }
    }

    [[nodiscard]] int get() const noexcept
    {
        return fd_;
    }

private:
    int fd_;
};

}
