#ifndef FIXED_SET_H
#define FIXED_SET_H

#include "adt_set.h"
#include "fixed_array_container.h"

namespace DSA
{
    template <class T, size_t CAPACITY>
    class fixed_set
        : public adt_set<T>
        , public fixed_array_container<T, CAPACITY>
    {
        typedef std::ptrdiff_t ptrdiff_t;
        typedef fixed_array_container<T, CAPACITY> base_impl;
    public:
        fixed_set() : fixed_array_container<T, CAPACITY>() {}

        fixed_set(const fixed_set<T, CAPACITY> &set)
        {
            base_impl::m_size = set.base_impl::m_size;
            memcpy(base_impl::m_data, set.base_impl::m_data, 
                    base_impl::m_size * sizeof(T));
            memset(&(base_impl::m_data[base_impl::m_size]), 0, 
                    (CAPACITY - base_impl::m_size) * sizeof(T));
        }

        fixed_set(fixed_set<T, CAPACITY> &&set) noexcept
        {
            base_impl::m_size = std::move(set.base_impl::m_size);
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                base_impl::m_data[i] = std::move(set.base_impl::m_data[i]);
            }
        }

        virtual ~fixed_set() {}

        virtual bool empty() const
        {
            return fixed_array_container<T, CAPACITY>::empty();
        }

        virtual bool full() const
        {
            return fixed_array_container<T, CAPACITY>::full();
        }

        virtual size_t size() const
        {
            return fixed_array_container<T, CAPACITY>::size();
        }

        virtual void clear()
        {
            fixed_array_container<T, CAPACITY>::clear();
        }

        virtual void add(const T &entry)
        {
            if (full())
            {
                throw full_container("Cannot add to full set.");
            }
            if (contains(entry))
            {
                throw duplicate_element("Entry is already in the set.");
            }
            base_impl::m_data[base_impl::m_size++] = entry;
        }

        virtual void add(T &&entry)
        {
            if (full())
            {
                throw full_container("Cannot add to full set.");
            }
            if (contains(entry))
            {
                throw duplicate_element("Entry is already in the set.");
            }
            base_impl::m_data[base_impl::m_size++] = std::move(entry);
        }

        virtual T remove()
        {
            if (empty())
            {
                throw empty_container("Set is empty.");
            }
            return base_impl::m_data[--base_impl::m_size];
        }

        virtual T *remove(const size_t &num)
        {
            if (0 > (ptrdiff_t)base_impl::m_size - (ptrdiff_t)num)
            {
                throw illegal_argument("");
            }
            if (0 == num)
            {
                return nullptr;
            }

            // TODO Rename this:
            T *cur_data = new T[num];
            size_t new_size = base_impl::m_size - num;
            memcpy(cur_data, &(base_impl::m_data[new_size]), num * sizeof(T));
            memset(&(base_impl::m_data[new_size]), 0, num * sizeof(T));
            base_impl::m_size = new_size;
            return cur_data;
        }

        virtual void remove(const T &entry)
        {
            size_t index = index_of(entry);
            base_impl::m_data[index] = base_impl::m_data[--base_impl::m_size];
        }

        virtual bool contains(const T &entry) const
        {
            return fixed_array_container<T, CAPACITY>::contains(entry);
        }

        fixed_set<T, CAPACITY>
            &operator=(const fixed_set<T, CAPACITY> &rhs)
        {
            return *this;
        }

        fixed_set<T, CAPACITY>
            &operator=(fixed_set<T, CAPACITY> &&rhs)
        {
            return *this;
        }
    };
}

#endif
