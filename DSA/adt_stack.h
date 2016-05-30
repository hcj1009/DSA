#ifndef ADT_STACK_H
#define ADT_STACK_H

#include "adt_container.h"

namespace DSA
{
    // Abstract data structure LIFO Stack.
    template <class T>
    class adt_stack : virtual public adt_container<T>
    {
    public:
        // Default constructor of the stack.
        adt_stack() : adt_container<T>() {}

        // Default destructor of the stack.
        virtual ~adt_stack() {}

        // Get the entry on the top of the stack.
        virtual T peek() const = 0;

        // Push an entry to the top of the stack.
        virtual void push(const T &entry) = 0;

        // Pop the top entry from the stack.
        virtual T pop() = 0;
    };
}

#endif
