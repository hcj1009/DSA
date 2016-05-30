#ifndef ARRAY_QUEUE_IMPL_H
#define ARRAY_QUEUE_IMPL_H

namespace DSA
{
    template <class T>
    size_t array_queue<T>::increase_index(const size_t &index,
        const size_t &increment) const
    {
        return (index + increment) % (base_impl::m_capacity + 1);
    }

    // Helper function to double the capacity of the queue when it is full.
    template <class T>
    void array_queue<T>::ensure_capacity()
    {
        // When the circular array is full
        if (increase_index(m_back, 2) == m_front)
        {
            size_t new_capacity = 2 * base_impl::m_capacity;
            data_ptr new_data = data_ptr(new entry_ptr[new_capacity]);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                new_data[i] = base_impl::m_data[increase_index(m_front, i)];
            }
            base_impl::m_data = std::move(new_data);
            m_front = 0;
            m_back = base_impl::m_size - 1;
            base_impl::m_capacity = new_capacity;
        }
    }

    template <class T>
    array_queue<T>::array_queue(const size_t &base_capacity)
    {
        base_impl::m_base_capacity = base_capacity;
        base_impl::m_capacity = base_impl::m_base_capacity;
        m_front = 0;
        m_back = base_impl::m_capacity;
        base_impl::m_data = data_ptr(new entry_ptr[base_impl::m_capacity + 1]);
    }

    template <class T>
    array_queue<T>::array_queue(const array_queue<T> &queue)
    {
        base_impl::m_base_capacity = queue.base_impl::m_base_capacity;
        base_impl::m_capacity = queue.base_impl::m_capacity;
        base_impl::m_size = queue.base_impl::m_size;
        m_front = queue.m_front;
        m_back = queue.m_back;
        base_impl::m_data = data_ptr(new entry_ptr[base_impl::m_capacity]);
        for (size_t i = 0; i < base_impl::m_size; i++)
        {
            base_impl::m_data[i] = std::shared_ptr<T>(queue.base_impl::m_data[i]);
        }
    }

    template <class T>
    array_queue<T>::array_queue(array_queue<T> &&queue) noexcept
    {

        base_impl::m_base_capacity
            = std::move(queue.base_impl::m_base_capacity);
        base_impl::m_capacity = std::move(queue.base_impl::m_base_capacity);
        base_impl::m_size = std::move(queue.base_impl::m_size);
        m_front = std::move(queue.m_front);
        m_back = std::move(queue.m_back);
        base_impl::m_data = std::move(queue.base_impl::m_data);
    }

    // Default destructor.
    template <class T>
    array_queue<T>::~array_queue() { }

    // Return if the queue is empty.
    template <class T>
    bool array_queue<T>::empty() const
    {
        return base_impl::empty();
    }

    // Get the size of the queue.
    template <class T>
    size_t array_queue<T>::size() const
    {
        return base_impl::size();
    }

    // Get the capacity of the queue.
    template <class T>
    size_t array_queue<T>::capacity() const
    {
        return base_impl::capacity();
    }

    // Get the first entry in the queue.
    template <class T>
    T array_queue<T>::front() const
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot get front entry: \
                        queue is empty.");
        }
        return *(base_impl::m_data[m_front]);
    }

    // Get the last entry in the queue.
    template <class T>
    T array_queue<T>::back() const
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot get back entry: queue is empty.");
        }
        return *(base_impl::m_data[m_back]);
    }

    // Add a given entry to the back of the queue.
    template <class T>
    void array_queue<T>::enqueue(const T &entry)
    {
        ensure_capacity();
        m_back = increase_index(m_back, 1);
        base_impl::m_data[m_back] = entry_ptr(new T(entry));
        base_impl::m_size++;
    }

    // Remove and return the first (oldest) entry in the queue.
    template <class T>
    T array_queue<T>::dequeue()
    {
        if (0 == base_impl::m_size)
        {
            throw empty_container("Cannot get back entry: \
                        queue is empty.");
        }
        T front_entry = std::move(*base_impl::m_data[m_front]);
        m_front = increase_index(m_front, 1);
        base_impl::m_size--;
        return front_entry;
    }

    // Remove all the entries from the queue, and free the memory.
    template <class T>
    void array_queue<T>::clear()
    {
        base_container<T>::clear();
        base_impl::m_capacity = base_impl::m_base_capacity;
        base_impl::m_data = data_ptr(new entry_ptr[base_impl::m_capacity + 1]);
        m_front = 0;
        m_back = base_impl::m_capacity;
    }

    // Return if the queue contains a given entry.
    template <class T>
    bool array_queue<T>::contains(const T &entry) const
    {
        if (0 == base_impl::m_size)
        {
            return false;
        }
        for (size_t i = m_front;
            i != m_back;
            i = increase_index(i, 1))
        {
            if (entry == *base_impl::m_data[i])
            {
                return true;
            }
        }
        return false;
    }
}

#endif