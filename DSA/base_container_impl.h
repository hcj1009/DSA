#ifndef BASE_CONTAINER_IMPL_H
#define BASE_CONTAINER_IMPL_H

namespace DSA
{
    template <class T>
    base_container<T>::base_container() 
        : adt_container<T>(), m_size(0) {}

    template <class T>
    base_container<T>::~base_container() {}

    template <class T>
    bool base_container<T>::empty() const
    {
        return (0 == m_size);
    }

    template <class T>
    size_t base_container<T>::size() const
    {
        return m_size;
    }

    template <class T>
    void base_container<T>::clear()
    {
        m_size = 0;
    }

    template <class T>
    bool base_container<T>::contains(const T &entry) const
    {
        return false;
    }
}

#endif