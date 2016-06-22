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
        m_front = 0;
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
        m_front = 0;
        m_back = m_capacity - 1;
    }

    template <class T>
    void circular_array_container<T>::
        reserve(const size_t& capacity)
    {
        m_capacity = capacity;
        auto new_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i)
        {
            new_data[i] = std::move(m_data[m_front]);
            index_self_inc(m_front);
        }
        delete[] m_data;
        m_data = new_data;
		m_front = 0;
		m_back = m_capacity - 1;
    }

    template <class T>
    void circular_array_container<T>::
        shrink()
    {
        m_capacity = m_size <= CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY
            ? CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY : m_size;
        auto new_data = new T[m_capacity];
        for (auto i = 0; i < m_size; ++i)
        {
            new_data[i] = std::move(m_data[m_front]);
            index_self_inc(m_front);
        }
        delete[] m_data;
        m_data = new_data;
        m_front = 0;
        m_back = m_capacity - 1;
    }

    template <class T>
    void circular_array_container<T>::
        push_front(const T& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        m_data[index_self_dec(m_front)] = entry;
        ++m_size;
    }

    template <class T>
    void circular_array_container<T>::
        push_front(T&& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
		m_data[index_self_dec(m_front)] = std::move(entry);
        ++m_size;
    }

    template <class T>
    void circular_array_container<T>::
        push_back(const T& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        m_data[index_self_inc(m_back)] = entry;
        ++m_size;
    }

    template <class T>
    void circular_array_container<T>::
        push_back(T&& entry)
    {
        if (m_size == m_capacity)
            ensure_capacity();
        m_data[index_self_inc(m_back)] = std::move(entry);
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
            shift_right(index);
            m_data[index_inc(m_front, index)] = entry;
            ++m_size;
        }
    }

	template <class T>
	void circular_array_container<T>::
		insert(const size_t& index, T&& entry)
	{
		if (index > m_size)
		{
			throw index_error("Index out of bounds");
		}
		if (0 == index)
		{
			push_front(std::move(entry));
		}
		else if (m_size == index)
		{
			push_back(std::move(entry));
		}
		else
		{
			shift_right(index);
			m_data[index_inc(m_front, index)] = std::move(entry);
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
        auto entry = std::move(m_data[m_front]);
        index_self_inc(m_front);
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
        auto entry = std::move(m_data[m_back]);
        index_self_dec(m_back);
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
		if (0 == index)
		{
			index_self_inc(m_front);
		}
		else if (m_size - 1 == index)
		{
			index_self_dec(m_back);
		}
		else
		{
			shift_left(index + 1);
		}
        --m_size;
    }

    template <class T>
    T circular_array_container<T>::
        at(const size_t& index) const
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds");
        }
        return m_data[index_inc(m_front, index)];
    }

    template <class T>
    size_t circular_array_container<T>::
        index_of(const T& entry) const
    {
        if (0 != m_size)
        {
            size_t index = m_front;
            while (index <= m_back)
            {
                if (entry == m_data[index])
                {
                    index += (m_capacity - m_front);
                    return index % m_capacity;
                }
                ++index;
                index %= m_capacity;
            }
        }
        throw no_such_element("Cannot find such entry in the container.");
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
        auto src_index = m_front;
        auto dest_index = 0;
        while (dest_index < m_size)
        {
            entries[dest_index] = m_data[src_index];
            ++dest_index;
            ++src_index;
            src_index %= m_capacity;
        }
        return entries;
    }

//----------------------------------------------------------------------------
//                        Private/Protected Functions
//----------------------------------------------------------------------------

    template <class T>
    size_t circular_array_container<T>::
        index_inc(const size_t& index, const size_t& inc) const
    {
		auto new_index = index + inc;
		if (new_index >= m_capacity)
			new_index %= m_capacity;
		return new_index;
    }
    
    template <class T>
    size_t circular_array_container<T>::
        index_self_inc(size_t& index, const size_t& inc)
    {
		index += inc;
		if (index >= m_capacity)
			index %= m_capacity;
        return index;
    }

    template <class T>
    size_t circular_array_container<T>::
        index_dec(const size_t& index, const size_t& dec) const
    {
        // TODO Fix the case when (dec - new_index) % m_capacity == 0;
        auto new_index = index >= dec ? index - dec 
            : m_capacity - (dec - index) % m_capacity;
        return new_index;
    }

    template <class T>
    size_t circular_array_container<T>::
        index_self_dec(size_t& index, const size_t& dec)
    {
        if (index >= dec)
        {
            index -= dec;
        }
        else
        {
            index = m_capacity - (dec - index) % m_capacity;
        }
        return index;
    }

    template <class T>
    bool circular_array_container<T>::
        index_gt(const size_t& index1, const size_t& index2)
    {
        
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
        for (size_t i = 0; i < m_size; ++i)
        {
            new_data[i] = std::move(m_data[m_front]);
            index_self_inc(m_front);
        }
        delete[] m_data;
        m_data = new_data;
		m_front = 0;
		m_back = m_size - 1;
    }

    template <class T>
    void circular_array_container<T>::
        ensure_capacity(const size_t& size)
    {
        m_capacity = capacity_of(size);
        auto new_data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i)
        {
            new_data[i] = std::move(m_data[m_front]);
            index_self_inc(m_front);
        }
        delete[] m_data;
        m_data = new_data;
		m_front = 0;
		m_back = m_size - 1;
    }

    template <class T>
    void circular_array_container<T>::
        shift_left(const size_t& index, const size_t& dis)
    {
    }

    template <class T>
    void circular_array_container<T>::
        shift_right(const size_t& index, const size_t& dis)
    {
        if (m_size += dis > m_capacity)
        {
            ensure_capacity(m_size + dis);
        }
		auto r_index = index_inc(m_front, index);
        size_t dest_index, src_index;
        if (m_size / 2 > index)
        {
            dest_index = index_dec(m_front, dis);
            src_index = m_front;
            while (src_index != r_index)
            {
                m_data[dest_index] = std::move(m_data[src_index]);
                index_self_inc(dest_index);
                index_self_inc(src_index);
            }
            index_self_dec(m_front, dis);
        }
        else
        {
            dest_index = index_inc(m_back, dis);
            src_index = m_back;
            while (src_index != index_dec(r_index))
            {
                m_data[dest_index] = std::move(m_data[src_index]);
                index_self_dec(dest_index);
                index_self_dec(src_index);
            }
            index_self_inc(m_back, dis);
        }
    }

    template <class T>
    size_t circular_array_container<T>::
        distance(const size_t& index1, const size_t& index2)
    {
        if ((index1 > m_front && index2 > m_front) 
            || (index1 < m_back && index2 < m_back))
            return abs(index2 - index1);
        else
           return (m_capacity - abs(index2 - index1));
    }

//----------------------------------------------------------------------------
//                                  Iterator
//----------------------------------------------------------------------------

	template <class T>
	circular_array_container<T>::iterator::
		iterator(circular_array_container<T>& container)
		: m_container(container), m_ptr(&m_container.m_data[0]) {}

	template <class T>
	circular_array_container<T>::iterator::
		iterator(const iterator& iter)
		: m_container(iter.m_container), m_ptr(iter.m_ptr) {}
	
	template <class T>
	circular_array_container<T>::iterator::
		~iterator() {}

	template <class T>
	typename circular_array_container<T>::iterator&
		circular_array_container<T>::iterator::
		operator=(const iterator& rhs)
	{
		m_container = rhs.m_container;
		m_ptr = rhs.m_ptr;
		return *this;
	}

	template <class T>
	bool circular_array_container<T>::iterator::
		operator==(const iterator& rhs) const
	{
		return (m_ptr == rhs.m_ptr);
	}

	template <class T>
	bool circular_array_container<T>::iterator::
		operator!=(const iterator& rhs) const
	{
		return (m_ptr != rhs.m_ptr);
	}

	template <class T>
	bool circular_array_container<T>::iterator::
		operator<(const iterator& rhs) const
	{
		return (m_ptr < rhs.m_ptr);
	}

	template <class T>
	bool circular_array_container<T>::iterator::
		operator>(const iterator& rhs) const
	{
		return (m_ptr > rhs.m_ptr);
	}

	template <class T>
	bool circular_array_container<T>::iterator::
		operator<=(const iterator& rhs) const
	{
		return (m_ptr <= rhs.m_ptr);
	}

	template <class T>
	bool circular_array_container<T>::iterator::
		operator>=(const iterator& rhs) const
	{
		return (m_ptr >= rhs.m_ptr);
	}

	template <class T>
	typename circular_array_container<T>::iterator&
		circular_array_container<T>::iterator::
		operator++()
	{
		if ((&m_container.m_data[m_container.m_back] + 1) != m_ptr)
		{
			if (&m_container.m_data[m_container.m_capacity - 1] != m_ptr)
			{
				++m_ptr;
			}
			else
			{
				m_ptr = &m_container.m_data[0];
			}
		}
		return *this;
	}

	template <class T>
	typename circular_array_container<T>::iterator
		circular_array_container<T>::iterator::
		operator++(int)
	{
		iterator old_iter(*this);
		++*this;
		return old_iter;
	}

	template <class T>
	typename circular_array_container<T>::iterator&
		circular_array_container<T>::iterator::
		operator--()
	{
		if (&m_container.m_data[m_container.m_front] != m_ptr)
		{
			if (&m_container.m_data[0] != m_ptr)
			{
				--m_ptr;
			}
			else
			{
				m_ptr = &m_container.m_data[m_container.m_capacity - 1];
			}
		}
		return *this;
	}

	template <class T>
	typename circular_array_container<T>::iterator
		circular_array_container<T>::iterator::
		operator--(int)
	{
		iterator old_iter(*this);
		--*this;
		return old_iter;
	}
}

#endif
