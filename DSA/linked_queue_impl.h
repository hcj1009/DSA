#ifndef LINKED_QUEUE_IMPL_H
#define LINKED_QUEUE_IMPL_H

namespace DSA
{
    // Default constructor.
    template <class T>
    linked_queue<T>::linked_queue()
        : s_linked_container<T>()
        , m_tail() {}

    // Copy constructor.
    template <class T>
    linked_queue<T>::linked_queue(const linked_queue<T> &queue)
    {
        base_impl::m_head
            = node_ptr(queue.base_impl::m_head);
        m_tail = node_ptr(queue.m_tail);
        base_impl::m_size = queue.base_impl::m_size;
    }

    // Move constructor.
    template <class T>
    linked_queue<T>::linked_queue(linked_queue<T> &&queue) noexcept
    {
        base_impl::m_head = queue.base_impl::m_head;
        m_tail = queue.m_tail;
        base_impl::m_size = queue.base_impl::m_size;
    }

    template <class T>
    linked_queue<T>::~linked_queue() {}

    template <class T>
    bool linked_queue<T>::empty() const
    {
        return s_linked_container<T>::empty();
    }

    template <class T>
    size_t linked_queue<T>::size() const
    {
        return s_linked_container<T>::size();
    }

    template <class T>
    void linked_queue<T>::clear()
    {
        s_linked_container<T>::clear();
    }

    // Add a given entry to the back of the queue.
    template <class T>
    void linked_queue<T>::enqueue(const T &entry)
    {
        node_ptr new_node
            = node_ptr(new s_node<T>(entry));
        // Empty list case.
        if (0 == base_impl::m_size)
        {
            base_impl::m_head = new_node;
            m_tail = new_node;
        }
        // Normal cases.
        else
        {
            m_tail->set_next(new_node);
            m_tail = new_node;
        }
        base_impl::m_size++;
    }

    // Get the entry from the front of the queue.
    template <class T>
    T linked_queue<T>::dequeue()
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot get back entry: \
                        queue is empty.");
        }
        node_ptr front_node = base_impl::m_head;
        base_impl::m_head = front_node->next();
        front_node->set_next(node_ptr());
        base_impl::m_size--;
        return front_node->data();
    }

    template <class T>
    T linked_queue<T>::front() const
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot get front entry: \
                        queue is empty.");
        }
        return base_impl::m_head->data();
    }

    template <class T>
    T linked_queue<T>::back() const
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot get back entry: queue is empty.");
        }
        return m_tail->data();
    }

    template <class T>
    bool linked_queue<T>::contains(const T &entry) const
    {
        return s_linked_container<T>::contains(entry);
    }
}

#endif