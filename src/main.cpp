#include <iostream>
#include <memory>
#include "ring_buffer.hpp"
#include "tick.hpp"

int main() { 

	auto ptr = std::make_unique<RingBuffer<Tick, 10>>();

	return 0;
}
