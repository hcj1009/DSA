#ifndef DYNAMIC_ARRAY_CONTAINER_H
#define DYNAMIC_ARRAY_CONTAINER_H

#include <cmath>
#include <memory>
#include <algorithm>
#include "dsa_except.h"
#include "adt_sequence_container.h"

#ifndef DISABLE_INLINE
#define INLINE inline
#endif
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
        typedef std::ptrdiff_t ptrdiff_t;
        typedef std::unique_ptr<T[]> data_ptr;
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
        inline virtual void reserve(const size_t &capacity);

        // Free unused memory occupied by the array.
        inline virtual void shrink();

        // Insert a given entry to the front of the container.
        // Same as insert_entry(0, entry);
        inline virtual void push_front(const T &entry);

        // Insert a given entry to the back of the container.
        // Same as insert_entry(m_size, entry);
        inline virtual void push_back(const T &entry);

        // Insert a given entry to a given place in the container.
        inline virtual void insert(const size_t &index, const T &entry);

        // Remove and return the object at the front of the container.
        inline virtual T pop_front();

        // Remove and return the object at the end of the container.
        inline virtual T pop_back();

        // Remove a given entry from the container.
        // Note that only one entry will be removed if there are duplicates.
        // Throw no_such_element exception if the entry is not found.
        inline virtual void remove(const T &entry);

        // Remove the entry at a given index.
        // Throw index_error exception when index out of bounds.
        inline virtual T remove(const size_t &index);

        // Return the entry at a given position in the container.
        // Throw index_error exception when index out of bounds.
        inline virtual T at(const size_t &index) const;

        // Get the index of a given entry.
        // Throw no_such_element exception when the given entry is not found.
        inline virtual size_t index_of(const T &entry) const;

        // Return if the container contains a given entry.
        inline virtual bool contains(const T &entry) const;

        inline virtual iterator begin();

        inline virtual iterator end();

        inline virtual T *to_array() const;

    protected:
        // Natural log 2, used in function capacity_of(const size_t &)
        float GROWTH_FACTOR_LOG = log(DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR);

        data_ptr m_data;
        size_t m_size;
        size_t m_capacity;
    public:
        // Helper function to determine the capacity needed to hold a
        // given size of list.
        inline size_t capacity_of(const size_t &size) const;

        // Helper function to shift a range of entries starting at a
        // given index with a given displacement.
        virtual void shift(const size_t &index, const ptrdiff_t &disp);
    };

    template <class T>
    class dynamic_array_container<T>::iterator
        : public std::iterator<std::random_access_iterator_tag, T>
    {
        typedef size_t size_type;
        typedef T& reference;
        typedef T* pointer;
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
        iterator& operator+=(size_type size);
        iterator operator+(size_type size) const;
        iterator& operator-=(size_type size);
        iterator operator-(size_type size) const;
        reference operator*() const;
        pointer operator->() const;
        reference operator[](size_type index) const;
    private:
        T* m_iter;
        dynamic_array_container<T>& m_container;
    };

    template <class T>
    struct sequence_container_traits<dynamic_array_container<T>>
    {
    public:
        const static bool is_sequence_container = true;
        const static bool support_push_front = true;
        const static bool support_push_back = true;
        const static bool support_insert = true;
        const static bool support_pop_front = true;
        const static bool support_pop_back = true;
        const static bool support_index_remove = true;
        const static bool support_entry_remove = true;
        const static bool support_index_of = true;
        const static bool support_at = true;
        const static bool support_reserve = true;
        const static bool support_shrink = true;
    };
}

#include "dynamic_array_container_impl.h"

#undef DYNAMIC_ARRAY_CONTAINER_BASE_CAPACITY
#undef DYNAMIC_ARRAY_CONTAINER_GROWTH_FACTOR

#endif
