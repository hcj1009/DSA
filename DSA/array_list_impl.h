#ifndef ARRAY_LIST_IMPL_H
#define ARRAY_LIST_IMPL_H

namespace DSA
{
    // Default constructor of the list.
    template <class T>
    array_list<T>::array_list(const size_t &base_capacity
        = base_impl::DEFAULT_BASE_CAPACITY)
        : dynamic_array_container<T>(base_capacity) {}

    // Builda list based on a given list.
    template <class T>
    array_list<T>::array_list(const array_list<T> &list)
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
    template <class T>
    array_list<T>::array_list(array_list<T> &&list) noexcept
    {
        base_impl::m_base_capacity =
            std::move(list.base_impl::m_base_capacity);
        base_impl::m_capacity = std::move(list.base_impl::m_capacity);
        base_impl::m_size = std::move(list.base_impl::m_size);
        base_impl::m_data = std::move(list.base_impl::m_data);
    }

    // Build a list based on a given array of entries.
    template <class T>
    array_list<T>::array_list(const T entries[],
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
    template <class T>
    virtual array_list<T>::~array_list() {}

    // Return if the container is empty.
    template <class T>
    virtual bool array_list<T>::empty() const
    {
        return base_impl::empty();
    }

    // Get the size of the list.
    template <class T>
    virtual size_t array_list<T>::size() const
    {
        return base_impl::size();
    }

    // Get the capacity of the list;
    template <class T>
    virtual size_t array_list<T>::capacity() const
    {
        return base_impl::capacity();
    }

    // Remove all the entries from the list, and free the memory.
    template <class T>
    virtual void array_list<T>::clear()
    {
        base_impl::clear();
    }

    // Add a given entry to the container.
    template <class T>
    virtual void array_list<T>::add(const T &entry)
    {
        base_impl::shift(base_impl::m_size, 1);
        base_impl::m_data[base_impl::m_size - 1] =
            entry_ptr(new T(entry));
    }

    // Add a given entry to a given index of the list.
    template <class T>
    virtual void array_list<T>::add(const size_t &index, const T &entry)
    {
        if (index > base_impl::m_size)
        {
            throw index_error("Index out of bounds.");
        }
        base_impl::shift(index, 1);
        base_impl::m_data[index] = entry_ptr(new T(entry));
    }

    template <class T>
    virtual void array_list<T>::add(const T entries[], const size_t &size)
    {
        base_impl::shift(base_impl::m_size, size);
        for (size_t i = 0; i < base_impl::m_size; i++)
        {
            base_impl::m_data[base_impl::m_size + i] =
                entry_ptr(new T(entries[i]));
        }
    }

    template <class T>
    virtual void array_list<T>::add(const size_t &index,
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

    template <class T>
    virtual void array_list<T>::add(const array_list<T> &list)
    {
        base_impl::shift(base_impl::m_size, list.base_impl::m_size);
        for (size_t i = 0; i < base_impl::m_size; i++)
        {
            base_impl::m_data[base_impl::m_size + i] =
                list.base_impl::m_data[i];
        }
    }

    template <class T>
    virtual void array_list<T>::add(const size_t &index,
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

    template <class T>
    virtual void array_list<T>::add(array_list<T> &&list)
    {
        base_impl::shift(base_impl::m_size, list.base_impl::m_size);
        for (size_t i = 0; i < list.m_size; i++)
        {
            base_impl::m_data[base_impl::m_size + i] =
                std::move(list.base_impl::m_data[i]);
        }
    }

    template <class T>
    virtual void array_list<T>::add(const size_t &index,
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

    // Remove the entry at a given index from the list.
    template <class T>
    virtual T array_list<T>::remove(const size_t &index)
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
    template <class T>
    virtual void array_list<T>::remove(const T &entry)
    {
        size_t index = index_of(entry);
        remove(index);
    }

    // Get the entry at a given index.
    template <class T>
    virtual T array_list<T>::get(const size_t &index) const
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
    template <class T>
    virtual void array_list<T>::set(const size_t &index, const T &entry)
    {
        if (index >= base_impl::m_size)
        {
            throw index_error("Index out of bounds.");
        }
        base_impl::m_data[index].reset(new T(entry));
    }

    template <class T>
    virtual size_t array_list<T>::index_of(const T &entry) const
    {
        return base_impl::index_of(entry);
    }

    // Return if the list contains a given entry.
    template <class T>
    virtual bool array_list<T>::contains(const T &entry) const
    {
        return base_impl::contains(entry);
    }

    // Get the pointer pointing to an array that represents the list.
    template <class T>
    virtual T *array_list<T>::to_array() const
    {
        return new T[base_impl::m_size];
    }

    // Override assignment expression.
    template <class T>
    virtual array_list<T> &
        array_list<T>::operator=(const array_list<T> &rhs)
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
    template <class T>
    array_list<T> &array_list<T>::operator= (array_list<T> &&rhs)
    {
        base_impl::m_base_capacity =
            std::move(rhs.base_impl::m_base_capacity);
        base_impl::m_capacity = std::move(rhs.base_impl::m_capacity);
        base_impl::m_size = std::move(rhs.base_impl::m_size);
        base_impl::m_data = std::move(rhs.base_impl::m_data);
        return *this;
    }

    template <class T>
    array_list<T> &array_list<T>::operator+= (const T &rhs)
    {
        add(rhs);
        return *this;
    }

    /*
    template <class T>
    friend array_list<T> operator+
    (const array_list<T> &lhs, const T &rhs)
    {
    array_list<T> new_list(lhs);
    new_list.add(rhs);
    return new_list;
    }
    */
}

#endif