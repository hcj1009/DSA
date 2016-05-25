#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "adt_stack.h"
#include "empty_stack.h"

// Array implementation of LIFO Stack data structure.
template <class T,
    size_t BASE_CAPACITY = 10>
class array_stack : adt_stack<T>
{
private:
    T *stack_data;
    size_t stack_size;
    size_t stack_capacity;

    // Helper function to double the capacity of the stack when it is full.
    void ensure_capacity()
    {
        if (stack_size == stack_capacity)
        {
            stack_capacity *= 2;
            T *new_data = new T[stack_capacity];
            for (size_t i = 0; i < stack_size; i++)
            {
                new_data[i] = stack_data[i];
            }
            delete[] stack_data;
            stack_data = new_data;
        }
    }

public:
    array_stack() : adt_stack()
    {
        stack_capacity = BASE_CAPACITY;
        stack_data = new T[stack_capacity];
        stack_size = 0;
    }

    virtual ~array_stack()
    {
        delete[] stack_data;
    }

    // Return if the stack is empty.
    virtual bool empty() const
    {
        return (0 == stack_size);
    }

    // Get the size of the stack.
    virtual size_t size() const
    {
        return stack_size;
    }

    // Get the capacity of the stack.
    virtual size_t capacity() const
    {
        return stack_capacity;
    }

    // Get the entry on the top of the stack.
    virtual T peek() const
    {
        if (0 == stack_size)
        {
            throw empty_stack("Cannot peek from an empty stack.");
        }
        return stack_data[stack_size - 1];
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
        stack_data[stack_size] = entry;
        stack_size++;
    }

    // Pop the top entry from the stack.
    virtual T pop()
    {
        if (0 == stack_size)
        {
            throw empty_stack("Cannot pop from an empty stack.");
        }
        return stack_data[--stack_size];
    }

    // Remove all the entries from the list, and free the memory.
    virtual void clear()
    {
        delete[] stack_data;
        stack_capacity = BASE_CAPACITY;
        stack_data = new T[stack_capacity];
        stack_size = 0;
    }

    // Return if the list stack a given entry.
    virtual bool contains(const T &entry) const
    {
        for (size_t i = 0; i < stack_size; i++)
        {
            if (entry == stack_data[i])
            {
                return true;
            }
        }
        return false;
    }
};

#endif