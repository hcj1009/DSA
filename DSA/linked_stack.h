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
    public:
        linked_stack() : adt_stack<T>() {}

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
            if (0 == m_size)
            {
                throw empty_container("Cannot pop from an empty stack.");
            }
            return m_head->data();
        }

        // Push an entry to the top of the stack.
        virtual void push(const T &entry)
        {
            insert_front(entry);
        }

        // Pop the top entry from the stack.
        virtual T pop()
        {
            if (0 == m_size)
            {
                throw empty_container("Cannot pop from an empty stack.");
            }
            s_node<T> *top_node = m_head;
            m_head = m_head->next();
            m_size--;
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