#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "adt_stack.h"
#include "s_linked_container.h"

namespace DSA
{
    // Singly linked node implementation of LIFO Stack data structure.
    template<class T>
    class linked_stack
        : public adt_stack<T>
        , public s_linked_container<T>
    {
        typedef s_linked_container<T> base_impl;
        typedef std::shared_ptr<s_node<T>> node_ptr;
    public:
        linked_stack();

        linked_stack(const linked_stack<T> &stack);

        virtual ~linked_stack();

        // Return if the stack is empty.
        inline virtual bool empty() const;

        // Get the size of the stack.
        inline virtual size_t size() const;

        // Get the entry on the top of the stack.
        inline virtual T peek() const;

        // Push an entry to the top of the stack.
        inline virtual void push(const T &entry);

        // Pop the top entry from the stack.
        inline virtual T pop();

        // Remove all the entries from the stack, and free the memory.
        inline virtual void clear();

        // Return if the stack contains a given entry.
        inline virtual bool contains(const T &entry) const;

        linked_stack<T> &operator=(const linked_stack<T> &stack);

        linked_stack<T> &operator=(linked_stack<T> &&stack);
    };
}

#include "linked_stack_impl.h"

#endif
