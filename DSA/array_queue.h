#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "adt_queue.h"
#include "dynamic_array_container.h"

namespace DSA
{
    // Circular array based implementation of FIFO Queue.
    template <class T>
    class array_queue
        : public adt_queue<T>
        , public dynamic_array_container<T>
    {
        typedef dynamic_array_container<T> base_impl;
        typedef std::shared_ptr<T> entry_ptr;
        typedef std::unique_ptr<std::shared_ptr<T>[]> data_ptr;
    protected:
        size_t m_front;
        size_t m_back;
        inline size_t increase_index(const size_t &index,
            const size_t &increment) const;
        // Helper function to double the capacity of the queue when it is full.
        inline void ensure_capacity();
    public:
        // Default constructor.
        array_queue(const size_t &base_capacity
            = base_impl::DEFAULT_BASE_CAPACITY);
        array_queue(const array_queue<T> &queue);
        array_queue(array_queue<T> &&queue) noexcept;
        // Default destructor.
        inline virtual ~array_queue();
        // Return if the queue is empty.
        inline virtual bool empty() const;
        // Get the size of the queue.
        inline virtual size_t size() const;
        // Get the capacity of the queue.
        inline virtual size_t capacity() const;
        // Get the first entry in the queue.
        inline virtual T front() const;
        // Get the last entry in the queue.
        inline virtual T back() const;
        // Add a given entry to the back of the queue.
        inline virtual void enqueue(const T &entry);
        // Remove and return the first (oldest) entry in the queue.
        inline virtual T dequeue();
        // Remove all the entries from the queue, and free the memory.
        inline virtual void clear();
        // Return if the queue contains a given entry.
        inline virtual bool contains(const T &entry) const;
    };
}

#include "array_queue_impl.h"

#endif
