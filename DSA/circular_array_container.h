#ifndef CIRCULAR_ARRAY_CONTAINER_H
#define CIRCULAR_ARRAY_CONTAINER_H

#include "dsa_exception.h"
#include "adt_sequence_container.h"

namespace DSA
{
    template <class T>
    class circular_array_container
        : virtual public adt_sequence_container<T>
    {
    public:
        class iterator;
    protected:
    };

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
        iterator& operator+=(size_type size);
        iterator operator+(size_type size) const;
        iterator& operator-=(size_type size);
        iterator operator-(size_type size) const;
        T& operator*() const;
        T* operator->() const;
        T& operator[](size_type index) const;
    private:
        T* m_iter;
        circular_array_container<T>& m_container;
    };
}

#include "circular_array_container_impl.h"

#endif