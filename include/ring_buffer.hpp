#pragma once

#include <atomic>
#include <array>
#include <stddef.h>
#include <type_traits>
#include <optional>
#include <new>

template<typename T, std::size_t Capacity>
class RingBuffer {
public:
	RingBuffer() : head_(0), tail_(0) {}

	~RingBuffer() {
		while(pop()){}
	}

	static_assert(Capacity>1, "[RingBuffer] Ring Buffer not instantiated with  large enough capacity");

	// push
	bool push(const T& item) {

		int head = head_.load(std::memory_order_relaxed);
		int next = increment(head);

		if(next == tail_.load(std::memory_order_acquire)) {
			return false; // this is no overwrite mode
		}

		// step 1: we need a raw pointer the pos in ds (make sure the address is type compatible with the raw ptr)
		void* slot = static_cast<void*>(&ringBuffer_[head]);
		// step 2: construct in place using placement new (assuming that item can be constructed over)
		new (slot) T(item);

		head_.store(next, std::memory_order_release);

		return true;
	}

	// pop
	std::optional<T> pop() {
		int tail = tail_.load(std::memory_order_relaxed);

		if(tail == head_.load(std::memory_order_acquire)) {
			return std::nullopt;
		}

		T* itemPtr = reinterpret_cast<T*>(&ringBuffer_[tail]);
		T item = std::move(*itemPtr);
		itemPtr->~T();

		tail_.store(increment(tail), std::memory_order_release);

		return item;

	}

private:
	std::atomic<int> head_;
	std::atomic<int> tail_;

	int increment(const int& n) const {
		return (n+1)%Capacity;
	}

	std::array<std::aligned_storage_t<sizeof(T), alignof(T)>, Capacity> ringBuffer_;

};

