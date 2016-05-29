#ifndef LINKED_DEQUE_H
#define LINKED_DEQUE_H

#include "adt_deque.h"
#include "d_linked_container.h"

namespace DSA
{
    template <class T>
    class linked_deque : public d_linked_container<T>
    {
    public:
        linked_deque() : d_linked_container() {}

        linked_deque(const linked_deque<T> &deque)
        {
            m_head = deque.m_head;
            m_tail = deque.m_tail;
            m_size = deque.m_size;
        }

        virtual ~linked_deque() {}

        virtual bool empty() const
        {
            return d_linked_container<T>::empty();
        }

        virtual size_t size() const
        {
            return d_linked_container<T>::size();
        }

        virtual void clear()
        {
            d_linked_container<T>::clear();
        }

        virtual void push_front(const T &entry)
        {
            d_node<T> *new_node(entry);
            insert_front(new_node);
        }

        virtual T pop_front()
        {
            if (0 == m_size)
            {
                throw empty_container("Cannot pop entry from an empty deque.");
            }
            d_node<T> *cur_node = remove(0);
            m_size--;
            return cur_node->data();
        }

        virtual T front() const
        {
            if (0 == m_size)
            {
                throw empty_container("Cannot get entry from an empty deque.");
            }
            return m_head->data();
        }

        virtual void push_back(const T &entry)
        {
            d_node<T> *new_node(entry);
            insert_back(new_node);
        }

        virtual T pop_back()
        {
            if (0 == m_size)
            {
                throw empty_container("Cannot pop entry from an empty deque.");
            }
            return T();
            // return remove(--m_size)->data();
        }

        virtual T back() const
        {
            if (0 == m_size)
            {
                throw empty_container("Cannot get entry from an empty deque.");
            }
            return T();
            // return m_tail->data();
        }

        virtual bool contains(const T &entry) const
        {
            return d_linked_container<T>::contains(entry);
        }
    };
}

#endif