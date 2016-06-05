#ifndef CIRCULAR_ARRAY_CONTAINER_IMPL_H
#define CIRCULAR_ARRAY_CONTAINER_IMPL_H

namespace DSA
{
//----------------------------------------------------------------------------
//                           Public Functions
//----------------------------------------------------------------------------
    template <class T>
    circular_array_container<T>::
        circular_array_container()
        : m_size(0), m_capacity(CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY)
    {
        m_data = new T[m_capacity];
        m_front = &m_data[0];
        m_back = m_front;
    }

    template <class T>
    circular_array_container<T>::
        ~circular_array_container() { delete[] m_data; }

    template <class T>
    bool circular_array_container<T>::
        empty() const
    {
        return (0 == m_size);
    }

    template <class T>
    size_t circular_array_container<T>::
        size() const
    {
        return m_size;
    }

    template <class T>
    size_t circular_array_container<T>::
        capacity() const
    {
        return m_capacity;
    }

    template <class T>
    void circular_array_container<T>::
        clear()
    {
        delete[] m_data;
        m_capacity = CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY;
        m_size = 0;
        m_data = new T[m_capacity];
        m_front = &m_data[0];
        m_back = m_front;
    }

    template <class T>
    void circular_array_container<T>::
        reserve(const size_t& capacity)
    {
        m_capacity = capacity;
        auto new_data = new T[m_capacity];
        // TODO Move data;
        delete[] m_data;
        m_data = new_data;
    }

    template <class T>
    void circular_array_container<T>::
        shrink()
    {
        m_capacity = m_size <= CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY
            ? CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY : m_size;
        auto new_data = new T[m_capacity];
        // TODO Move data;
        delete[] m_data;
        m_data = new_data;
    }

    template <class T>
    void circular_array_container<T>::
        push_front(const T& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        *dec_ptr(m_front) = entry;
        --m_size;
    }

    template <class T>
    void circular_array_container<T>::
        push_front(T&& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        *dec_ptr(m_front) = std::move(entry);
        --m_size;
    }

    template <class T>
    void circular_array_container<T>::
        push_back(const T& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        *m_back = entry;
        inc_ptr(m_back);
        ++m_size;
    }

    template <class T>
    void circular_array_container<T>::
        push_back(T&& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        *m_back = std::move(entry);
        inc_ptr(m_back);
        ++m_size;
    }

    template <class T>
    void circular_array_container<T>::
        insert(const size_t& index, const T& entry)
    {
        if (index > m_size)
        {
            throw index_error("Index out of bounds");
        }

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
            if ((m_size - 1) / 2 <= index)
            {
                //shift_right(index);
            }
            else
            {
                //shift_left();
            }
            m_data[index] = entry;
            ++m_size;
        }
    }

    template <class T>
    T circular_array_container<T>::
        pop_front()
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot remove entry from an \
                empty container.");
        }
        auto entry = std::move(*m_front);
        inc_ptr(m_front);
        --m_size;
        return entry;
    }

    template <class T>
    T circular_array_container<T>::
        pop_back()
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot remove entry from an \
                empty container.");
        }
        auto entry = std::move(*m_back);
        dec_ptr(m_back);
        --m_size;
        return entry;
    }

    template <class T>
    void circular_array_container<T>::
        remove(const T& entry)
    {
        remove(index_of(entry));
    }

    template <class T>
    void circular_array_container<T>::
        remove(const size_t& index)
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds");
        }
        if ((m_size - 1) / 2 <= index)
        {
            //shift_left(index + 1);
        }
        else
        {
            //shift_right(index - 1);
        }

    }

    template <class T>
    T circular_array_container<T>::
        at(const size_t& index) const
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds");
        }
        return m_data[index];
    }

    template <class T>
    size_t circular_array_container<T>::
        index_of(const T& entry) const
    {
        /*
        auto index = 0;
        T* iter = m_front;
        while (m_front != m_back)
        {
            if (entry == *iter)
            {
                return index;
            }
            ++index;
            inc_ptr(iter);
        }
        throw no_such_element("Cannot find such entry in the container.");
        */
        return 0;
    }

    template <class T>
    bool circular_array_container<T>::
        contains(const T& entry) const
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

    /**
    template <class T>
    typename circular_array_container<T>::iterator
        circular_array_container<T>::
        begin()
    {
        return iterator(*this);
    }

    template <class T>
    typename circular_array_container<T>::iterator
        circular_array_container<T>::
        end()
    {
        return iterator(*this);
    }
    /**/
    template <class T>
    T* circular_array_container<T>::
        to_array() const
    {
        auto entries = new T[m_size];
        // TODO Copy data;
        return entries;
    }

//----------------------------------------------------------------------------
//                        Private/Protected Functions
//----------------------------------------------------------------------------

    template <class T>
    T* circular_array_container<T>::
        inc_ptr(data_ptr ptr)
    {
        if (&m_data[m_capacity - 1] != ptr)
        {
            ++ptr;
        }
        else
        {
            ptr = &m_data[0];
        }
        return ptr;
    }

    template <class T>
    T* circular_array_container<T>::
        dec_ptr(data_ptr ptr)
    {
        if (&m_data[0] != ptr)
        {
            --ptr;
        }
        else
        {
            ptr = &m_data[m_capacity - 1];
        }
        return ptr;
    }

    template <class T>
    size_t circular_array_container<T>::
        capacity_of(const size_t& size) const noexcept
    {
        // Optimize for default situations.
        size_t new_capacity = 0;
        if (size <= m_capacity)
            new_capacity = m_capacity;
        else if (size <= 2 * m_capacity)
            new_capacity = 2 * m_capacity;
        else
            new_capacity = (size_t)CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY \
            * pow(CIRCULAR_ARRAY_CONTAINER_GROWTH_FACTOR, ceil(\
                log((double)size / CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY) \
                / GROWTH_FACTOR_LOG));
        return new_capacity;
    }

    template <class T>
    void circular_array_container<T>::
        ensure_capacity()
    {
        m_capacity *= CIRCULAR_ARRAY_CONTAINER_GROWTH_FACTOR;
        auto new_data = new T[m_capacity];
        // TODO Move data;
        delete[] m_data;
        m_data = new_data;
    }

    template <class T>
    void circular_array_container<T>::
        shift_left(data_ptr begin, data_ptr end)
    {

    }

    template <class T>
    void circular_array_container<T>::
        shift_right(data_ptr begin, data_ptr end)
    {

    }

//----------------------------------------------------------------------------
//                                  Iterator
//----------------------------------------------------------------------------


}

#endif