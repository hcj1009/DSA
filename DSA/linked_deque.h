#ifndef LINKED_DEQUE_H
#define LINKED_DEQUE_H

#include "adt_deque.h"
#include "d_linked_container.h"

namespace DSA
{
    template <class T>
    class linked_deque : public d_linked_container<T>
    {
        typedef d_linked_container<T> base_impl;
        typedef std::shared_ptr<d_node<T>> node_ptr;
    public:
        linked_deque();

        linked_deque(const linked_deque<T> &deque);

        virtual ~linked_deque();

        inline virtual bool empty() const;

        inline virtual size_t size() const;

        inline virtual void clear();

        inline virtual void push_front(const T &entry);

        inline virtual T pop_front();

        inline virtual T front() const;

        inline virtual void push_back(const T &entry);

        inline virtual T pop_back();

        inline virtual T back() const;

        inline virtual bool contains(const T &entry) const;
    };
}

#include "linked_deque_impl.h"

#endif
