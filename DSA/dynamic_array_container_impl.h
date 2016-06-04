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
        : m_size(0), m_capacity (DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY)
    {
        m_data = data_ptr(new T[m_capacity]);
    }

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
        //delete[] m_data;
        m_size = 0;
        m_capacity = DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY;
        m_data = data_ptr(new T[m_capacity]);
    }

    template <class T>
    void dynamic_array_container<T>::
        reserve(const size_t &capacity)
    {
        m_capacity = capacity;
        auto old_data = m_data.release();
        auto new_data = new T[m_capacity];
        memcpy(new_data, old_data, m_size * sizeof(T));
        //std::copy(begin(), end(), new_data);
        /*
        for (size_t i = 0; i < m_size; i++)
        {
            std::swap(std::move(new_data[i]), std::move(m_data[i]));
        }
        */
        m_data.reset(old_data);
        //delete[] m_data;
        m_data.reset(new_data);
    }

    template <class T>
    void dynamic_array_container<T>::
        shrink()
    {
        m_capacity = capacity_of(m_size);
        auto new_data = data_ptr(new T[m_capacity]);
        for (size_t i = 0; i < m_size; i++)
        {
            new_data[i] = std::move(m_data[i]);
        }
        m_data.reset();
        //delete[] m_data;
        m_data = std::move(new_data);
    }

    template <class T>
    void dynamic_array_container<T>::
        push_front(const T &entry)
    {
        unchecked_shift(0, 1);
        m_data[0] = entry;
    }

    template <class T>
    void dynamic_array_container<T>::
        push_back(const T &entry)
    {
        unchecked_shift(m_size, 1);
        m_data[m_size - 1] = entry;
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
        return remove(0);
    }

    template <class T>
    T dynamic_array_container<T>::
        pop_back()
    {
        return remove(m_size - 1);
    }

    template <class T>
    T dynamic_array_container<T>::
        remove(const size_t &index)
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds!");
        }
        auto entry = std::move(m_data[index]);
        unchecked_shift(index + 1, -1);
        return entry;
    }

    template <class T>
    void dynamic_array_container<T>::
        remove(const T &entry)
    {
        // Get the index of the given entry.
        // Throw no_such_element exception if the entry does not exist.
        auto index = index_of(entry);
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
        auto entries = new T[m_size];
        //std::copy(m_data, &(m_data[m_size - 1]), entries);
        return entries;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator
        dynamic_array_container<T>::
        begin()
    {
        iterator iter{*this};
        return iter;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator
        dynamic_array_container<T>::
        end()
    {
        iterator iter{*this};
        iter += m_size;
        return iter;
    }

//----------------------------------------------------------------------------
//                          Operator Overloads
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//                      Private/Protected Functions
//----------------------------------------------------------------------------

    // Helper function to determine the capacity needed to hold a
    // given size of list.
    template <class T>
    inline size_t dynamic_array_container<T>::
        capacity_of(const size_t &size) const
    {
        // Optimize for default situations.
        size_t new_capacity = 0;
        if (size <= m_capacity)
            new_capacity = m_capacity;
        else if (size <= 2 * m_capacity)
            new_capacity = 2 * m_capacity;
        else
            new_capacity = (size_t)DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY \
            * pow(DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR, ceil( \
            log((double)size / DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY) \
                / GROWTH_FACTOR_LOG));
        return new_capacity;
    }

    template <class T>
    void dynamic_array_container<T>::
        shift_left(const size_t &index)
    {

    }

    template <class T>
    void dynamic_array_container<T>::
        shift_right(const size_t &index)
    {
        
    }

    template <class T>
    void dynamic_array_container<T>::
        unchecked_shift(const size_t &index, const ptrdiff_t &disp)
    {
        auto new_size = m_size + disp;
        auto new_capacity = capacity_of(new_size);
        
        if (new_capacity <= m_capacity)
        {
            if (index == m_size)
            {
                m_size = new_size;
                return;
            }
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
                m_data[dest + i * sign] = 
                    std::move(std::move(m_data[src + i * sign]));
            }
        }
        else
        {
            m_capacity = new_capacity;
            auto new_data = data_ptr(new T[m_capacity]);
            for (size_t i = 0; i < m_size; ++i)
            {
                auto in = i < index ? i : i + disp;
                new_data[in] = std::move(m_data[i]);
            }
            m_data = std::move(new_data);
        }
        m_size = new_size;
    }

    // Helper function to shift a range of entries starting at a
    // given index with a given displacement.
    template <class T>
    void dynamic_array_container<T>::
        shift(const size_t &index, const ptrdiff_t &disp)
    {
        // Index out of bounds error comes first.
        if (index > m_size)
            throw index_error("Index out of bounds!");
        if (0 == disp)
            return;
        if (0 > index + disp)
            throw illegal_argument("Invalid displacement: index/indeces \
                smaller than 0 after shifting.");

        unchecked_shift(index, disp);
    }

//----------------------------------------------------------------------------
//                              Iterator
//----------------------------------------------------------------------------

    template <class T>
    dynamic_array_container<T>::iterator::
        iterator(dynamic_array_container<T>& container)
        : m_container(container), m_iter(&(container.m_data[0])) {}

    template <class T>
    dynamic_array_container<T>::iterator::
        iterator(const iterator &iter)
        : m_container(iter.m_container), m_iter(iter.m_iter) {}

    template <class T>
    dynamic_array_container<T>::iterator::
        ~iterator() {}

    template <class T>
    typename dynamic_array_container<T>::iterator&
        dynamic_array_container<T>::iterator::
        operator=(const iterator &rhs)
    {
        m_container = rhs.m_container;
        m_iter = rhs.m_iter;
        return *this;
    }

    template <class T>
    bool dynamic_array_container<T>::iterator::
        operator==(const iterator &rhs) const
    {
        return m_iter == rhs.m_iter;
    }

    template <class T>
    bool dynamic_array_container<T>::iterator::
        operator!=(const iterator &rhs) const
    {
        return m_iter != rhs.m_iter;
    }

    template <class T>
    bool dynamic_array_container<T>::iterator::
        operator<(const iterator &rhs) const
    {
        return m_iter < rhs.m_iter;
    }

    template <class T>
    bool dynamic_array_container<T>::iterator::
        operator>(const iterator &rhs) const
    {
        return m_iter > rhs.m_iter;
    }

    template <class T>
    bool dynamic_array_container<T>::iterator::
        operator<=(const iterator &rhs) const
    {
        return m_iter <= rhs.m_iter;
    }

    template <class T>
    bool dynamic_array_container<T>::iterator::
        operator>=(const iterator &rhs) const
    {
        return m_iter >= rhs.m_iter;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator& 
        dynamic_array_container<T>::iterator::
        operator++()
    {
        if (m_iter != &(m_container.m_data[m_container.m_size - 1]) + 1)
        {
            ++m_iter;
        }
        return *this;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator
        dynamic_array_container<T>::iterator::
        operator++(int)
    {
        auto old_iter = *this;
        ++*this;
        return old_iter;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator&
        dynamic_array_container<T>::iterator::
    operator--()
    {
        if (m_iter != &(m_container.m_data[0]))
        {
            --m_iter;
        }
        return *this;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator
        dynamic_array_container<T>::iterator::
        operator--(int)
    {
        auto old_iter = *this;
        --*this;
        return old_iter;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator&
        dynamic_array_container<T>::iterator::
        operator+=(size_type size)
    {
        m_iter += size;
        return *this;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator
        dynamic_array_container<T>::iterator::
        operator+(size_type size) const
    {
        auto old_iter = *this;
        old_iter += size;
        return old_iter;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator&
        dynamic_array_container<T>::iterator::
        operator-=(size_type size)
    {
        m_iter -= size;
        return *this;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator
        dynamic_array_container<T>::iterator::
        operator-(size_type size) const
    {
        auto old_iter = *this;
        old_iter -= size;
        return old_iter;
    }

    template <class T>
    T& dynamic_array_container<T>::iterator::
        operator*() const
    {
        return *m_iter;
    }

    template <class T>
    T* dynamic_array_container<T>::iterator::
        operator->() const
    {
        return m_iter;
    }

    template <class T>
    T& dynamic_array_container<T>::iterator::
        operator[](size_type index) const
    {

    }
}

#endif
