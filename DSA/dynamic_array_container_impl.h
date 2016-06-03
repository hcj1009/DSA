#ifndef DYNAMIC_ARRAY_CONTAINER_IMPL_H
#define DYNAMIC_ARRAY_CONTAINER_IMPL_H

namespace DSA
{
//----------------------------------------------------------------------------
//                           Public Functions
//----------------------------------------------------------------------------
    template <class T>
    dynamic_array_container<T>::
        dynamic_array_container()
        : m_data(), m_size(0), m_capacity
        (DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY) {}

    template <class T>
    dynamic_array_container<T>::
        ~dynamic_array_container() { }

    template <class T>
    size_t dynamic_array_container<T>::
        capacity() const
    {
        return m_capacity;
    }

    template <class T>
    bool dynamic_array_container<T>::
        empty() const
    {
        return (0 == m_size);
    }

    template <class T>
    size_t dynamic_array_container<T>::
        size() const
    {
        return m_size;
    }

    template <class T>
    void dynamic_array_container<T>::
        clear()
    {
        m_data.reset();
        m_size = 0;
        m_capacity = DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY;
    }

    template <class T>
    void dynamic_array_container<T>::
        reserve(const size_t &capacity)
    {
        m_capacity = capacity;
        data_ptr new_data = data_ptr(new T[m_capacity]);
        for (size_t i = 0; i < m_size; i++)
        {
            new_data[i] = std::move(m_data[i]);
        }
        m_data.reset();
        m_data = std::move(new_data);
    }

    template <class T>
    void dynamic_array_container<T>::
        shrink()
    {
        m_capacity = m_size;
        data_ptr new_data = data_ptr(new T[m_capacity]);
        for (size_t i = 0; i < m_size; i++)
        {
            new_data[i] = std::move(m_data[i]);
        }
        m_data.reset();
        m_data = std::move(new_data);
    }

    template <class T>
    void dynamic_array_container<T>::
        push_front(const T &entry)
    {
        insert(0, entry);
    }

    template <class T>
    void dynamic_array_container<T>::
        push_back(const T &entry)
    {
        insert(m_size, entry);
    }

    template <class T>
    void dynamic_array_container<T>::
        insert(const size_t &index, const T &entry)
    {
        // Shift all the element starting from the index right.
        shift(index, 1);
        m_data[index] = entry;
    }

    template <class T>
    T dynamic_array_container<T>::
        pop_front()
    {
        remove(0);
    }

    template <class T>
    T dynamic_array_container<T>::
        pop_back()
    {
        remove(m_size - 1);
    }

    template <class T>
    T dynamic_array_container<T>::
        remove(const size_t &index)
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds!");
        }
        T entry = std::move(m_data[index]);
        shift(index + 1, -1);
        return entry;
    }

    template <class T>
    void dynamic_array_container<T>::
        remove(const T &entry)
    {
        // Get the index of the given entry.
        // Throw no_such_element exception if the entry does not exist.
        size_t index = index_of(entry);
        remove(index);
    }

    template <class T>
    T dynamic_array_container<T>::
        at(const size_t &index) const
    {
        return m_data[index];
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    template <class T>
    inline size_t dynamic_array_container<T>::
        index_of(const T &entry) const
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (entry == m_data[i])
            {
                return i;
            }
        }
        throw no_such_element("Cannot find such entry in the container.");
    }

    template <class T>
    // Return if the container contains a given entry.
    bool dynamic_array_container<T>::
        contains(const T &entry) const
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            if (entry == m_data[i])
            {
                return true;
            }
        }
        return false;
    }

    template <class T>
    T* dynamic_array_container<T>::
        to_array() const
    {
        T *entries = new T[m_size];
        std::copy(m_data, &(m_data[m_size - 1]), entries);
        return entries;
    }

    template <class T>
    dynamic_array_container<T>::iterator dynamic_array_container<T>::
        begin()
    {
        iterator iter;
        return iter;
    }

    template <class T>
    dynamic_array_container<T>::iterator dynamic_array_container<T>::
        end()
    {
        iterator iter;
        iter += m_size - 1;
        return iter;
    }

//----------------------------------------------------------------------------
//                          Operator Overloads
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//                      Private/Protected Functions
//----------------------------------------------------------------------------
    template <class T>
    static constexpr float dynamic_array_container<T>::
        GROWTH_FACTOR_LOG;

    // Helper function to determine the capacity needed to hold a
    // given size of list.
    template <class T>
    inline size_t dynamic_array_container<T>::
        capacity_of(const size_t &size) const
    {
        // Optimize for default situations.
        return (size_t)pow(DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR, \
            ceil(log((double)size / DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY) \
                / GROWTH_FACTOR_LOG))
            * DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY;
    }

    // Helper function to shift a range of entries starting at a
    // given index with a given displacement.
    template <class T>
    void dynamic_array_container<T>::
        shift(const size_t &index, const ptrdiff_t &disp)
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
            throw illegal_argument("Invalid displacement: index/indeces \
                smaller than 0 after shifting.");
        }

        size_t new_size = m_size + disp;
        size_t new_capacity = capacity_of(m_size);

        if (new_capacity > m_capacity)
        {
            m_capacity = new_capacity;
            data_ptr new_data =
                data_ptr(new entry_ptr[m_capacity]);
            for (size_t i = 0; i < m_size; ++i)
            {
                size_t in = i < index ? i : i + disp;
                new_data[in] = std::move(m_data[i]);
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
            for (size_t i = index; i < m_size; ++i)
            {
                // Note m_data[n] is shared_ptr,
                // need not move semantics.
                m_data[dest + i * sign] = std::move(m_data[src + i * sign]);
            }
        }
        m_size = new_size;
    }

//----------------------------------------------------------------------------
//                              Iterator
//----------------------------------------------------------------------------

    template <class T>
    class dynamic_array_container<T>::iterator
        : public std::iterator<std::random_access_iterator_tag, T>
    {
    public:
        iterator() : m_iter(&(m_data[0])) {}

        iterator(const iterator &iter)
            : m_iter(iter.m_iter) {}

        ~iterator() {}

        iterator& operator=(const iterator &rhs)
        {
            m_iter = rhs.m_iter;
        }

        bool operator==(const iterator &rhs) const
        {
            return m_iter == rhs.m_iter;
        }

        bool operator!=(const iterator &rhs) const
        {
            return m_iter != rhs.m_iter;
        }

        bool operator<(const iterator &rhs) const
        {
            return m_iter < rhs.m_iter;
        }

        bool operator>(const iterator &rhs) const
        {
            return m_iter > rhs.m_iter;
        }

        bool operator<=(const iterator &rhs) const
        {
            return m_iter <= rhs.m_iter;
        }

        bool operator>=(const iterator &rhs) const
        {
            return m_iter >= rhs.m_iter;
        }

        iterator& operator++()
        {
            if (m_iter != m_data[m_size - 1])
            {
                ++m_iter;
            }
            m_iter != &(m_data[m_size - 1]) ? ++m_iter : m_iter = nullptr;
        }

        iterator operator++(int)
        {
            dynamic_array_container<T>::iterator old_iter = *this;
            ++*this;
            return old_iter;
        }

        iterator& operator--()
        {
            m_iter != &(m_data[0]) ? --m_iter : m_iter = nullptr;
        }

        iterator operator--(int)
        {
            iterator old_iter = *this;
            --*this;
            return old_iter;
        }

        iterator& operator+=(size_type size)
        {
            m_iter += size;
            return *this;
        }

        iterator operator+(size_type size) const
        {
            iterator old_iter = *this;
            old_iter += size;
            return old_iter;
        }

        iterator& operator-=(size_type size)
        {
            m_iter -= size;
            return *this;
        }

        iterator operator-(size_type size) const
        {
            iterator old_iter = *this;
            old_iter -= size;
            return old_iter;
        }

        reference operator*() const
        {
            return &m_iter;
        }

        pointer operator->() const
        {
            return m_iter;
        }

        reference operator[](size_type index) const
        {

        }
    };
}

#endif
