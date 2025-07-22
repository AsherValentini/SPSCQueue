SPSCQueue<T> — Lock-Free Single Producer, Single Consumer Queue
Paragraph:

You're building a lock-free queue that supports a single producer and a single consumer thread.
This data structure is foundational in HFT systems and real-time pipelines where low latency and predictable performance are critical.

You must implement a bounded circular buffer using only atomics and memory ordering — no locks allowed.
Clarifications:

    Implement a template class: template<typename T> class SPSCQueue.

    Constructor takes size_t capacity.

    Fixed-size circular buffer (no dynamic growth).

    API:

        bool push(const T& item); — returns false if full.

        bool pop(T& out); — returns false if empty.

    No blocking, no sleeping, no condition_variable.

    Use std::atomic<size_t> for head/tail indices.

    Use memory_order_relaxed for performance unless ordering is needed.

Example Usage:

SPSCQueue<int> q(4);

std::thread producer([&]() {
    for (int i = 1; i <= 5; ++i) {
        while (!q.push(i)) {}  // spin until pushed
    }
});

std::thread consumer([&]() {
    int val;
    for (int i = 1; i <= 5; ++i) {
        while (!q.pop(val)) {}  // spin until popped
        std::cout << "Got: " << val << "\n";
    }
});

producer.join();
consumer.join();

Expected Output:

Got: 1
Got: 2
Got: 3
Got: 4
Got: 5

Tips:

    Keep head and tail as atomic counters.

    Buffer size should be capacity + 1 to distinguish full vs empty.

    Wrap around with modulo: index % capacity.

    Only one thread writes head (producer), only one writes tail (consumer).

    Reads of opposing side must be atomic (with acquire/release).

Goal:

Model a correct, minimal, and performant SPSCQueue<T> — no STL queues, no mutexes, no dynamic memory.
