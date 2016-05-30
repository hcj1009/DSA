#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "adt_queue.h"
#include "s_linked_container.h"

namespace DSA
{
    template <class T>
    class linked_queue 
        : public adt_queue<T>
        , public s_linked_container<T>
    {
        typedef s_linked_container<T> base_impl;
        typedef std::shared_ptr<s_node<T>> node_ptr;
    protected:
        node_ptr m_tail;    // Optimization for enqueue to the back.

    public:
        // Default constructor.
        linked_queue() 
            : s_linked_container<T>()
            , m_tail() {}

        // Copy constructor.
        linked_queue(const linked_queue<T> &queue)
        {
            base_impl::m_head 
                = node_ptr(queue.base_impl::m_head);
            m_tail = node_ptr(queue.m_tail);
            base_impl::m_size = queue.base_impl::m_size;
        }

        // Move constructor.
        linked_queue(linked_queue<T> &&queue) noexcept
        {
            base_impl::m_head = queue.base_impl::m_head;
            m_tail = queue.m_tail;
            base_impl::m_size = queue.base_impl::m_size;
        }

        virtual ~linked_queue() {}

        virtual bool empty() const
        {
            return s_linked_container<T>::empty();
        }

        virtual size_t size() const
        {
            return s_linked_container<T>::size();
        }

        virtual void clear()
        {
            s_linked_container<T>::clear();
        }

        // Add a given entry to the back of the queue.
        virtual void enqueue(const T &entry)
        {
            node_ptr new_node
                = node_ptr(new s_node<T>(entry));
            // Empty list case.
            if (0 == base_impl::m_size)
            {
                base_impl::m_head = new_node;
                m_tail = new_node;
            }
            // Normal cases.
            else
            {
                m_tail->set_next(new_node);
                m_tail = new_node;
            }
            base_impl::m_size++;
        }

        // Get the entry from the front of the queue.
        virtual T dequeue()
        {
            if (0 == base_impl::m_size)
            {
                throw empty_container("Cannot get back entry: \
                        queue is empty.");
            }
            node_ptr front_node = base_impl::m_head;
            base_impl::m_head = front_node->next();
            front_node->set_next(node_ptr());
            base_impl::m_size--;
            return front_node->data();
        }

        virtual T front() const
        {
            if (0 == base_impl::m_size)
            {
                throw empty_container("Cannot get front entry: \
                        queue is empty.");
            }
            return base_impl::m_head->data();
        }

        virtual T back() const
        {
            if (0 == base_impl::m_size)
            {
                throw empty_container("Cannot get back entry: queue is empty.");
            }
            return m_tail->data();
        }

        virtual bool contains(const T &entry) const
        {
            return s_linked_container<T>::contains(entry);
        }
    };
}

#endif
