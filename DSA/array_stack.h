#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "adt_stack.h"
#include "dsaexcept.h"

// Array implementation of LIFO Stack data structure.
template <class T,
    size_t BASE_CAPACITY = 10>
class array_stack : adt_stack<T>
{
private:
    T *m_data;
    size_t m_size;
    size_t m_capacity;

    // Helper function to double the capacity of the stack when it is full.
    void ensure_capacity()
    {
        if (m_size == m_capacity)
        {
            m_capacity *= 2;
            T *new_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; i++)
            {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
        }
    }

public:
    array_stack() : adt_stack()
    {
        m_capacity = BASE_CAPACITY;
        m_data = new T[m_capacity];
        m_size = 0;
    }

    virtual ~array_stack()
    {
        delete[] m_data;
    }

    // Return if the stack is empty.
    virtual bool empty() const
    {
        return (0 == m_size);
    }

    // Get the size of the stack.
    virtual size_t size() const
    {
        return m_size;
    }

    // Get the capacity of the stack.
    virtual size_t capacity() const
    {
        return m_capacity;
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

    // Add a given entry to the stack.
    virtual void add(const T &entry)
    {
        push(entry);
    }

    // Push an entry to the top of the stack.
    // Alias for add(const T &entry)
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

    // Remove all the entries from the list, and free the memory.
    virtual void clear()
    {
        delete[] m_data;
        m_capacity = BASE_CAPACITY;
        m_data = new T[m_capacity];
        m_size = 0;
    }

    // Return if the stack contains a given entry.
    virtual bool contains(const T &entry) const
    {
        for (size_t i = 0; i < m_size; i++)
        {
            if (entry == m_data[i])
            {
                return true;
            }
        }
        return false;
    }
};

#endif