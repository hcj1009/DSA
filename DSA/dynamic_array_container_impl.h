#ifndef DYNAMIC_ARRAY_CONTAINER_IMPL_H
#define DYNAMIC_ARRAY_CONTAINER_IMPL_H

namespace DSA
{
    // Helper function to determine the capacity needed to hold a
    // given size of list.
    template <class T>
    inline size_t dynamic_array_container<T>::capacity_of(const size_t &size) const
    {
#if defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG) \
    && defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG)
        // When both base_capacity and growth factor are user defined.
        return size < m_capacity
            ? m_capacity : size < m_growth_factor * m_capacity
            ? 2 * m_capacity : 
            (size_t)pow(m_growth_factor, ceil(log((double)size \
            / m_base_capacity) / log(m_growth_factor))) * m_base_capacity;
#elif defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG)
        // When base_capacity is user defined.
        return size < m_capacity
            ? m_capacity : size < DEFAULT_GROWTH_FACTOR * m_capacity
            ? 2 * m_capacity :
            (size_t)pow(DEFAULT_GROWTH_FACTOR, ceil(log((double)size \
            / m_base_capacity) / DEFAULT_LOG)) 
            * m_base_capacity;
#elif defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG)
        // When growth factor is user defined.
        return size < m_capacity
            ? m_capacity : size < DEFAULT_GROWTH_FACTOR * m_capacity
            ? 2 * m_capacity :
            (size_t)pow(m_growth_factor, ceil(log((double)size \
            / DEFAULT_BASE_CAPACITY) / log(m_growth_factor))) 
            * DEFAULT_BASE_CAPACITY;
#else
        // Optimize for default situations.
        return (size_t)pow(DEFAULT_GROWTH_FACTOR, ceil(log((double)size \
            / DEFAULT_BASE_CAPACITY) / DEFAULT_LOG)) 
            * DEFAULT_BASE_CAPACITY;
#endif
    }

    // Helper function to enlarge the capacity when the container is full.
    template <class T>
    inline void dynamic_array_container<T>::ensure_capacity()
    {
        if (m_size >= m_capacity)
        {
            m_capacity = m_size < 2 * m_capacity
                ? 2 * m_capacity : capacity_of(m_size);
            data_ptr new_data = data_ptr(new entry_ptr[m_capacity]);
            for (size_t i = 0; i < m_size; i++)
            {
                new_data[i] = m_data[i];
            }
            m_data = std::move(new_data);
        }
    }

    // Helper function to shift a range of entries starting at a
    // given index with a given displacement.
    template <class T>
    void dynamic_array_container<T>::shift(const size_t &index,
        const ptrdiff_t &disp)
    {
        // Index out of bounds error comes first.
        if (index > m_size)
        {
            throw index_error("Index out of bounds!");
        }
        if (0 == disp)
        {
            return;
        }
        if (0 > index + disp)
        {
            throw illegal_argument("Invalid displacement: index/indeces smaller \
                than 0 after shifting.");
        }

        size_t new_size = m_size + disp;
        size_t new_capacity = capacity_of(m_size);

        if (new_capacity > m_capacity)
        {
            m_capacity = new_capacity;
            data_ptr new_data =
                data_ptr(new entry_ptr[m_capacity]);
            for (size_t i = 0; i < m_size; i++)
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
                src = m_size + index - 1;
                sign *= -1;
                cls = index;
            }
            size_t dest = src + disp;
            for (size_t i = index; i < m_size; i++)
            {
                // Note m_data[n] is shared_ptr,
                // need not move semantics.
                m_data[dest + i * sign] = m_data[src + i * sign];
            }
        }
        m_size = new_size;
    }

    // Constructors.
#if defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG) \
    && defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG)
    template <class T>
    dynamic_array_container<T>::dynamic_array_container
    (const size_t &base_capacity,
        const float &growth_factor)
        : m_data()
        , m_size(0)
        , m_capacity(base_capacity)
        , m_base_capacity(base_capacity)
        , m_growth_factor(growth_factor) {}
#elif defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG)
    template <class T>
    dynamic_array_container<T>::dynamic_array_container
    (const size_t &base_capacity)
        : m_data()
        , m_size(0)
        , m_capacity(base_capacity)
        , m_base_capacity(base_capacity) {}
#elif defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG)
    template <class T>
    dynamic_array_container<T>::dynamic_array_container
    (const float &growth_factor)
        : m_data()
        , m_size(0)
        , m_capacity(DEFAULT_BASE_CAPACITY)
        , m_growth_factor(growth_factor) {}
#else
    template <class T>
    dynamic_array_container<T>::dynamic_array_container()
        : m_data(), m_size(0), m_capacity(DEFAULT_BASE_CAPACITY) {}
#endif

    template <class T>
    dynamic_array_container<T>::~dynamic_array_container() { }

    template <class T>
    size_t dynamic_array_container<T>::capacity() const
    {
        return m_capacity;
    }

#ifdef DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG
    template <class T>
    size_t dynamic_array_container<T>::base_capacity() const
    {
        return m_base_capacity;
    }

    template <class T>
    void dynamic_array_container<T>::set_base_capacity
    (const size_t &base_capacity)
    {
        m_base_capacity = base_capacity;
    }
#endif
#ifdef DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG
    template <class T>
    float dynamic_array_container<T>::growth_factor() const
    {
        return m_growth_factor;
    }
    
    template <class T>
    void dynamic_array_container<T>::set_growth_facotr
    (const float &growth_factor)
    {
        m_growth_factor = growth_factor;
    }
#endif

    template <class T>
    bool dynamic_array_container<T>::empty() const
    {
        return (0 == m_size);
    }

    template <class T>
    size_t dynamic_array_container<T>::size() const
    {
        return m_size;
    }

    template <class T>
    void dynamic_array_container<T>::clear()
    {
        m_data.reset();
        m_size = 0;
#ifdef DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG
        m_capacity = m_base_capacity;
#else
        m_capacity = DEFAULT_BASE_CAPACITY;
#endif
    }

    template <class T>
    void dynamic_array_container<T>::push_front(const T &entry)
    {
        insert(0, entry);
    }

    template <class T>
    void dynamic_array_container<T>::push_back(const T &entry)
    {
        insert(m_size, entry);
    }

    template <class T>
    void dynamic_array_container<T>::insert(const size_t &index, const T &entry)
    {
        // Shift all the element starting from the index right.
        shift(index, 1);
        m_data[index] = entry_ptr(new T(entry));
    }

    template <class T>
    T dynamic_array_container<T>::pop_front()
    {
        remove(0);
    }

    template <class T>
    T dynamic_array_container<T>::pop_back()
    {
        remove(m_size - 1);
    }

    template <class T>
    T dynamic_array_container<T>::remove(const size_t &index)
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds!");
        }
        T entry = std::move(*m_data[index]);
        shift(index + 1, -1);
        return entry;
    }

    template <class T>
    void dynamic_array_container<T>::remove(const T &entry)
    {
        // Get the index of the given entry.
        // Throw no_such_element exception if the entry does not exist.
        size_t index = index_of(entry);
        remove(index);
    }

    template <class T>
    T dynamic_array_container<T>::at(const size_t &index) const
    {
        return *m_data[index];
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    template <class T>
    inline size_t dynamic_array_container<T>::index_of(const T &entry) const
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if (entry == *m_data[i])
            {
                return i;
            }
        }
        throw no_such_element("Cannot find such entry in the container.");
    }

    template <class T>
    // Return if the container contains a given entry.
    bool dynamic_array_container<T>::contains(const T &entry) const
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if (entry == *m_data[i])
            {
                return true;
            }
        }
        return false;
    }

    template <class T>
    T *dynamic_array_container<T>::to_array() const
    {
        T *entries = new T[m_size];
        for (size_t i = 0; i < m_size; i++)
        {
            entries[i] = *m_data[i];
        }
        return entries;
    }
}

#endif
