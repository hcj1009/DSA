#ifndef LINKED_STACK_IMPL_H
#define LINKED_STACK_IMPL_H

namespace DSA
{
    template <class T>
    linked_stack<T>::linked_stack() : base_impl() {}

    template <class T>
    linked_stack<T>::linked_stack(const linked_stack<T> &stack) {}

    template <class T>
    linked_stack<T>::~linked_stack() {}

    // Return if the stack is empty.
    template <class T>
    bool linked_stack<T>::empty() const
    {
        return s_linked_container<T>::empty();
    }

    // Get the size of the stack.
    template <class T>
    size_t linked_stack<T>::size() const
    {
        return s_linked_container<T>::size();
    }

    // Get the entry on the top of the stack.
    template <class T>
    T linked_stack<T>::peek() const
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot pop from an empty stack.");
        }
        return base_impl::m_head->data();
    }

    // Push an entry to the top of the stack.
    template <class T>
    void linked_stack<T>::push(const T &entry)
    {
        base_impl::insert_front(entry);
    }

    // Pop the top entry from the stack.
    template <class T>
    T linked_stack<T>::pop()
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
    template <class T>
    void linked_stack<T>::clear()
    {
        s_linked_container<T>::clear();
    }

    // Return if the stack contains a given entry.
    template <class T>
    bool linked_stack<T>::contains(const T &entry) const
    {
        return s_linked_container<T>::contains(entry);
    }

    template <class T>
    linked_stack<T> &linked_stack<T>::operator=(const linked_stack<T> &stack)
    {
        return *this;
    }

    template <class T>
    linked_stack<T> &linked_stack<T>::operator=(linked_stack<T> &&stack)
    {
        return *this;
    }
}

#endif