#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "adt_stack.h"
#include "dynamic_array_container.h"

// Array implementation of LIFO Stack data structure.
template <class T>
class array_stack 
    : public adt_stack<T>
    , public dynamic_array_container<T>
{
public:
    array_stack(const size_t &base_capacity = DEFAULT_BASE_CAPACITY)
        : dynamic_array_container(base_capacity) {}

    array_stack(const array_stack<T> &stack)
    {
        m_base_capacity = stack.m_base_capacity;
        m_capacity = stack.m_capacity;
        m_size = stack.m_size;
        m_data = new T[m_capacity];
        memcpy(m_data, stack.m_data, m_size * sizeof(T));
    }

    array_stack(array_stack<T> &&stack) noexcept
    {
        m_base_capacity = std::move(stack.m_base_capacity);
        m_capacity = std::move(stack.m_capacity);
        m_size = std::move(stack.m_size);
        m_data = std::move(stack.m_data);
        stack.m_size = 0;
        memset(stack.m_data, 0, m_size * sizeof(T));
    }

    virtual ~array_stack()
    {
        // delete[] m_data;
    }

    // Return if the stack is empty.
    virtual bool empty() const
    {
        return dynamic_array_container<T>::empty();
    }

    // Get the size of the stack.
    virtual size_t size() const
    {
        return dynamic_array_container<T>::size();
    }

    // Get the capacity of the stack.
    virtual size_t capacity() const
    {
        return dynamic_array_container<T>::capacity();
    }

    // Remove all the entries from the list, and free the memory.
    virtual void clear()
    {
        dynamic_array_container<T>::clear();
    }

    // Get the entry on the top of the stack.
    virtual T peek() const
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot peek from an empty stack.");
        }
        return m_data[m_size - 1];
    }

    // Push an entry to the top of the stack.
    virtual void push(const T &entry)
    {
        ensure_capacity();
        m_data[m_size] = entry;
        m_size++;
    }

    // Pop the top entry from the stack.
    virtual T pop()
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot pop from an empty stack.");
        }
        return m_data[--m_size];
    }

    // Return if the stack contains a given entry.
    virtual bool contains(const T &entry) const
    {
        return dynamic_array_container<T>::contains(entry);
        /*
        for (size_t i = 0; i < m_size; i++)
        {
            if (entry == m_data[i])
            {
                return true;
            }
        }
        return false;
        */
    }

    array_stack& operator=(const array_stack<T> &stack)
    {   
        if (stack.m_capacity > m_capacity)
        {
            delete[] m_data;
            m_capacity = stack.m_capacity;
            m_data = new T[m_capacity];
        }
        m_base_capacity = stack.m_base_capacity;
        m_size = stack.m_size;
        memcpy(m_data, stack.m_data, m_size * sizeof(T));
        memset(&(m_data[m_size]), 0, (m_capacity - m_size) * sizeof(T));
        return *this;
    }

    array_stack& operator=(array_stack<T> &&stack)
    {
        delete[] m_data;
        m_base_capacity = std::move(stack.m_base_capacity);
        m_capacity = std::move(stack.m_capacity);
        m_size = std::move(stack.m_size);
        m_data = std::move(stack.m_data);
        stack.m_size = 0;
        memset(stack.m_data, 0, m_size * sizeof(T));
        return *this;
    }
};

#endif