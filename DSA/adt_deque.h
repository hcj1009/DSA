#ifndef ADT_DEQUE_H
#define ADT_DEQUE_H

#include "adt_container.h"

namespace DSA
{
    // Abstract data structure Double-ended Queue (Deque)
    template <class T>
    class adt_deque : virtual public adt_container<T>
    {
    public:
        // Default constructor.
        adt_deque() : adt_container<T>() {}

        // Default destructor.
        virtual ~adt_deque() {}

        // Add a agiven entry to the front of the deque.
        virtual void push_front(const T &entry) = 0;

        // Remove and return the entry from the front.
        virtual T pop_front() = 0;

        // Get the entry from the front.
        virtual T front() const = 0;

        // Add a given entry to the end of the deque.
        virtual void push_back(const T &entry) = 0;

        // Remove and return the entry from the back.
        virtual T pop_back() = 0;

        // Get the entry from the back.
        virtual T back() const = 0;
    };
}

#endif
