#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "dynamic_array_container.h"
#include "adt_list.h"

// Array-based List implementation.
template <class T,
    size_t BASE_CAPACITY = 10>
class array_list
    : public adt_list<T>
    , public dynamic_array_container<T, BASE_CAPACITY>
{
    typedef dynamic_array_container<T, BASE_CAPACITY> super;
public:
    // Default constructor of the list.
    array_list() : dynamic_array_container(), adt_list() {}

    // Builda list based on a given list.
    array_list(const array_list<T, BASE_CAPACITY> &list)
    {
        m_size = list.m_size;
        m_capacity = list.m_capacity;
        m_data = new T[m_capacity];
        memset(m_data, 0, m_capacity);
        memcpy(m_data, list.m_data,
            m_size * sizeof(T));
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
        m_capacity = std::move(list.m_capacity);
        m_size = std::move(list.m_size);
        m_data = std::move(list.m_data);
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
        return dynamic_array_container<T, BASE_CAPACITY>::empty();
    }

    // Get the size of the list.
    virtual size_t size() const
    {
        return dynamic_array_container<T, BASE_CAPACITY>::size();
    }

    // Get the capacity of the list;
    virtual size_t capacity() const
    {
        return dynamic_array_container<T, BASE_CAPACITY>::capacity();
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
        memcpy(&(m_data[m_size]), entries, size * sizeof(T));
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
        memcpy(&(m_data[index]), entries, size * sizeof(T));
    }

    virtual void add(const array_list<T, BASE_CAPACITY> &list)
    {
        shift(m_size, list.m_size);
        memcpy(&(m_data[m_size]), list.m_data, list.m_size * sizeof(T));
    }

    virtual void add(const size_t &index, 
        const array_list<T, BASE_CAPACITY> &list)
    {
        if (index > m_size)
        {
            throw index_error("Index out of bounds.");
        }
        shift(index, list.m_size);
        memcpy(&(m_data[index]), list.m_data, list.m_size * sizeof(T));
    }

    virtual void add(array_list<T, BASE_CAPACITY> &&list)
    {
        shift(m_size, list.m_size);
        for (size_t i = 0; i < list.m_size; i++)
        {
            m_data[m_size + i] = std::move(list.m_data[i]);
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
            m_data[index + i] = std::move(list.m_data[i]);
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

    // Remove all the entries from the list, and free the memory.
    virtual void clear()
    {
        dynamic_array_container<T, BASE_CAPACITY>::clear();
    }

    virtual size_t index_of(const T &entry) const
    {
        return dynamic_array_container<T, BASE_CAPACITY>::index_of(entry);
    }

    // Return if the list contains a given entry.
    virtual bool contains(const T &entry) const
    {
        return dynamic_array_container<T, BASE_CAPACITY>::contains(entry);
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
            m_capacity = std::move(rhs.m_capacity);
            m_size = std::move(rhs.m_size);
            m_data = std::move(rhs.m_data);
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