#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include "adt_queue.h"
#include "dynamic_array_container.h"

namespace DSA
{
    // Circular array based implementation of FIFO Queue.
    template <class T>
    class array_queue
        : public adt_queue<T>
        , public dynamic_array_container<T>
    {
    protected:
        size_t m_front;
        size_t m_back;

        size_t increase_index(const size_t &index,
            const size_t &increment) const
        {
            return (index + increment) % (m_capacity + 1);
        }

        // Helper function to double the capacity of the queue when it is full.
        inline void ensure_capacity()
        {
            // When the circular array is full
            if (increase_index(m_back, 2) == m_front)
            {
                size_t new_capacity = 2 * m_capacity;
                data_t new_data = data_t(new std::shared_ptr<T>[new_capacity]);
                for (size_t i = 0; i < m_size; i++)
                {
                    new_data[i] = m_data[increase_index(m_front, i)];
                }
                m_data = std::move(new_data);
                m_front = 0;
                m_back = m_size - 1;
                m_capacity = new_capacity;
            }
        }

    public:
        // Default constructor.
        array_queue
        (const size_t &base_capacity = DEFAULT_BASE_CAPACITY)
        {
            m_base_capacity = base_capacity;
            m_capacity = m_base_capacity;
            m_front = 0;
            m_back = m_capacity;
            m_data = data_t(new std::shared_ptr<T>[m_capacity + 1]);
        }

        array_queue(const array_queue<T> &queue)
        {
            m_base_capacity = queue.m_base_capacity;
            m_capacity = queue.m_capacity;
            m_size = queue.m_size;
            m_front = queue.m_front;
            m_back = queue.m_back;
            m_data = data_t(new std::shared_ptr<T>[m_capacity]);
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[i] = std::shared_ptr<T>(queue.m_data[i]);
            }
        }

        array_queue(array_queue<T> &&queue) noexcept
        {
            
            m_base_capacity = std::move(queue.m_base_capacity);
            m_capacity = std::move(queue.m_base_capacity);
            m_size = std::move(queue.m_size);
            m_front = std::move(queue.m_front);
            m_back = std::move(queue.m_back);
            m_data = std::move(queue.m_data);
        }

        // Default destructor.
        virtual ~array_queue() { }

        // Return if the queue is empty.
        virtual bool empty() const
        {
            return dynamic_array_container<T>::empty();
        }

        // Get the size of the queue.
        virtual size_t size() const
        {
            return dynamic_array_container<T>::size();
        }

        // Get the capacity of the queue.
        virtual size_t capacity() const
        {
            return dynamic_array_container<T>::capacity();
        }

        // Get the first entry in the queue.
        virtual T front() const
        {
            if (0 == m_size)
            {
                throw empty_container("Cannot get front entry: queue is empty.");
            }
            return *(m_data[m_front]);
        }

        // Get the last entry in the queue.
        virtual T back() const
        {
            if (0 == m_size)
            {
                throw empty_container("Cannot get back entry: queue is empty.");
            }
            return *(m_data[m_back]);
        }

        // Add a given entry to the back of the queue.
        virtual void enqueue(const T &entry)
        {
            ensure_capacity();
            m_back = increase_index(m_back, 1);
            m_data[m_back].reset(new T(entry));
            m_size++;
        }

        // Remove and return the first (oldest) entry in the queue.
        virtual T dequeue()
        {
            if (0 == m_size)
            {
                throw empty_container("Cannot get back entry: \
queue is empty.");
            }
            T front_entry = std::move(*m_data[m_front]);
            m_front = increase_index(m_front, 1);
            m_size--;
            return front_entry;
        }

        // Remove all the entries from the queue, and free the memory.
        virtual void clear()
        {
            base_container<T>::clear();
            m_capacity = m_base_capacity;
            m_data = data_t(new std::shared_ptr<T>[m_capacity + 1]);
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
                if (entry == *m_data[i])
                {
                    return true;
                }
            }
            return false;
        }
    };
}

#endif