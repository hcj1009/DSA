#ifndef ARRAY_STACK_IMPL_H
#define ARRAY_STACK_IMPL_H

namespace DSA
{
    template <class T>
    array_stack<T>::array_stack() : cont()
    {
        static_assert(
            sequence_container_traits<Container>::is_sequence_container
            , "Specified container is not a sequence container. Abort!");
    }

    template <class T>
    array_stack<T>::array_stack(const array_stack<T> &stack) {}

    template <class T>
    array_stack<T>::array_stack(array_stack<T> &&stack) noexcept {}

    template <class T>
    array_stack<T>::~array_stack() {}

    // Return if the stack is empty.
    template <class T>
    bool array_stack<T>::empty() const
    {
        return cont.empty();
    }

    // Get the size of the stack.
    template <class T>
    size_t array_stack<T>::size() const
    {
        return cont.size();
    }

    // Get the capacity of the stack.
    template <class T>
    size_t array_stack<T>::capacity() const
    {
        if (sequence_container_traits<Container>::support_capacity)
        {
            return cont.capacity();
        }
        else
        {
            return cont.size();
        }
    }

    // Remove all the entries from the list, and free the memory.
    template <class T>
    void array_stack<T>::clear()
    {
        cont.clear();
    }

    // Get the entry on the top of the stack.
    template <class T>
    T array_stack<T>::peek() const
    {
        static_assert(
            sequence_container_traits<Container>::support_front
            , "Specified container does not support peek() function. Abort!");
        return count.
    }

    // Push an entry to the top of the stack.
    template <class T>
    void array_stack<T>::push(const T &entry)
    {

    }

    template <class T>
    void array_stack<T>::push(T &&entry)
    {

    }

    // Pop the top entry from the stack.
    template <class T>
    T array_stack<T>::pop()
    {
        
    }

    // Return if the stack contains a given entry.
    template <class T>
    bool array_stack<T>::contains(const T &entry) const
    {
        return con.contains(entry);
    }

    template <class T>
    array_stack<T> &array_stack<T>::operator=(const array_stack<T> &stack)
    {
        return *this;
    }

    template <class T>
    array_stack<T> &array_stack<T>::operator=(array_stack<T> &&stack)
    {
        return *this;
    }
}

#endif