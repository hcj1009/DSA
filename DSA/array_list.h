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
        typedef dynamic_array_container<T> base_impl;
        typedef std::shared_ptr<T> entry_ptr;
        typedef std::unique_ptr<std::shared_ptr<T>[]> data_ptr;
    public:
        // Default constructor of the list.
        array_list(const size_t &base_capacity 
                = base_impl::DEFAULT_BASE_CAPACITY)
            : dynamic_array_container<T>(base_capacity) {}

        // Builda list based on a given list.
        array_list(const array_list<T> &list)
        {
            base_impl::m_base_capacity = list.base_impl::m_base_capacity;
            base_impl::m_capacity = list.base_impl::m_capacity;
            base_impl::m_size = list.base_impl::m_size;
            base_impl::m_data = 
                data_ptr(new entry_ptr[base_impl::m_capacity]);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[i] = 
                    std::shared_ptr<T>(list.base_impl::m_data[i]);
            }
        }

        // Move constructor: build a list based on a given list (rvalue).
        array_list(array_list<T> &&list) noexcept
        {
            base_impl::m_base_capacity =
                std::move(list.base_impl::m_base_capacity);
            base_impl::m_capacity = std::move(list.base_impl::m_capacity);
            base_impl::m_size = std::move(list.base_impl::m_size);
            base_impl::m_data = std::move(list.base_impl::m_data);
        }

        // Build a list based on a given array of entries.
        array_list(const T entries[],
            const size_t &size,
            const size_t &base_capacity
            = base_impl::DEFAULT_BASE_CAPACITY)
        {
            base_impl::m_base_capacity = base_capacity;
            base_impl::m_capacity = base_impl::capacity_of(size);
            base_impl::m_size = size;
            base_impl::m_data = 
                data_ptr(new entry_ptr[base_impl::m_capacity]);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[i].reset(new T(entries[i]));
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
            base_impl::shift(base_impl::m_size, 1);
            base_impl::m_data[base_impl::m_size - 1] = 
                entry_ptr(new T(entry));
        }

        /*/
        /**
        virtual void add(T &&entry)
        {
            base_impl::shift(m_size, 1);
            base_impl::m_data[m_size - 1].reset(&std::move(entry));
        }
        /**/

        // Add a given entry to a given index of the list.
        virtual void add(const size_t &index, const T &entry)
        {
            if (index > base_impl::m_size)
            {
                throw index_error("Index out of bounds.");
            }
            base_impl::shift(index, 1);
            base_impl::m_data[index] = entry_ptr(new T(entry));
        }

        /**/
        virtual void add(const T entries[], const size_t &size)
        {
            base_impl::shift(base_impl::m_size, size);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[base_impl::m_size + i] = 
                    entry_ptr(new T(entries[i]));
            }
        }

        virtual void add(const size_t &index,
            const T entries[],
            const size_t &size)
        {
            if (index > base_impl::m_size)
            {
                throw index_error("Index out of bounds.");
            }
            base_impl::shift(index, size);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[index + i] = entry_ptr(new T(entries[i]));
            }
        }

        virtual void add(const array_list<T> &list)
        {
            base_impl::shift(base_impl::m_size, list.base_impl::m_size);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[base_impl::m_size + i] =
                    list.base_impl::m_data[i];
            }
        }

        virtual void add(const size_t &index,
            const array_list<T> &list)
        {
            if (index > base_impl::m_size)
            {
                throw index_error("Index out of bounds.");
            }
            base_impl::shift(index, list.base_impl::m_size);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[index + i] = list.base_impl::m_data[i];
            }
        }

        virtual void add(array_list<T> &&list)
        {
            base_impl::shift(base_impl::m_size, list.base_impl::m_size);
            for (size_t i = 0; i < list.m_size; i++)
            {
                base_impl::m_data[base_impl::m_size + i] =
                    std::move(list.base_impl::m_data[i]);
            }
        }

        virtual void add(const size_t &index,
            array_list<T> &&list)
        {
            if (index > base_impl::m_size)
            {
                throw index_error("Index out of bounds.");
            }
            base_impl::shift(index, list.base_impl::m_size);
            for (size_t i = 0; i < list.base_impl::m_size; i++)
            {
                base_impl::m_data[index + i] =
                    std::move(list.base_impl::m_data[i]);
            }
        }

        /**/

        // Remove the entry at a given index from the list.
        virtual T remove(const size_t &index)
        {
            if (index >= base_impl::m_size)
            {
                throw index_error("Index out of bounds.");
            }
            T cur_entry = std::move(*base_impl::m_data[index]);
            base_impl::shift(index + 1, -1);
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
            if (index >= base_impl::m_size)
            {
                throw index_error("Index out of bounds.");
            }
            T cur_entry = *(base_impl::m_data[index]);
            return cur_entry;
        }

        // Set the value of the entry at a given index to a given entry.
        // Throw index_error exception.
        virtual void set(const size_t &index, const T &entry)
        {
            if (index >= base_impl::m_size)
            {
                throw index_error("Index out of bounds.");
            }
            base_impl::m_data[index].reset(new T(entry));
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
            return new T[base_impl::m_size];
        }

        // Override assignment expression.
        virtual array_list
            &operator=(const array_list<T> &rhs)
        {
            if (rhs.base_impl::m_capacity != base_impl::m_capacity)
            {
                base_impl::m_data.reset(new entry_ptr[base_impl::m_capacity 
                        = rhs.base_impl::m_capacity]);
            }
            base_impl::m_base_capacity = rhs.base_impl::m_base_capacity;
            base_impl::m_size = rhs.base_impl::m_size;
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[i] =
                    std::shared_ptr<T>(rhs.base_impl::m_data[i]);
            }
            return *this;
        }

        // Cases when the right-hand expression is rvalue.
        virtual array_list<T> &operator=
            (array_list<T> &&rhs)
        {
            base_impl::m_base_capacity =
                std::move(rhs.base_impl::m_base_capacity);
            base_impl::m_capacity = std::move(rhs.base_impl::m_capacity);
            base_impl::m_size = std::move(rhs.base_impl::m_size);
            base_impl::m_data = std::move(rhs.base_impl::m_data);
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
