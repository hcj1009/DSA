#ifndef DYNAMIC_ARRAY_CONTAINER_H
#define DYNAMIC_ARRAY_CONTAINER_H

#include <cmath>
#include <algorithm>
#include "base_container.h"

template <class T>
class dynamic_array_container : public base_container<T>
{
protected:
    // Natural log 2, used in function capacity_of(const size_t &)
    const double LOG2 = 0.6931471805599453;
    static const size_t DEFAULT_BASE_CAPACITY = 10;

    T *m_data;
    size_t m_capacity;
    size_t m_base_capacity;

    // Helper function to determine the capacity needed to hold a
    // given size of list.
    inline size_t capacity_of(const size_t &size) const
    {
        // TODO Optimize this:
        return (size_t)pow(2, ceil(log((double)size / m_base_capacity) \
            / LOG2)) * m_base_capacity;
    }

    // Helper function to enlarge the capacity when the container is full.
    inline void ensure_capacity()
    {
        if (m_size >= m_capacity)
        {
            m_capacity = m_size < 2 * m_capacity 
                ? 2 * m_capacity : capacity_of(m_size);
            T *new_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; i++)
            {
                new_data[i] = std::move(m_data[i]);
            }
            memset((&new_data[m_size]), 0, (m_capacity - m_size) * sizeof(T));
            delete[] m_data;
            m_data = new_data;
        }
    }

    // Helper function to shift a range of entries starting at a
    // given index with a given displacement.
    void shift(const size_t &index,
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

        size_t new_size = m_size + disp;
        size_t new_capacity = capacity_of(new_size);

        if (new_capacity > m_capacity)
        {
            m_capacity = new_capacity;
            T *new_data = new T[m_capacity];
            memset(new_data, 0, m_capacity);
            for (size_t i = 0; i < m_size; i++)
            {
                size_t in = i < index ? i : i + disp;
                new_data[in] = std::move(m_data[i]);
            }
            delete[] m_data;
            m_data = new_data;
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
                m_data[dest + i * sign] =
                    std::move(m_data[src + i * sign]);
            }
            memset(&(m_data[cls]), 0, -sign * disp * sizeof(T));
        }
        m_size = new_size;
    }

public:
    dynamic_array_container
    (const size_t &base_capacity = DEFAULT_BASE_CAPACITY)
        : base_container()
    {
        m_base_capacity = base_capacity;
        m_capacity = m_base_capacity;
        m_data = new T[m_capacity];
        memset(m_data, 0, m_capacity * sizeof(T));
    }

    virtual ~dynamic_array_container()
    {
        // delete[] m_data;
    }

    virtual size_t capacity() const
    {
        return m_capacity;
    }

    virtual void clear()
    {
        base_container<T>::clear();
        m_capacity = m_base_capacity;
        m_data = new T[m_capacity];
        memset(m_data, 0, m_capacity * sizeof(T));
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    virtual size_t index_of(const T &entry) const
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if (entry == m_data[i])
            {
                return i;
            }
        }
        throw no_such_element("Cannot find such entry in the container.");
    }

    // Return if the container contains a given entry.
    virtual bool contains(const T &entry) const
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
};

#endif