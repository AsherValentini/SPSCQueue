#include "tick.hpp"
#include "ring_buffer.hpp"
#include <memory>

#include <gtest/gtest.h>

inline bool operator == (const Tick& lhs, const Tick& rhs) {
    return lhs.price_ == rhs.price_ && lhs.symbol_ == rhs.symbol_;
}

TEST(Title, Description) {
    auto pushTick = Tick("AAPL", 10);
    auto ringBuffer = std::make_shared<RingBuffer<Tick, 10>>();
    ringBuffer->push(pushTick);
    auto popTick = ringBuffer->pop().value();
    ASSERT_EQ(pushTick, popTick);
}
