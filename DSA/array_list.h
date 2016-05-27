#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cmath>
#include <algorithm>
#include "dsaexcept.h"
#include "adt_list.h"

using std::move;

// Array-based List implementation.
template <class T,
    size_t BASE_CAPACITY = 10>
class array_list : public adt_list<T>
{
protected:
    // Natural log 2, used in function capacity_of(const size_t &)
    const double LOG2 = 0.6931471805599453;

    T *m_data;
    size_t m_size;
    size_t m_capacity;

    // Helper function to determine the capacity needed to hold a
    // given size of list.
    inline size_t capacity_of(const size_t &size)
    {
        return (size_t)pow(2, ceil(log((double) size / BASE_CAPACITY) \
            / LOG2)) * BASE_CAPACITY;
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
                new_data[in] = move(m_data[i]);
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
                    move(m_data[src + i * sign]);
            }
            memset(&(m_data[cls]), 0, -sign * disp * sizeof(T));
        }
        m_size = new_size;
    }

public:
    // Default constructor of the list.
    array_list() : adt_list()
    {
        m_capacity = BASE_CAPACITY;
        m_size = 0;
        m_data = new T[m_capacity];
        memset(m_data, 0, m_capacity);
    }

    // Builda list based on a given list.
    array_list(const array_list<T, BASE_CAPACITY> &list)
    {
        m_capacity = list.m_capacity;
        m_size = list.m_size;
        m_data = new T[m_capacity];
        memset(m_data, 0, m_capacity);
        memcpy(m_data, list.m_data, m_size * sizeof(T));
    }

    array_list(array_list<T, BASE_CAPACITY> *list)
    {
        m_capacity = list->m_capacity;
        m_size = list->m_size;
        m_data = new T[m_capacity];
        memset(m_data, 0, m_capacity);
        memcpy(m_data, list->m_data, m_size * sizeof(T));
    }

    // Move constructor: build a list based on a given list (rvalue).
    array_list(array_list<T, BASE_CAPACITY> &&list) noexcept
    {
        m_capacity = move(list.m_capacity);
        m_size = move(list.m_size);
        m_data = move(list.m_data);
        list.m_capacity = BASE_CAPACITY;
        list.m_size = 0;
        memset(list.m_data, 0, list.m_capacity * sizeof(T));
    }

    // Build a list based on a given array of entries.
    array_list(const T entries[], const size_t &size)
        : adt_list(entries, size)
    {
        m_capacity = capacity_of(size);
        m_size = size;
        m_data = new T[m_capacity];
        memset(m_data, 0, m_capacity);
        memcpy(m_data, entries, m_size * sizeof(T));
    }

    // Default destructor fo the list.
    virtual ~array_list()
    {
        //delete[] m_data;
    }

    // Return if the container is empty.
    virtual bool empty() const
    {
        return (0 == m_size);
    }

    // Get the size of the list.
    virtual size_t size() const
    {
        return m_size;
    }
    
    // Get the capacity of the list;
    virtual size_t capacity() const
    {
        return m_capacity;
    }

    // Add a given entry to the container.
    virtual void add(const T &entry)
    {
        shift(m_size, 1);
        m_data[m_size - 1] = entry;
    }

    // Add a given entry to a given index of the list.
    virtual void add(const size_t &index, const T &entry)
    {
        if (index > m_size)
        {
            throw index_error("Index out of bounds.");
        }
        shift(index, 1);
        m_data[index] = entry;
    }

    /**/
    virtual void add(const T entries[], const size_t &size)
    {
        shift(m_size, size);
        memcpy(&(m_data[m_size]), entries, size);
    }
    
    virtual void add(const size_t &index,
        const T entries[],
        const size_t &size)
    {
        if (index > m_size)
        {
            throw index_error("Index out of bounds.");
        }
        shift(index, size);
        memcpy(&(m_data[index]), entries, size);
    }

    virtual void add(const array_list<T, BASE_CAPACITY> &list)
    {
        shift(m_size, list.m_size);
        memcpy(&(m_data[m_size]), list.m_data, list.m_size);
    }

    virtual void add(const size_t &index, 
        const array_list<T, BASE_CAPACITY> &list)
    {
        if (index > m_size)
        {
            throw index_error("Index out of bounds.");
        }
        shift(index, list.m_size);
        memcpy(&(m_data[index]), list.m_data, list.m_size);
    }

    virtual void add(array_list<T, BASE_CAPACITY> &&list)
    {
        shift(m_size, list.m_size);
        for (size_t i = 0; i < list.m_size; i++)
        {
            m_data[m_size + i] = move(list.m_data[i]);
        }
        list.m_size = 0;
        memset(list.m_data, 0, list.m_capacity * sizeof(T));
    }

    virtual void add(const size_t &index,
        array_list<T, BASE_CAPACITY> &&list)
    {
        if (index > m_size)
        {
            throw index_error("Index out of bounds.");
        }
        shift(index, list.m_size);
        for (size_t i = 0; i < list.m_size; i++)
        {
            m_data[index + i] = move(list.m_data[i]);
        }
        list.m_size = 0;
        memset(list.m_data, 0, list.m_capacity * sizeof(T));
    }

    /**/

    // Remove the entry at a given index from the list.
    virtual T remove(const size_t &index)
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds.");
        }
        T rm = m_data[index];
        shift(index + 1, -1);
        return rm;
    }

    // Remove a given entry from the list.
    virtual void remove(const T &entry)
    {
        size_t index = index_of(entry);
        remove(index);
    }

    // Get the entry at a given index.
    virtual T get(const size_t &index) const
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds.");
        }
        return m_data[index];
    }

    // Set the value of the entry at a given index to a given entry.
    // Throw index_error exception.
    virtual void set(const size_t &index, const T &entry)
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds.");
        }
        m_data[index] = entry;
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
        throw no_such_element("Cannot get the index of an entry that \
is not in the list.");
    }

    // Remove all the entries from the list, and free the memory.
    virtual void clear()
    {
        delete[] m_data;
        m_capacity = BASE_CAPACITY;
        m_size = 0;
        m_data = new T[m_capacity];
        memset(m_data, 0, m_capacity);
    }

    // Return if the list contains a given entry.
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

    // Get the pointer pointing to an array that represents the list.
    virtual T *to_array() const
    {
        T *copy_data = new T[m_size];
        memcpy(copy_data, m_data, m_size * sizeof(T));
        return copy_data;
    }

    // Override assignment expression.
    virtual array_list 
        &operator=(const array_list<T, BASE_CAPACITY> &rhs)
    {
        if (rhs.m_capacity != m_capacity)
        {
            delete[] m_data;
            m_data = new T[m_capacity = rhs.m_capacity];
        }
        memset(m_data, 0, m_capacity);
        m_size = rhs.m_size;
        memcpy(m_data, rhs.m_data, rhs.m_size * sizeof(T));
        return *this;
    }

    // Cases when the right-hand expression is rvalue.
    virtual array_list<T, BASE_CAPACITY> &operator=
        (array_list<T, BASE_CAPACITY> &&rhs)
    {
        if (!rhs.m_data)
        {
            clear();
        }
        else
        {
            delete[] m_data;
            m_capacity = move(rhs.m_capacity);
            m_size = move(rhs.m_size);
            m_data = move(rhs.m_data);
            rhs.m_size = 0;
            memset(rhs.m_data, 0, rhs.m_capacity);
        }
        return *this;
    }

    array_list<T, BASE_CAPACITY> &operator+=
        (const T &rhs)
    {
        add(rhs);
        return *this;
    }

    friend array_list<T, BASE_CAPACITY> operator+
        (const array_list<T, BASE_CAPACITY> &lhs, const T &rhs)
    {
        array_list<T, BASE_CAPACITY> new_list(lhs);
        new_list.add(rhs);
        return new_list;
    }
};

#endif