#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "adt_queue.h"
#include "s_linked_container.h"

namespace DSA
{
    template <class T>
    class linked_queue 
        : public adt_queue<T>
        , public s_linked_container<T>
    {
        typedef s_linked_container<T> base_impl;
        typedef std::shared_ptr<s_node<T>> node_ptr;
    protected:
        node_ptr m_tail;    // Optimization for enqueue to the back.

    public:
        // Default constructor.
        linked_queue();

        // Copy constructor.
        linked_queue(const linked_queue<T> &queue);

        // Move constructor.
        linked_queue(linked_queue<T> &&queue) noexcept;

        virtual ~linked_queue();

        inline virtual bool empty() const;

        inline virtual size_t size() const;

        inline virtual void clear();

        // Add a given entry to the back of the queue.
        inline virtual void enqueue(const T &entry);

        // Get the entry from the front of the queue.
        inline virtual T dequeue();

        inline virtual T front() const;

        inline virtual T back() const;

        inline virtual bool contains(const T &entry) const;
    };
}

#include "linked_queue_impl.h"

#endif
