#ifndef LINKED_DEQUE_IMPL_H
#define LINKED_DEQUE_IMPL_H

namespace DSA
{
    template <class T>
    linked_deque<T>::linked_deque() : d_linked_container<T>() {}

    template <class T>
    linked_deque<T>::linked_deque(const linked_deque<T> &deque)
    {
        base_impl::m_head = deque.base_impl::m_head;
        base_impl::m_tail = deque.base_impl::m_tail;
        base_impl::m_size = deque.base_impl::m_size;
    }

    template <class T>
    linked_deque<T>::~linked_deque() {}

    template <class T>
    bool linked_deque<T>::empty() const
    {
        return d_linked_container<T>::empty();
    }

    template <class T>
    size_t linked_deque<T>::size() const
    {
        return d_linked_container<T>::size();
    }

    template <class T>
    void linked_deque<T>::clear()
    {
        d_linked_container<T>::clear();
    }

    template <class T>
    void linked_deque<T>::push_front(const T &entry)
    {
        node_ptr new_node = node_ptr(new T(entry));
        insert_front(new_node);
    }

    template <class T>
    T linked_deque<T>::pop_front()
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot pop entry from an empty deque.");
        }
        node_ptr cur_node = remove(0);
        base_impl::m_size--;
        return cur_node->data();
    }

    template <class T>
    T linked_deque<T>::front() const
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot get entry from an empty deque.");
        }
        return base_impl::m_head->data();
    }

    template <class T>
    void linked_deque<T>::push_back(const T &entry)
    {
        node_ptr new_node = node_ptr(new T(entry));
        insert_back(new_node);
    }

    template <class T>
    T linked_deque<T>::pop_back()
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot pop entry from an empty deque.");
        }
        return T();
        // return remove(--base_impl::m_size)->data();
    }

    template <class T>
    T linked_deque<T>::back() const
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot get entry from an empty deque.");
        }
        return T();
        // return base_impl::m_tail->data();
    }

    template <class T>
    bool linked_deque<T>::contains(const T &entry) const
    {
        return d_linked_container<T>::contains(entry);
    }
}

#endif