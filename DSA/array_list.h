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
            = base_impl::DEFAULT_BASE_CAPACITY);
        // Builda list based on a given list.
        array_list(const array_list<T> &list);
        // Move constructor: build a list based on a given list (rvalue).
        array_list(array_list<T> &&list) noexcept;
        // Build a list based on a given array of entries.
        array_list(const T entries[],
            const size_t &size,
            const size_t &base_capacity
            = base_impl::DEFAULT_BASE_CAPACITY);
        // Default destructor fo the list.
        virtual ~array_list();
        virtual bool empty() const;
        virtual size_t size() const;
        virtual size_t capacity() const;
        virtual void clear();
        virtual void add(const T &entry);
        virtual void add(const size_t &index, const T &entry);
        virtual void add(const T entries[], const size_t &size);
        virtual void add(const size_t &index,
            const T entries[], 
            const size_t &size);
        virtual void add(const array_list<T> &list);
        virtual void add(const size_t &index, const array_list<T> &list);
        virtual void add(array_list<T> &&list);
        virtual void add(const size_t &index, array_list<T> &&list);
        // Remove the entry at a given index from the list.
        virtual T remove(const size_t &index);
        // Remove a given entry from the list.
        virtual void remove(const T &entry);
        // Get the entry at a given index.
        virtual T get(const size_t &index) const;
        // Set the value of the entry at a given index to a given entry.
        // Throw index_error exception.
        virtual void set(const size_t &index, const T &entry);
        virtual size_t index_of(const T &entry) const;
        // Return if the list contains a given entry.
        virtual bool contains(const T &entry) const;
        // Get the pointer pointing to an array that represents the list.
        virtual T *to_array() const;
        // Override assignment expression.
        virtual array_list &operator=(const array_list<T> &rhs);
        // Cases when the right-hand expression is rvalue.
        virtual array_list<T> &operator= (array_list<T> &&rhs);
        array_list<T> &operator+= (const T &rhs);
    };
}

#include "array_list_impl.h"
#endif
