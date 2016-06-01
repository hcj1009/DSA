#ifndef SINGLY_LINKED_CONTAINER_IMPL_H
#define SINGLY_LINKED_CONTAINER_IMPL_H

namespace DSA
{
    // Get the node at a given position (index) in the linked chain.
    template <class T>
    std::shared_ptr<s_node<T>> 
        singly_linked_container<T>::node_at(const size_t &index) const
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds.");
        }
#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
        if (m_size - 1 == index)
        {
            return m_tail;
        }
#endif
        node_ptr cur_node = m_head;
        for (size_t i = 0; i < index; i++)
        {
            cur_node = cur_node->next();
        }
        return cur_node;
    }

    // Get the node that contains a given entry in the linked chain.
    template <class T>
    std::shared_ptr<s_node<T>> 
        singly_linked_container<T>::node_of(const T &entry) const
    {
        node_ptr cur_node = m_head;
        while (&cur_node)
        {
            if (entry == cur_node->data())
            {
                return cur_node;
            }
            cur_node = cur_node->next();
        }
        throw no_such_element("Cannot find such entry in the container.");
    }

#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
    template <class T>
    singly_linked_container<T>::singly_linked_container()
        : m_head(), m_tail() {}
#else
    template <class T>
    singly_linked_container<T>::singly_linked_container()
        : m_head() {}
#endif

    template <class T>
    singly_linked_container<T>::~singly_linked_container() {}

    template <class T>
    bool singly_linked_container<T>::empty() const
    {
        return (0 == m_size);
    }

    template <class T>
    size_t singly_linked_container<T>::size() const
    {
        return m_size;
    }

    template <class T>
    void singly_linked_container<T>::clear()
    {
        m_size = 0;
        m_head.reset();
        m_tail.reset();
    }

    template <class T>
    void singly_linked_container<T>::push_front(const T &entry)
    {
        node_ptr new_node = node_ptr(new s_node<T>(entry));
        new_node->set_next(m_head);
        m_head = new_node;
#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
        if (0 == m_size)
        {
            m_tail = new_node;
        }
#endif
        m_size++;
    }

    template <class T>
    void singly_linked_container<T>::push_back(const T &entry)
    {
        node_ptr new_node = node_ptr(new s_node<T>(entry));
#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
        m_tail ? m_tail->set_next(new_node) : m_head = new_node;
        m_tail = new_node;
        m_size++;
#else
        insert(m_size, entry);
#endif
    }

    template <class T>
    void singly_linked_container<T>::insert
    (const size_t &index, const T &entry)
    {
        // Case when adding to the frong of the list
        if (0 == index)
        {
            push_front(entry);
        }
#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
        else if (m_size == index)
        {
            push_back(entry);
        }
#endif
        else
        {
            node_ptr new_node = node_ptr(new s_node<T>(entry));
            node_ptr prev_node = node_at(index - 1);
            new_node->set_next(prev_node->next());
            prev_node->set_next(new_node);
            m_size++;
        }
    }

    // Remove and return the object at the front of the container.
    template <class T>
    T singly_linked_container<T>::pop_front()
    {
        node_ptr cur_node = node_at(index);
        T cur_entry = cur_node->data();
        m_head = cur_node->next();
#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
        // Case when removing the last entry in the list.
        if (!m_head)
        {
            m_tail.reset();
        }
#endif
        m_size--;
        return cur_entry;
    }

    // Remove and return the object at the end of the container.
    template <class T>
    T singly_linked_container<T>::pop_back()
    {
        return remove(m_size - 1);
    }

    // Remove a given entry from the container.
    // Note that only one entry will be removed if there are duplicates.
    // Throw no_such_element exception if the entry is not found.
    template <class T>
    void singly_linked_container<T>::remove(const T &entry)
    {
        if (0 != m_size)
        {
            // Check head.
            if (entry == m_head->data())
            {
                pop_front();
                return;
            }
#if defined(SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG) \
    && defined(SINGLY_LINKED_CONTAINER_UNSTABLE_INDEX_FLAG)
            if (entry == m_tail->data())
            {
                pop_back();
                return;
            }
#endif
            node_ptr prev_node = m_head;
            while (prev_node->next())
        }
        throw no_such_element("Cannot find such entry in the container.");
    }

    // Remove the entry at a given index.
    // Throw index_error exception when index out of bounds.
    template <class T>
    T singly_linked_container<T>::remove(const size_t &index)
    {
        if (0 == index)
        {
            return pop_front();
        }
        else
        {
            node_ptr prev_node = node_at(index - 1);
            node_ptr cur_node = prev_node->next();
            T cur_entry = cur_node->data();
            prev_node->set_next(cur_node->next());
#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
            // Case when removing the last entry from the list.
            if (!cur_node->next())
            {
                m_tail = prev_node;
            }
#endif
            m_size++;
            return cur_entry;
        }
    }

    // Return the entry at a given position in the container.
    // Throw index_error exception when index out of bounds.
    template <class T>
    T singly_linked_container<T>::at(const size_t &index) const
    {
        return node_at(index)->data();
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    template <class T>
    size_t singly_linked_container<T>::index_of(const T &entry) const
    {
#if defined(SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG) \
    && defined(SINGLY_LINKED_CONTAINER_UNSTABLE_INDEX_FLAG)
        if (entry == m_tail->data())
        {
            return m_size - 1;
        }
#endif
        size_t index = 0;
        node_ptr cur_node = m_head;
        while (cur_node)   // cur_node != nullptr;
        {
            if (entry == cur_node->data())
            {
                return index;
            }
            index++;
            cur_node = cur_node->next();
        }
        throw no_such_element("Cannot get the index of an entry that \
is not in the list.");
    }

    template <class T>
    bool singly_linked_container<T>::contains(const T &entry) const
    {
#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
        if (entry == m_tail->data())
        {
            return true;
        }
#endif
        node_ptr cur_node = m_head;
        while (cur_node)   // cur_node != nullptr;
        {
            if (entry == cur_node->data())
            {
                return true;
            }
            cur_node = cur_node->next();
        }
        return false;
    }
}

#endif