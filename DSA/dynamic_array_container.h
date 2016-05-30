#ifndef DYNAMIC_ARRAY_CONTAINER_H
#define DYNAMIC_ARRAY_CONTAINER_H

#include <cmath>
#include <memory>
#include <algorithm>
#include "dsa_except.h"
#include "base_container.h"

namespace DSA
{
    template <class T>
    class dynamic_array_container
        : virtual public base_container<T>
    {
        typedef std::ptrdiff_t ptrdiff_t;
        typedef std::shared_ptr<T> entry_ptr;
        typedef std::unique_ptr<entry_ptr[]> data_ptr;
    protected:
        // Natural log 2, used in function capacity_of(const size_t &)
        const double LOG2 = 0.6931471805599453;
        static const size_t DEFAULT_BASE_CAPACITY = 10;

        data_ptr m_data;
        size_t m_capacity;
        size_t m_base_capacity;

        // Helper function to determine the capacity needed to hold a
        // given size of list.
        inline size_t capacity_of(const size_t &size) const;

        // Helper function to enlarge the capacity when the container is full.
        inline void ensure_capacity();

        // Get the index of a given entry.
        // Throw no_such_element exception when the given entry is not found.
        inline size_t index_of(const T &entry) const;

        // Helper function to shift a range of entries starting at a
        // given index with a given displacement.
        inline void shift(const size_t &index, const ptrdiff_t &disp);

    public:
        dynamic_array_container
        (const size_t &base_capacity = DEFAULT_BASE_CAPACITY);

        virtual ~dynamic_array_container();

        inline virtual size_t capacity() const;

        inline virtual void clear();

        // Return if the container contains a given entry.
        inline virtual bool contains(const T &entry) const;
    };
}

#include "dynamic_array_container_impl.h"

#endif
