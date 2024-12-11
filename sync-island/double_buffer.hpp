#pragma once

#include <atomic>
#include <cstddef>
#include <memory>

namespace sync_island {
template <typename T>
class DoubleBuffer {
public:
    DoubleBuffer()
        : index_(false) {}

    auto set(T&& buffer) -> void {
        buffers_[index_.load()] = std::make_shared<T>(std::forward<T>(buffer));
        swap();
    }

    auto set(T& buffer) -> void {
        buffers_[index_.load()] = std::make_shared<T>(buffer);
        swap();
    }

    auto set(std::shared_ptr<T> buffer) -> void {
        buffers_[index_.load()] = buffer;
        swap();
    }

    auto get() const -> std::shared_ptr<const T> {
        if (!buffers_[index_.load()])
            return nullptr;
        return buffers_[index_.load()];
    }

    auto swap() -> void { index_.store(!index_.load()); }

private:
    std::atomic<bool> index_;
    std::shared_ptr<T> buffers_[2];
};
} // namespace sync_island