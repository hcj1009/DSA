#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "adt_stack.h"
#include "dynamic_array_container.h"

namespace DSA
{
    // Array implementation of LIFO Stack data structure.
    template <class T>
    class array_stack
        : public adt_stack<T>
        , public dynamic_array_container<T>
    {
        typedef dynamic_array_container<T> base_impl;
        typedef std::shared_ptr<T> entry_ptr;
        typedef std::unique_ptr<std::shared_ptr<T>[]> data_ptr;
    public:
        array_stack(const size_t &base_capacity 
                = base_impl::DEFAULT_BASE_CAPACITY)
            : dynamic_array_container<T>(base_capacity) {}

        array_stack(const array_stack<T> &stack)
        {
            base_impl::m_base_capacity = stack.base_impl::m_base_capacity;
            base_impl::m_capacity = stack.base_impl::m_capacity;
            base_impl::m_size = stack.base_impl::m_size;
            base_impl::m_data = data_ptr(new entry_ptr[base_impl::m_capacity]);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[i]
                    = std::shared_ptr<T>(stack.base_impl::m_data[i]);
            }
        }

        array_stack(array_stack<T> &&stack) noexcept
        {
            base_impl::m_base_capacity = 
                std::move(stack.base_impl::m_base_capacity);
            base_impl::m_capacity = std::move(stack.base_impl::m_capacity);
            base_impl::m_size = std::move(stack.base_impl::m_size);
            base_impl::m_data = std::move(stack.base_impl::m_data);
        }

        virtual ~array_stack() {}

        // Return if the stack is empty.
        virtual bool empty() const
        {
            return base_impl::empty();
        }

        // Get the size of the stack.
        virtual size_t size() const
        {
            return base_impl::size();
        }

        // Get the capacity of the stack.
        virtual size_t capacity() const
        {
            return base_impl::capacity();
        }

        // Remove all the entries from the list, and free the memory.
        virtual void clear()
        {
            base_impl::clear();
        }

        // Get the entry on the top of the stack.
        virtual T peek() const
        {
            if (0 == base_impl::m_size)
            {
                throw empty_container("Cannot peek from an empty stack.");
            }
            return *(base_impl::m_data[base_impl::m_size - 1]);
        }

        // Push an entry to the top of the stack.
        virtual void push(const T &entry)
        {
            base_impl::ensure_capacity();
            base_impl::m_data[base_impl::m_size].reset(new T(entry));
            base_impl::m_size++;
        }

        virtual void push(T &&entry)
        {
            base_impl::ensure_capacity();
            base_impl::m_data[base_impl::m_size].reset(new T(std::move(entry)));
            base_impl::m_size++;
        }

        // Pop the top entry from the stack.
        virtual T pop()
        {
            if (0 == base_impl::m_size)
            {
                throw empty_container("Cannot pop from an empty stack.");
            }
            T cur_entry = std::move(*base_impl::m_data[base_impl::m_size - 1]);
            base_impl::shift(base_impl::m_size, -1);
            return cur_entry;
        }

        // Return if the stack contains a given entry.
        virtual bool contains(const T &entry) const
        {
            return base_impl::contains(entry);
        }

        array_stack& operator=(const array_stack<T> &stack)
        {
            if (stack.base_impl::m_capacity > base_impl::m_capacity)
            {
                base_impl::m_capacity = stack.base_impl::m_capacity;
                base_impl::m_data = data_ptr(new entry_ptr[base_impl::m_capacity]);
            }
            base_impl::m_base_capacity = stack.base_impl::m_base_capacity;
            base_impl::m_size = stack.base_impl::m_size;
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[i] = stack.base_impl::m_data[i];
            }
            return *this;
        }

        array_stack& operator=(array_stack<T> &&stack)
        {
            base_impl::m_base_capacity
                = std::move(stack.base_impl::m_base_capacity);
            base_impl::m_capacity = std::move(stack.base_impl::m_capacity);
            base_impl::m_size = std::move(stack.base_impl::m_size);
            base_impl::m_data = std::move(stack.base_impl::m_data);
            return *this;
        }
    };
}

#endif
