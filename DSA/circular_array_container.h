#ifndef CIRCULAR_ARRAY_CONTAINER_H
#define CIRCULAR_ARRAY_CONTAINER_H

#include <cmath>
#include "dsa_exception.h"
#include "adt_sequence_container.h"

#ifndef CIRCULAR_ARRAY_CONTAINER_BASE_CAPACI
#define CIRCULAR_ARRAY_CONTAINER_BASE_CAPACITY 10
#endif
#ifndef CIRCULAR_ARRAY_CONTAINER_GROWTH_FACTOR
#define CIRCULAR_ARRAY_CONTAINER_GROWTH_FACTOR 1.5
#endif

namespace DSA
{
    template <class T>
    class circular_array_container
        : virtual public adt_sequence_container<T>
    {
        typedef std::size_t size_t;
        typedef std::ptrdiff_t ptrdiff_t;
        typedef T* data_ptr;
    public:
        class iterator;

        circular_array_container();

        virtual ~circular_array_container();

        // Return if the container is empty.
        // A container is empty when it does not contain any entry.
        inline virtual bool empty() const;

        // Get the number of entries in the container.
        inline virtual size_t size() const;

        // Get the capacity of the container.
        // Node that capacity represents how many item the container
        // can hold, not how many item it has.
        inline virtual size_t capacity() const;

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
		inline virtual void insert(const size_t& index, T&& entry);

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

        /**
        // Return an iterator pointing to the beginning of the container.
        inline virtual iterator begin();

        // Return an iterator pointing to the end of the container.
        inline virtual iterator end();
        /**/

        // Return an array that contains all the entries in the container.
        inline virtual T* to_array() const;

    protected:
        float GROWTH_FACTOR_LOG = log(CIRCULAR_ARRAY_CONTAINER_GROWTH_FACTOR);

        data_ptr m_data;
        size_t m_front;
        size_t m_back;
        size_t m_size;
        size_t m_capacity;

        // Increase the index by a given increment (return a copy).
        inline size_t index_inc(const size_t& index,
                const size_t& inc = 1) const;

        // Increase the index by a given increment (self increment).
        inline size_t index_self_inc(size_t& index,
                const size_t& inc = 1);

        // Decrease the index by a given decrement (return a copy);
        inline size_t index_dec(const size_t& index,
                const size_t& dec = 1) const;

        // Decrease the index by a given decrement (self decrement).
        inline size_t index_self_dec(size_t& index,
                const size_t& dec = 1);

        inline bool index_gt(const size_t& index1, const size_t& index2);

        // Return the distance between two indexes.
        inline size_t distance(const size_t& index1, const size_t& index2);

        inline size_t capacity_of(const size_t& size) const noexcept;
        inline virtual void ensure_capacity();
        inline virtual void ensure_capacity(const size_t& size);
        inline virtual void shift_left(const size_t& index, 
                const size_t& dis = 1);
        inline virtual void shift_right(const size_t& index,
                const size_t& dis = 1);
    };

    /**/
    template <class T>
    class circular_array_container<T>::iterator
        : public std::iterator<std::random_access_iterator_tag, T>
    {
    public:
        iterator(circular_array_container<T>& container);
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
        T* m_ptr;
        circular_array_container<T>& m_container;
    };
    /**/
}

#include "circular_array_container_impl.h"

#endif
