#ifndef DYNAMIC_ARRAY_CONTAINER_H
#define DYNAMIC_ARRAY_CONTAINER_H

#include <cmath>
#include <memory>
#include <algorithm>
#include "dsa_exception.h"
#include "adt_sequence_container.h"

#ifndef DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY
#define DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY 10
#endif
#ifndef DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR
#define DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR 1.5
#endif

namespace DSA
{
    template <class T>
    class dynamic_array_container
        : virtual public adt_sequence_container<T>
    {
        typedef std::size_t size_t;
        typedef std::ptrdiff_t ptrdiff_t;
        //typedef std::unique_ptr<T[]> data_ptr;
        typedef T* data_ptr;
    public:
        class iterator;

        // Construct a dynamic array container with default
        // base capacity (10) and growth factor (1.5).
        dynamic_array_container();

        virtual ~dynamic_array_container();

        // Return if the container is empty.
        // A container is empty when it does not contain any entry.
        inline bool empty() const;

        // Get the number of entries in the container.
        inline virtual size_t size() const;

        // Get the capacity of the container.
        // Node that capacity represents how many item the container
        // can hold, not how many item it has.
        inline size_t capacity() const;

        // Remove all the entries from the container, and free the memory.
        inline virtual void clear();

        // Allocate memory for a given amount of entries.
        inline virtual void reserve(const size_t& capacity);
        
        // Free unused memory occupied by the array.
        inline virtual void shrink();

        // Insert a given entry to the front of the container.
        // Same as insert_entry(0, entry);
        inline virtual void push_front(const T& entry);
        inline virtual void push_front(T&& entry);

        // Insert a given entry to the back of the container.
        // Same as insert_entry(m_size, entry);
        inline virtual void push_back(const T& entry);
        inline virtual void push_back(T&& entry);

        // Insert a given entry to a given place in the container.
        inline virtual void insert(const size_t& index, const T& entry);

        // Remove and return the object at the front of the container.
        inline virtual T pop_front();

        // Remove and return the object at the end of the container.
        inline virtual T pop_back();

        // Remove a given entry from the container.
        // Note that only one entry will be removed if there are duplicates.
        // Throw no_such_element exception if the entry is not found.
        inline virtual void remove(const T& entry);

        // Remove the entry at a given index.
        // Throw index_error exception when index out of bounds.
        inline virtual void remove(const size_t& index);

        // Return the entry at a given position in the container.
        // Throw index_error exception when index out of bounds.
        inline virtual T at(const size_t& index) const;

        // Get the index of a given entry.
        // Throw no_such_element exception when the given entry is not found.
        inline virtual size_t index_of(const T& entry) const;

        // Return if the container contains a given entry.
        inline virtual bool contains(const T& entry) const;

        // Return an iterator pointing to the beginning of the container.
        inline virtual iterator begin();

        // Return an iterator pointing to the end of the container.
        inline virtual iterator end();

        // Return an array that contains all the entries in the container.
        inline virtual T *to_array() const;

    protected:
        // Natural log 2, used in function capacity_of(const size_t &)
        float GROWTH_FACTOR_LOG = log(DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR);

        data_ptr m_data;
        size_t m_size;
        size_t m_capacity;
    
        // Helper function to determine the capacity needed to hold a
        // given size of list.
        inline size_t capacity_of(const size_t& size) const;

        // Expand the array when the container is full.
        virtual inline void ensure_capacity();

        // Shift all entries after a given index left one position.
        virtual inline void shift_left(const size_t& index);

        // Shift all entries after a given index right one position.
        virtual inline void shift_right(const size_t& index);
    };

    template <class T>
    class dynamic_array_container<T>::iterator
        : public std::iterator<std::random_access_iterator_tag, T>
    {
    public:
        iterator(dynamic_array_container<T>& container);
        iterator(const iterator& iter);
        ~iterator();
        iterator& operator=(const iterator& rhs);
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        bool operator<(const iterator& rhs) const;
        bool operator>(const iterator& rhs) const;
        bool operator<=(const iterator& rhs) const;
        bool operator>=(const iterator& rhs) const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+=(size_t size);
        iterator operator+(size_t size) const;
        iterator& operator-=(size_t size);
        iterator operator-(size_t size) const;
        T& operator*() const;
        T* operator->() const;
        T& operator[](size_t index) const;
    private:
        T* m_iter;
        dynamic_array_container<T>& m_container;
    };
}

#include "dynamic_array_container_impl.h"

#undef DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY
#undef DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR

#endif
