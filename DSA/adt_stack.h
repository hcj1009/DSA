#ifndef ADT_STACK_H
#define ADT_STACK_H

#include "adt_container.h"

// Abstract data structure LIFO Stack.
template <class T>
class adt_stack : public adt_container<T>
{
public:
    // Default constructor of the stack.
    adt_stack() : adt_container() {}

    adt_stack(adt_stack *stack) : adt_container() {}

    adt_stack(const adt_stack &stack) : adt_container() {}

    adt_stack(adt_stack && stack) : adt_container() {}

    // Default destructor of the stack.
    virtual ~adt_stack() {}

    // Get the entry on the top of the stack.
    virtual T peek() const = 0;

    // Push an entry to the top of the stack.
    // Alias for add(const T &entry)
    virtual void push(const T &entry) = 0;

    // Pop the top entry from the stack.
    virtual T pop() = 0;

    adt_stack& operator=(const adt_stack<T> &stack)
    { return *this; }

    adt_stack& operator=(adt_stack<T> &&stack)
    { return *this; }
};

#endif