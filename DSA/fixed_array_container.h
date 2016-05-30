#ifndef FIXED_ARRAY_CONTAINER_H
#define FIXED_ARRAY_CONTAINER_H

#include "dsa_except.h"
#include "base_container.h"

namespace DSA
{
    template <class T, size_t CAPACITY>
    class fixed_array_container :
        virtual public base_container<T>
    {
        typedef base_container<T> base_impl;
    protected:
        T m_data[CAPACITY];

        inline size_t index_of(const T &entry) const
        {
            for (size_t i = 0; i < base_impl::m_size; i++)
            {
                if (entry == m_data[i])
                {
                    return i;
                }
            }
            throw no_such_element("Cannot find such entry in the container.");
        }

    public:
        fixed_array_container() : base_container<T>()
        {
            memset(m_data, 0, CAPACITY * sizeof(T));
        }

        virtual ~fixed_array_container() {}

        virtual void clear()
        {
            base_container<T>::clear();
            memset(m_data, 0, CAPACITY * sizeof(T));
        }

        virtual size_t capacity() const
        {
            return CAPACITY;
        }

        virtual bool full() const
        {
            return (base_impl::m_size == CAPACITY);
        }

        virtual bool contains(const T &entry) const
        {
            try
            {
                index_of(entry);
            }
            catch (no_such_element e)
            {
                return false;
            }
            return true;
        }
    };
}

#endif
