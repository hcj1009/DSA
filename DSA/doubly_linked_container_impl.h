#ifndef DOUBLY_LINKED_CONTAINER_IMPL_H
#define DOUBLY_LINKED_CONTAINER_IMPL_H


namespace DSA
{
    template <class T>
    std::shared_ptr<d_node<T>> 
    //node_ptr
        doubly_linked_container<T>::node_at(const size_t &index) const
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds.");
        }

        node_ptr cur_node;
        // When index is on the left side of the linked chain.
        if (index <= (float)m_size / 2)
        {
            cur_node = m_head;
            for (size_t i = 0; i < index; i++)
            {
                cur_node = cur_node->next();
            }
        }
        // When index is on the right side of the linked chain.
        else
        {
            cur_node = m_tail;
            for (size_t i = 0; i < m_size - index - 1; i++)
            {
                cur_node = cur_node->prev();
            }
        }
        return cur_node;
    }

    template <class T>
    std::shared_ptr<d_node<T>> 
        doubly_linked_container<T>::node_of(const T &entry) const
    {
        node_ptr cur_node = m_head;
        while (cur_node)
        {
            if (entry == cur_node->data())
            {
                return cur_node;
            }
            cur_node = cur_node->next();
        }
        throw no_such_element("Cannot find such entry in the container.");
    }

    template <class T>
    doubly_linked_container<T>::doubly_linked_container() 
        : m_size(), m_head(), m_tail() {}

    template <class T>
    doubly_linked_container<T>::~doubly_linked_container() {}

    template <class T>
    bool doubly_linked_container<T>::empty() const
    {
        return (0 == m_size);
    }

    template <class T>
    size_t doubly_linked_container<T>::size() const
    {
        return m_size;
    }

    template <class T>
    void doubly_linked_container<T>::clear()
    {
        m_size = 0;
        m_head.reset();
        m_tail.reset();
    }

    template <class T>
    void doubly_linked_container<T>::push_front(const T &entry)
    {
        node_ptr new_node = node_ptr(new d_node<T>(entry));
        // If m_head is nullptr, then m_tail must be nullptr,
        // container must be empty.
        if (m_head)
        {
            m_head->set_prev(new_node);
        }
        else
        {
            m_tail = new_node;
        }
        new_node->set_next(m_head);     // new_node->prev == nullptr
        m_head = new_node;
        m_size++;
    }

    template <class T>
    void doubly_linked_container<T>::push_back(const T &entry)
    {
        node_ptr new_node = node_ptr(new d_node<T>(entry));
        if (m_tail)
        {
            new_node->set_prev(m_tail);
            m_tail->set_next(new_node);
        }
        // If m_tail is nullptr, then m_head must be nullptr,
        // container must be empty.
        else
        {
            m_head = new_node;
        }
        m_tail = new_node;
        m_size++;
    }

    template <class T>
    void doubly_linked_container<T>::insert
    (const size_t &index, const T &entry)
    {
        if (0 == index)
        {
            push_front(entry);
        }
        else if (m_size == index)
        {
            push_back(entry);
        }
        else
        {
            node_ptr new_node = node_ptr(new d_node<T>(entry));
            node_ptr old_node = node_at(index);
            new_node->set_prev(old_node->prev());
            new_node->set_next(old_node);
            if (new_node->prev())
            {
                new_node->prev()->set_next(new_node);
            }
            old_node->set_prev(new_node);
            m_size++;
        }
    }

    template <class T>
    T doubly_linked_container<T>::pop_front()
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot remove item from an empty \
                container!");
        }
        node_ptr front_node = m_head;
        T front_entry = front_node->data();
        front_node->next().reset();
        m_head = m_head->next();
        if (m_head)
        {
            m_head->prev().reset();
        }
        else
        {
            m_tail.reset();
        }
        m_size--;
        return front_entry;
    }

    template <class T>
    T doubly_linked_container<T>::pop_back()
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot remove item from an empty \
                container!");
        }
        node_ptr back_node = m_tail;
        T back_entry = m_tail->data();
        back_node->prev().reset();
        m_tail = m_tail->prev();
        if (m_tail)
        {
            m_tail->next().reset();
        }
        else
        {
            m_head.reset();
        }
        m_size--;
        return back_entry;
    }

    template <class T>
    void doubly_linked_container<T>::remove(const T &entry)
    {
        node_ptr cur_node = node_of(entry);
        node_ptr prev_node = cur_node->prev();
        node_ptr next_node = cur_node->next();
        // Normal cases
        if (prev_node)
        {
            prev_node->set_next(next_node);
        }
        else    // prev_node == nullptr, node is the head.
        {
            m_head = next_node;
        }
        if (next_node)
        {
            next_node->set_prev(prev_node);
        }
        else    // next_node == nullptr, node is the tail.
        {
            m_tail = prev_node;
        }
        m_size--;
    }

    template <class T>
    T doubly_linked_container<T>::remove(const size_t &index)
    {
        if (m_size <= index)
        {
            throw index_error("Index out of bounds!");
        }

        if (0 == index)
        {
            return pop_front();
        }
        else if (m_size - 1 == index)
        {
            return pop_back();
        }
        // General cases.
        else
        {
            node_ptr cur_node = node_at(index);
            node_ptr prev_node = cur_node->prev();
            node_ptr next_node = cur_node->next();
            // Normal cases
            if (prev_node)
            {
                prev_node->set_next(next_node);
            }
            else    // prev_node == nullptr, node is the head.
            {
                m_head = next_node;
            }
            if (next_node)
            {
                next_node->set_prev(prev_node);
            }
            else    // next_node == nullptr, node is the tail.
            {
                m_tail = prev_node;
            }
            m_size--;
        }
    }

    template <class T>
    T doubly_linked_container<T>::at(const size_t &index) const
    {
        return node_at(index)->data();
    }

    // TODO Optimize this:
    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    template <class T>
    size_t doubly_linked_container<T>::index_of(const T &entry) const
    {
        node_ptr forward_node = m_head;
        node_ptr backward_node = m_tail;

        for (int i = 0; i < m_size / 2; i++)
        {
            if (entry == forward_node->data())
            {
                return i;
            }
            if (entry == backward_node->data())
            {
                return m_size - i - 1;
            }
            forward_node = forward_node->next();
            backward_node = backward_node->prev();
        }

        throw no_such_element("Cannot get the index of an entry that \
                is not in the container.");
    }


    template <class T>
    bool doubly_linked_container<T>::contains(const T &entry) const
    {
        try
        {
            index_of(entry);
        }
        catch (no_such_element e)
        {
            return false;
        }
        return true;
    }

    template <class T>
    T *doubly_linked_container<T>::to_array() const
    {
        T *entries = new T[m_size];
        node_ptr forward_node = m_head;
        node_ptr backward_node = m_tail;
        for (size_t i = 0; i < m_size / 2; i++)
        {
            entries[i] = forward_node->data();
            entries[m_size - i - 1] = backward_node->data();

            forward_node = forward_node->next();
            backward_node = backward_node->prev();
        }
        return entries;
    }
}

#endif
