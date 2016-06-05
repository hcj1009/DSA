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
        : m_size(0)
        , m_capacity (DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY)
    {
        m_data = std::make_unique<T[]>(m_capacity);
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
        m_size = 0;
        m_capacity = DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY;
        m_data.reset(new T[m_capacity]);
    }

    template <class T>
    void dynamic_array_container<T>::
        reserve(const size_t &capacity)
    {
        m_capacity = capacity;
        auto new_data = new T[m_capacity];
        std::move(&m_data[0], &m_data[m_size], &new_data[0]);
        m_data.reset(new_data);
    }

    template <class T>
    void dynamic_array_container<T>::
        shrink()
    {
        m_capacity = capacity_of(m_size);
        auto new_data = new T[m_capacity];
        std::move(&m_data[0], &m_data[m_size], &new_data[0]);
        m_data.reset(new_data);
    }

    template <class T>
    void dynamic_array_container<T>::
        push_front(const T& entry)
    {
        shift_right(0);
        m_data[0] = entry;
    }

    template <class T>
    void dynamic_array_container<T>::
        push_front(T&& entry)
    {
        shift_right(0);
        m_data[0] = std::move(entry);
    }

    template <class T>
    void dynamic_array_container<T>::
        push_back(const T& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        m_data[m_size++] = entry;
    }

    template <class T>
    void dynamic_array_container<T>::
        push_back(T&& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        m_data[m_size++] = std::move(entry);
    }

    template <class T>
    void dynamic_array_container<T>::
        insert(const size_t& index, const T& entry)
    {
        shift_right(index);
        m_data[index] = entry;
    }

    template <class T>
    T dynamic_array_container<T>::
        pop_front()
    {
        auto entry = std::move(m_data[0]);
        remove(0);
        return entry;
    }

    template <class T>
    T dynamic_array_container<T>::
        pop_back()
    {
        auto entry = std::move(m_data[--m_size]);
        return entry;
    }

    template <class T>
    void dynamic_array_container<T>::
        remove(const size_t& index)
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds!");
        }
        if (index == m_size - 1)
        {
            --m_size;
        }
        else
        {
            shift_left(index + 1);
        }
    }

    template <class T>
    void dynamic_array_container<T>::
        remove(const T& entry)
    {
        // Get the index of the given entry.
        // Throw no_such_element exception if the entry does not exist.
        auto index = index_of(entry);
        remove(index);
    }

    template <class T>
    T dynamic_array_container<T>::
        at(const size_t& index) const
    {
        return m_data[index];
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    template <class T>
    inline size_t dynamic_array_container<T>::
        index_of(const T& entry) const
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
    bool dynamic_array_container<T>::
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

    template <class T>
    T* dynamic_array_container<T>::
        to_array() const
    {
        auto entries = new T[m_size];
        std::copy(&m_data[0], &m_data[m_size - 1], &entries[0]);
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
        capacity_of(const size_t& size) const
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
        ensure_capacity()
    {
        if (m_size == m_capacity)
        {
            m_capacity *= DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR;
            auto new_data = new T[m_capacity];
            std::move(&m_data[0], &m_data[m_size], &new_data[0]);
            m_data.reset(new_data);
        }
    }

    template <class T>
    void dynamic_array_container<T>::
        shift_left(const size_t& index)
    {
        std::move(&m_data[index], &m_data[m_size], &m_data[index - 1]);
        --m_size;
    }

    template <class T>
    void dynamic_array_container<T>::
        shift_right(const size_t& index)
    {
        if (index == m_size)
        {
            ensure_capacity();
        }
        else if (m_size < m_capacity)
        {
            std::move_backward(&m_data[index], 
                &m_data[m_size],
                &m_data[m_size + 1]);
        }
        else
        {
            m_capacity *= DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR;
            auto new_data = std::make_unique<T[]>(m_capacity);
            std::move(&m_data[0], &m_data[index], &new_data[0]);
            std::move(&m_data[index], &m_data[m_size], &new_data[index + 1]);
            m_data = std::move(new_data);
        }
        ++m_size;
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
        if (m_iter != &(m_container.m_data[m_container.m_size]))
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
        operator+=(size_t size)
    {
        m_iter += size;
        return *this;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator
        dynamic_array_container<T>::iterator::
        operator+(size_t size) const
    {
        auto old_iter = *this;
        old_iter += size;
        return old_iter;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator&
        dynamic_array_container<T>::iterator::
        operator-=(size_t size)
    {
        m_iter -= size;
        return *this;
    }

    template <class T>
    typename dynamic_array_container<T>::iterator
        dynamic_array_container<T>::iterator::
        operator-(size_t size) const
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
        operator[](size_t index) const
    {

    }
}

#endif
