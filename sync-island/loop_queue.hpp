#pragma once

#include <atomic>
#include <cstddef>
#include <optional>

namespace sync_island {

template <typename T, size_t N>
class loop_queue {
public:
    loop_queue()
        : head_(0)
        , tail_(0)
        , size_(0) {}

    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == N; }
    size_t size() const { return size_; }
    size_t capacity() const { return N; }

    void push(const T& value) {
        if (full()) {
            return;
        }

        size_t tail   = tail_.load(std::memory_order_relaxed);
        buffer_[tail] = value;

        tail_.compare_exchange_strong(tail, (tail + 1) % N, std::memory_order_release);

        size_.store(size_.load() + 1);
    }

    std::optional<T> pop() {
        if (empty()) {
            return std::nullopt;
        }

        size_t head = head_.load(std::memory_order_relaxed);
        T value     = buffer_[head];
        head_.compare_exchange_strong(head, (head + 1) % N, std::memory_order_release);
        size_.store(size_.load() - 1);

        return value;
    }

private:
    T buffer_[N];
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;
    std::atomic<size_t> size_;
};

} // namespace sync_island
