#ifndef DYNAMIC_ARRAY_CONTAINER_IMPL_H
#define DYNAMIC_ARRAY_CONTAINER_IMPL_H

namespace DSA
{
    template <class T>
    const size_t dynamic_array_container<T>::DEFAULT_BASE_CAPACITY;

    // Helper function to determine the capacity needed to hold a
    // given size of list.
    template <class T>
    inline size_t dynamic_array_container<T>::capacity_of(const size_t &size) const
    {
        return (size_t)pow(2, ceil(log((double)size / m_base_capacity) \
            / LOG2)) * m_base_capacity;
    }

    // Helper function to enlarge the capacity when the container is full.
    template <class T>
    inline void dynamic_array_container<T>::ensure_capacity()
    {
        if (base_container<T>::m_size >= m_capacity)
        {
            m_capacity = base_container<T>::m_size < 2 * m_capacity
                ? 2 * m_capacity : capacity_of(base_container<T>::m_size);
            data_ptr new_data = data_ptr(new entry_ptr[m_capacity]);
            for (size_t i = 0; i < base_container<T>::m_size; i++)
            {
                new_data[i] = std::move(m_data[i]);
            }
            m_data = std::move(new_data);
        }
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    template <class T>
    inline size_t dynamic_array_container<T>::index_of(const T &entry) const
    {
        for (size_t i = 0; i < base_container<T>::m_size; i++)
        {
            if (entry == *m_data[i])
            {
                return i;
            }
        }
        throw no_such_element("Cannot find such entry in the container.");
    }

    // Helper function to shift a range of entries starting at a
    // given index with a given displacement.
    template <class T>
    void dynamic_array_container<T>::shift(const size_t &index,
        const ptrdiff_t &disp)
    {
        if (0 == disp)
        {
            return;
        }

        if (0 > index + disp)
        {
            throw index_error("Invalid displacement: index/indeces smaller \
than 0 after shifting.");
        }

        size_t new_size = base_container<T>::m_size + disp;
        size_t new_capacity = new_size < m_capacity
            ? m_capacity : new_size < 2 * m_capacity
            ? 2 * m_capacity : capacity_of(base_container<T>::m_size);

        if (new_capacity > m_capacity)
        {
            m_capacity = new_capacity;
            data_ptr new_data =
                data_ptr(new entry_ptr[m_capacity]);
            for (size_t i = 0; i < base_container<T>::m_size; i++)
            {
                size_t in = i < index ? i : i + disp;
                new_data[in] = m_data[i];
            }
            m_data = std::move(new_data);
        }
        else
        {
            size_t src = 0;
            size_t cls = new_size;
            ptrdiff_t sign = 1;
            if (0 < disp)
            {
                src = base_container<T>::m_size + index - 1;
                sign *= -1;
                cls = index;
            }
            size_t dest = src + disp;
            for (size_t i = index; i < base_container<T>::m_size; i++)
            {
                m_data[dest + i * sign] =
                    std::move(m_data[src + i * sign]);
            }
        }
        base_container<T>::m_size = new_size;
    }

    template <class T>
    dynamic_array_container<T>::dynamic_array_container
    (const size_t &base_capacity = DEFAULT_BASE_CAPACITY)
        : base_container<T>()
    {
        m_base_capacity = base_capacity;
        m_capacity = m_base_capacity;
        m_data = data_ptr(new entry_ptr[m_capacity]);
    }

    template <class T>
    dynamic_array_container<T>::~dynamic_array_container() { }

    template <class T>
    size_t dynamic_array_container<T>::capacity() const
    {
        return m_capacity;
    }

    template <class T>
    void dynamic_array_container<T>::clear()
    {
        base_container<T>::clear();
        m_capacity = m_base_capacity;
        m_data = data_ptr(new entry_ptr[m_capacity]);
    }

    template <class T>
    // Return if the container contains a given entry.
    bool dynamic_array_container<T>::contains(const T &entry) const
    {
        try
        {
            index_of(entry);
        }
        catch (no_such_element exception)
        {
            return false;
        }
        return true;
    }
}

#endif