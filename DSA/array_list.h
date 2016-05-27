#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cmath>
#include <algorithm>
#include "dsaexcept.h"
#include "adt_list.h"

using std::min;
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

        ptrdiff_t new_index = index + disp;

        if (0 > new_index)
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
            /* Memory copy version.
               TODO Something is wrong. Fix later. *
            // Copy unchanged entries.
            memcpy(&(new_data[0]), &(m_data[0]), index * sizeof(T));
            // Copy shifted entries.
            memcpy(&(new_data[new_index]), &(m_data[index]),
                (m_size - index) * sizeof(T));
            /**/
            /* Move semantics version. */
            for (size_t i = 0; i < m_size; i++)
            {
                size_t in = i < min(index, (size_t)new_index) ? i : i + disp;
                new_data[in] = move(m_data[i]);
            }
            /**/
            delete[] m_data;
            m_data = new_data;
        }
        else if ((0 < disp) && (1 <= m_size))  // shifting right
        {
            for (size_t i = m_size - 1; i >= index; i--)
            {
                m_data[i + disp] = move(m_data[i]);
            }
            memset(&(m_data[index]), 0, disp * sizeof(T));
        }
        else    // case when displacement < 0, shifting left
        {
            for (size_t i = index; i < m_size; i++)
            {
                m_data[i + disp] = move(m_data[i]);
            }
            // TODO Something wrong with this, fix later:
            // memset(&(m_data[new_size]), 0, (-disp) * sizeof(T));
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
        memset(list.m_data, 0, list.m_capacity);
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
    virtual array_list 
        &operator=(array_list<T, BASE_CAPACITY> &&rhs)
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
            rhs.m_capacity = BASE_CAPACITY;
            rhs.m_size = 0;
            memset(rhs.m_data, 0, m_size);
        }
        return *this;
    }
};

#endif