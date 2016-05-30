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
        linked_stack() : base_impl() {}

        linked_stack(const linked_stack<T> &stack)
        {

        }

        virtual ~linked_stack() {}

        // Return if the stack is empty.
        virtual bool empty() const
        {
            return s_linked_container<T>::empty();
        }

        // Get the size of the stack.
        virtual size_t size() const
        {
            return s_linked_container<T>::size();
        }

        // Get the entry on the top of the stack.
        virtual T peek() const
        {
            if (0 == base_impl::m_size)
            {
                throw empty_container("Cannot pop from an empty stack.");
            }
            return base_impl::m_head->data();
        }

        // Push an entry to the top of the stack.
        virtual void push(const T &entry)
        {
            base_impl::insert_front(entry);
        }

        // Pop the top entry from the stack.
        virtual T pop()
        {
            if (0 == base_impl::m_size)
            {
                throw empty_container("Cannot pop from an empty stack.");
            }
            node_ptr top_node = base_impl::m_head;
            base_impl::m_head = std::move(base_impl::m_head->next());
            base_impl::m_size--;
            return top_node->data();
        }

        // Remove all the entries from the stack, and free the memory.
        virtual void clear()
        {
            s_linked_container<T>::clear();
        }

        // Return if the stack contains a given entry.
        virtual bool contains(const T &entry) const
        {
            return s_linked_container<T>::contains(entry);
        }

        linked_stack& operator=(const linked_stack<T> &stack)
        {
            return *this;
        }

        linked_stack& operator=(linked_stack<T> &&stack)
        {
            return *this;
        }
    };
}

#endif
