#ifndef ARRAY_STACK_IMPL_H
#define ARRAY_STACK_IMPL_H

namespace DSA
{
    template <class T>
    array_stack<T>::array_stack(const size_t &base_capacity)
        : dynamic_array_container<T>(base_capacity) {}

    template <class T>
    array_stack<T>::array_stack(const array_stack<T> &stack)
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

    template <class T>
    array_stack<T>::array_stack(array_stack<T> &&stack) noexcept
    {
        base_impl::m_base_capacity =
            std::move(stack.base_impl::m_base_capacity);
        base_impl::m_capacity = std::move(stack.base_impl::m_capacity);
        base_impl::m_size = std::move(stack.base_impl::m_size);
        base_impl::m_data = std::move(stack.base_impl::m_data);
    }

    template <class T>
    array_stack<T>::~array_stack() {}

    // Return if the stack is empty.
    template <class T>
    bool array_stack<T>::empty() const
    {
        return base_impl::empty();
    }

    // Get the size of the stack.
    template <class T>
    size_t array_stack<T>::size() const
    {
        return base_impl::size();
    }

    // Get the capacity of the stack.
    template <class T>
    size_t array_stack<T>::capacity() const
    {
        return base_impl::capacity();
    }

    // Remove all the entries from the list, and free the memory.
    template <class T>
    void array_stack<T>::clear()
    {
        base_impl::clear();
    }

    // Get the entry on the top of the stack.
    template <class T>
    T array_stack<T>::peek() const
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot peek from an empty stack.");
        }
        return *(base_impl::m_data[base_impl::m_size - 1]);
    }

    // Push an entry to the top of the stack.
    template <class T>
    void array_stack<T>::push(const T &entry)
    {
        base_impl::ensure_capacity();
        base_impl::m_data[base_impl::m_size].reset(new T(entry));
        base_impl::m_size++;
    }

    template <class T>
    void array_stack<T>::push(T &&entry)
    {
        base_impl::ensure_capacity();
        base_impl::m_data[base_impl::m_size].reset(new T(std::move(entry)));
        base_impl::m_size++;
    }

    // Pop the top entry from the stack.
    template <class T>
    T array_stack<T>::pop()
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
    template <class T>
    bool array_stack<T>::contains(const T &entry) const
    {
        return base_impl::contains(entry);
    }

    template <class T>
    array_stack<T> &array_stack<T>::operator=(const array_stack<T> &stack)
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

    template <class T>
    array_stack<T> &array_stack<T>::operator=(array_stack<T> &&stack)
    {
        base_impl::m_base_capacity
            = std::move(stack.base_impl::m_base_capacity);
        base_impl::m_capacity = std::move(stack.base_impl::m_capacity);
        base_impl::m_size = std::move(stack.base_impl::m_size);
        base_impl::m_data = std::move(stack.base_impl::m_data);
        return *this;
    }
}

#endif