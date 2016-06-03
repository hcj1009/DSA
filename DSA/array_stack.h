#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "adt_stack.h"
#include "singly_linked_container.h"

namespace DSA
{
    // Array implementation of LIFO Stack data structure.
    template <class T, class Container
        = singly_linked_container<T>>
    class array_stack
        : public adt_stack<T>
    {
    protected:
        Container cont;

    public:
        array_stack();
        array_stack(const array_stack<T> &stack);
        array_stack(array_stack<T> &&stack) noexcept;
        virtual ~array_stack();

        // Return if the stack is empty.
        inline virtual bool empty() const;

        // Get the size of the stack.
        inline virtual size_t size() const;

        // Get the capacity of the stack.
        inline virtual size_t capacity() const;

        // Remove all the entries from the list, and free the memory.
        inline virtual void clear();

        // Get the entry on the top of the stack.
        inline virtual T peek() const;

        // Push an entry to the top of the stack.
        inline virtual void push(const T &entry);

        inline virtual void push(T &&entry);

        // Pop the top entry from the stack.
        inline virtual T pop();

        // Return if the stack contains a given entry.
        inline virtual bool contains(const T &entry) const;

        array_stack<T> &operator=(const array_stack<T> &stack);

        array_stack<T> &operator=(array_stack<T> &&stack);
    };
}

#include "array_stack_impl.h"

#endif
