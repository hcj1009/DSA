#ifndef D_LINKED_CONTAINER_IMPL_H
#define D_LINKED_CONTAINER_IMPL_H

namespace DSA
{
    template <class T>
    std::shared_ptr<d_node<T>> 
    //node_ptr
        d_linked_container<T>::node_at(const size_t &index) const
    {
        if (index >= base_impl::m_size)
        {
            throw index_error("Index out of bounds.");
        }

        node_ptr cur_node;
        // When index is on the left side of the linked chain.
        if (index <= (float)base_impl::m_size / 2)
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
            for (size_t i = 0; i < base_impl::m_size - index - 1; i++)
            {
                cur_node = cur_node->prev();
            }
        }
        return cur_node;
    }

    template <class T>
    std::shared_ptr<d_node<T>> 
        d_linked_container<T>::node_of(const T &entry) const
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
    void d_linked_container<T>::insert_front(const T &entry)
    {
        node_ptr new_node = node_ptr(new T(entry));
        if (m_head)
        {
            m_head->set_prev(new_node);
        }
        // If m_head is nullptr, then m_tail must be nullptr,
        // container must be empty.
        else
        {
            m_tail = new_node;
        }
        new_node->set_next(m_head);     // new_node->prev == nullptr
        m_head = new_node;
        base_impl::m_size++;
    }

    template <class T>
    void d_linked_container<T>::insert_back(const T &entry)
    {
        node_ptr new_node = node_ptr(new T(entry));
        new_node->set_prev(m_tail);
        m_tail->set_next(new_node);
        m_tail = new_node;
        base_impl::m_size++;
    }

    template <class T>
    void d_linked_container<T>::insert_entry
    (const size_t &index, const T &entry)
    {
        // Insert entry to the front.
        if (0 == index)
        {
            insert_front(entry);
        }
        // Insert entry to the back. (base_impl::m_size must not equal to 0)
        else if (base_impl::m_size == index)
        {
            insert_back(entry);
        }
        // General cases.
        else
        {
            node_ptr new_node = node_ptr(new T(entry));
            node_ptr old_node = node_at(index);
            new_node->set_prev(old_node->prev());
            new_node->set_next(old_node);
            if (!new_node->prev())
            {
                new_node->prev()->set_next(new_node);
            }
            old_node->set_prev(new_node);
            base_impl::m_size++;
        }
    }

    template <class T>
    d_linked_container<T>::d_linked_container() 
        : base_container<T>()
    {
        m_head = node_ptr();
        m_tail = node_ptr();
    }

    template <class T>
    d_linked_container<T>::~d_linked_container() {}

    template <class T>
    void d_linked_container<T>::clear()
    {
        base_impl::clear();
        m_head = node_ptr();
        m_tail = node_ptr();
    }

    // TODO Optimize this:
    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    template <class T>
    size_t d_linked_container<T>::index_of(const T &entry) const
    {
        node_ptr forward_node = m_head;
        node_ptr backward_node = m_tail;

        for (int i = 0; i < base_impl::m_size / 2; i++)
        {
            if (entry == forward_node->data())
            {
                return i;
            }
            if (entry == backward_node->data())
            {
                return base_impl::m_size - i - 1;
            }
            forward_node = forward_node->next();
            backward_node = backward_node->prev();
        }

        throw no_such_element("Cannot get the index of an entry that \
                is not in the container.");
    }


    template <class T>
    bool d_linked_container<T>::contains(const T &entry) const
    {
        /* Avoid try catch overhead *
        try
        {
            index_of(entry);
        }
        catch (no_such_element exception)
        {
            return false;
        }
        return true;
        /**/

        node_ptr forward_node = m_head;
        node_ptr backward_node = m_tail;

        for (int i = 0; i < base_impl::m_size / 2; i++)
        {
            if (entry == forward_node->data())
            {
                return true;
            }
            if (entry == backward_node->data())
            {
                return true;
            }
            forward_node = forward_node->next();
            backward_node = backward_node->prev();
        }
        return false;
    }
}

#endif