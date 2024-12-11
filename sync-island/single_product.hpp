#pragma once

#include "double_buffer.hpp"

namespace sync_island::single_product {
template <typename T>
class SyncIsland {

public:
    auto push(T value) -> void { buffer_.set(value); }

    auto get() -> T { return buffer_.get(); }

private:
    DoubleBuffer<T> buffer_;
};
} // namespace sync_island::single_product