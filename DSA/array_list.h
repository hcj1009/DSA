#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "dynamic_array_container.h"
#include "adt_list.h"

namespace DSA
{
    // Array-based List implementation.
    template <class T>
    class array_list
        : public adt_list<T>
        , public dynamic_array_container<T>
    {
        typedef std::shared_ptr<T> entry_ptr;
        typedef std::unique_ptr<std::shared_ptr<T>[]> data_ptr;
    public:
        // Default constructor of the list.
        array_list(const size_t &base_capacity = DEFAULT_BASE_CAPACITY)
            : dynamic_array_container(base_capacity) {}

        // Builda list based on a given list.
        array_list(const array_list<T> &list)
        {
            m_base_capacity = list.m_base_capacity;
            m_capacity = list.m_capacity;
            m_size = list.m_size;
            m_data = data_ptr(new entry_ptr[m_capacity]);
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[i] = std::shared_ptr<T>(list.m_data[i]);
            }
        }

        // Move constructor: build a list based on a given list (rvalue).
        array_list(array_list<T> &&list) noexcept
        {
            m_base_capacity = std::move(list.m_base_capacity);
            m_capacity = std::move(list.m_capacity);
            m_size = std::move(list.m_size);
            m_data = std::move(list.m_data);
        }

        // Build a list based on a given array of entries.
        array_list(const T entries[],
            const size_t &size,
            const size_t &base_capacity = DEFAULT_BASE_CAPACITY)
        {
            m_base_capacity = base_capacity;
            m_capacity = capacity_of(size);
            m_size = size;
            m_data = data_ptr(new shared_ptr<T>[m_capacity]);
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[i].reset(new T(entries[i]));
            }
        }

        // Default destructor fo the list.
        virtual ~array_list()
        {}

        // Return if the container is empty.
        virtual bool empty() const
        {
            return dynamic_array_container<T>::empty();
        }

        // Get the size of the list.
        virtual size_t size() const
        {
            return dynamic_array_container<T>::size();
        }

        // Get the capacity of the list;
        virtual size_t capacity() const
        {
            return dynamic_array_container<T>::capacity();
        }

        // Remove all the entries from the list, and free the memory.
        virtual void clear()
        {
            dynamic_array_container<T>::clear();
        }

        // Add a given entry to the container.
        virtual void add(const T &entry)
        {
            shift(m_size, 1);
            m_data[m_size - 1].reset(new T(entry));
        }

        /*/
        /**
        virtual void add(T &&entry)
        {
            shift(m_size, 1);
            m_data[m_size - 1].reset(&std::move(entry));
        }
        /**/

        // Add a given entry to a given index of the list.
        virtual void add(const size_t &index, const T &entry)
        {
            if (index > m_size)
            {
                throw index_error("Index out of bounds.");
            }
            shift(index, 1);
            m_data[index].reset(new T(entry));
        }

        /**/
        virtual void add(const T entries[], const size_t &size)
        {
            shift(m_size, size);
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[m_size + i].reset(new T(entries[i]));
            }
        }

        virtual void add(const size_t &index,
            const T entries[],
            const size_t &size)
        {
            if (index > m_size)
            {
                throw index_error("Index out of bounds.");
            }
            shift(index, size);
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[index + i].reset(new T(entries[i]));
            }
        }

        virtual void add(const array_list<T> &list)
        {
            shift(m_size, list.m_size);
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[m_size + i] = list.m_data[i];
            }
        }

        virtual void add(const size_t &index,
            const array_list<T> &list)
        {
            if (index > m_size)
            {
                throw index_error("Index out of bounds.");
            }
            shift(index, list.m_size);
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[index + i] = list.m_data[i];
            }
        }

        virtual void add(array_list<T> &&list)
        {
            shift(m_size, list.m_size);
            for (size_t i = 0; i < list.m_size; i++)
            {
                m_data[m_size + i] = std::move(list.m_data[i]);
            }
            list.m_size = 0;
        }

        virtual void add(const size_t &index,
            array_list<T> &&list)
        {
            if (index > m_size)
            {
                throw index_error("Index out of bounds.");
            }
            shift(index, list.m_size);
            for (size_t i = 0; i < list.m_size; i++)
            {
                m_data[index + i] = std::move(list.m_data[i]);
            }
            list.m_size = 0;
        }

        /**/

        // Remove the entry at a given index from the list.
        virtual T remove(const size_t &index)
        {
            if (index >= m_size)
            {
                throw index_error("Index out of bounds.");
            }
            T cur_entry = std::move(*m_data[index]);
            shift(index + 1, -1);
            return cur_entry;
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
            T cur_entry = *(m_data[index]);
            return cur_entry;
        }

        // Set the value of the entry at a given index to a given entry.
        // Throw index_error exception.
        virtual void set(const size_t &index, const T &entry)
        {
            if (index >= m_size)
            {
                throw index_error("Index out of bounds.");
            }
            m_data[index].reset(new T(entry));
        }

        virtual size_t index_of(const T &entry) const
        {
            return dynamic_array_container<T>::index_of(entry);
        }

        // Return if the list contains a given entry.
        virtual bool contains(const T &entry) const
        {
            return dynamic_array_container<T>::contains(entry);
        }

        // Get the pointer pointing to an array that represents the list.
        virtual T *to_array() const
        {
            return new T[m_size];
        }

        // Override assignment expression.
        virtual array_list
            &operator=(const array_list<T> &rhs)
        {
            if (rhs.m_capacity != m_capacity)
            {
                m_data.reset(new entry_ptr[m_capacity = rhs.m_capacity]);
            }
            m_base_capacity = rhs.m_base_capacity;
            m_size = rhs.m_size;
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[i] = std::shared_ptr<T>(rhs.m_data[i]);
            }
            return *this;
        }

        // Cases when the right-hand expression is rvalue.
        virtual array_list<T> &operator=
            (array_list<T> &&rhs)
        {
            m_base_capacity = std::move(rhs.m_base_capacity);
            m_capacity = std::move(rhs.m_capacity);
            m_size = std::move(rhs.m_size);
            m_data = std::move(rhs.m_data);
            return *this;
        }

        array_list<T> &operator+=
            (const T &rhs)
        {
            add(rhs);
            return *this;
        }

        friend array_list<T> operator+
            (const array_list<T> &lhs, const T &rhs)
        {
            array_list<T> new_list(lhs);
            new_list.add(rhs);
            return new_list;
        }
    };
}

#endif