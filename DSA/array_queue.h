#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "dsaexcept.h"
#include "adt_queue.h"

// Circular array based implementation of FIFO Queue.
template <class T,
    size_t BASE_CAPACITY = 10>
class array_queue : adt_queue<T>
{
private:
    T *m_data;
    size_t m_size;
    size_t m_capacity;
    size_t m_front;
    size_t m_back;

    size_t increase_index(const size_t &index, 
        const size_t &increment) const
    {
        return (index + increment) % (m_capacity + 1);
    }

    // Helper function to double the capacity of the queue when it is full.
    void ensure_capacity()
    {
        // When the circular array is full
        if (increase_index(m_back, 2) == m_front)
        {
            size_t new_capacity = 2 * m_capacity;
            T *new_data = new T[new_capacity + 1];
            for (size_t i = 0; i < m_size; i++)
            {
                new_data[i] = m_data[increase_index(m_front, i)];
            }
            delete[] m_data;
            m_data = new_data;
            m_front = 0;
            m_back = m_size - 1;
            m_capacity = new_capacity;
        }
    }

public:
    // Default constructor.
    array_queue() : adt_queue()
    {
        m_capacity = BASE_CAPACITY;
        m_data = new T[m_capacity + 1];
        m_size = 0;
        m_front = 0;
        m_back = m_capacity;
    }

    // Default destructor.
    virtual ~array_queue()
    {
        delete[] m_data;
    }

    // Return if the queue is empty.
    virtual bool empty() const
    {
        return (0 == m_size);
    }

    // Get the size of the queue.
    virtual size_t size() const
    {
        return m_size;
    }

    // Get the capacity of the queue.
    virtual size_t capacity() const
    {
        return m_capacity;
    }

    // Get the first entry in the queue.
    virtual T front() const
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot get front entry: queue is empty.");
        }
        return m_data[m_front];
    }

    // Get the last entry in the queue.
    virtual T back() const
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot get back entry: queue is empty.");
        }
        return m_data[m_back];
    }

    // Add a given entry to the queue.
    virtual void add(const T &entry)
    {
        enqueue(entry);
    }

    // Add a given entry to the back of the queue.
    // Alias for add(const T &entry)
    virtual void enqueue(const T &entry)
    {
        ensure_capacity();
        m_back = increase_index(m_back, 1);
        m_data[m_back] = entry;
        m_size++;
    }

    // Remove and return the first (oldest) entry in the queue.
    virtual T dequeue()
    {
        if (0 == m_size)
        {
            throw empty_container("Cannot get back entry: queue is empty.");
        }
        T front_entry = m_data[m_front];
        m_front = increase_index(m_front, 1);
        m_size--;
        return front_entry;
    }

    // Remove all the entries from the queue, and free the memory.
    virtual void clear()
    {
        delete[] m_data;
        m_capacity = BASE_CAPACITY;
        m_data = new T[m_capacity + 1];
        m_size = 0;
        m_front = 0;
        m_back = m_capacity;
    }

    // Return if the queue contains a given entry.
    virtual bool contains(const T &entry) const
    {
        if (0 == m_size)
        {
            return false;
        }
        for (size_t i = m_front;
            i != m_back;
            i = increase_index(i, 1))
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