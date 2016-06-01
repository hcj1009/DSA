#ifndef DYNAMIC_ARRAY_CONTAINER_H
#define DYNAMIC_ARRAY_CONTAINER_H

#include <cmath>
#include <memory>
#include <algorithm>
#include "dsa_except.h"
#include "adt_sequence_container.h"

namespace DSA
{
    template <class T>
    class dynamic_array_container
        : virtual public adt_sequence_container<T>
    {
        typedef std::ptrdiff_t ptrdiff_t;
        typedef std::shared_ptr<T> entry_ptr;
        typedef std::unique_ptr<entry_ptr[]> data_ptr;
    protected:
        // Natural log 2, used in function capacity_of(const size_t &)
        static const size_t DEFAULT_BASE_CAPACITY = 10;
        static const float DEFAULT_GROWTH_FACTOR = 1.5;

        data_ptr m_data;
        size_t m_size;
        size_t m_capacity;
        
        // Do not allow user specified base capacity and growth factor.
#ifdef DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG
        size_t m_base_capacity;
#endif
#ifdef DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG
        float m_growth_factor;
#endif
        inline virtual float quick_log(const float &a)
        {
            // Return pre-calculated natural log 2 if input is 
            // EFAULT_GROWTH_FACTOR.
            // Node: change this when changing DEFAULT_GROWTH_FACTOR;
            return DEFAULT_BASE_CAPACITY == a ? 0.4054651081081644f : log(a);
        }

        // Helper function to determine the capacity needed to hold a
        // given size of list.
        inline virtual size_t capacity_of(const size_t &size) const;

        // Helper function to enlarge the capacity when the container is full.
        inline virtual void ensure_capacity();

        // Helper function to shift a range of entries starting at a
        // given index with a given displacement.
        inline virtual void shift(const size_t &index, const ptrdiff_t &disp);

    public:
        // Construct a dynamic array container with default
        // base capacity (10) and growth factor (1.5).

#if defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG) \
    && defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG)
        dynamic_array_container(const size_t &base_capacity 
            = DEFAULT_BASE_CAPACITY,
            const float &growth_factor 
            = DEFAULT_GROWTH_FACTOR);
#elif defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG)
        dynamic_array_container(const size_t &base_capacity
            = DEFAULT_BASE_CAPACITY);
#elif defined(DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG)
        dynamic_array_container(const float &growth_factor
            = DEFAULT_GROWTH_FACTOR);
#else
        dynamic_array_container();
#endif

        virtual ~dynamic_array_container();

#ifdef DYNAMIC_ARRAY_CONTAINER_CUSTOM_BASE_CAPACITY_FLAG
        inline virtual size_t base_capacity() const;
        inline virtual void set_base_capacity(const size_t &base_capacity);
#endif
#ifdef DYNAMIC_ARRAY_CONTAINER_CUSTOM_GROWTH_FACTOR_FLAG
        inline virtual size_t growth_factor() const;
        inline virtual void set_growth_facotr(const size_t &growth_factor);
#endif
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

        inline virtual T *to_array() const;
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
    };
}

#include "dynamic_array_container_impl.h"

#endif
