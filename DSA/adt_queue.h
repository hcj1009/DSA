#ifndef ADT_QUEUE_H
#define ADT_QUEUE_H

#include "adt_container.h"

// Abstract data structure FIFO Queue.
template <class T>
class adt_queue : adt_container<T>
{
public:
    // Default constructor.
    adt_queue() : adt_container() {};

    // Default destructor.
    virtual ~adt_queue() {}

    // Add a given entry to the back of the queue.
    // Alias for add(const T &entry)
    virtual void enqueue(const T &entry) = 0;

    // Remove and return the first (oldest) entry in the queue.
    virtual T dequeue() = 0;

    // Get the first entry in the queue.
    virtual T front() const = 0;

    // Get the last entry in the queue.
    virtual T back() const = 0;
};

#endif