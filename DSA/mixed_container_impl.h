#ifndef MIXED_CONTAINER_IMPL_H
#define MIXED_CONTAINER_IMPL_H

namespace DSA
{
    template <class T>
    const size_t mixed_container<T>::DEFAULT_BASE_CAPACITY;

    template <class T>
    mixed_container<T>::mixed_container(const size_t &array_capacity)
        : d_linked_container<std::unique_ptr<std::shared_ptr<T>[]>>()
        , m_front(0), m_array_capacity(array_capacity) {}

    template <class T>
    mixed_container<T>::~mixed_container() {}

    template <class T>
    bool mixed_container<T>::empty()
    {
        return base_impl::empty();
    }

    template <class T>
    bool mixed_container<T>::contains(const T &entry)
    {
        // TODO Implement later.
    }
}

#endif