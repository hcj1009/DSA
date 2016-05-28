#ifndef D_LINKED_CONTAINER_H
#define D_LINKED_CONTAINER_H

#include "base_container.h"
#include "d_node.h"

template <class T>
class d_linked_container : public base_container<T>
{
protected:
    d_node<T> *m_head;
    d_node<T> *m_tail;

    d_node<T> *node_at(const size_t &index) const
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds.");
        }
        
        // When index is on the left side of the linked chain.
        if (index <= (float)m_size / 2)
        {
            d_node<T> *cur_node = m_head;
            for (size_t i = 0; i < index; i++)
            {
                cur_node = cur_node->next();
            }
            return cur_node;
        }
        // When index is on the right side of the linked chain.
        else
        {
            d_node<T> *cur_node = m_tail;
            for (size_t i = 0; i < m_size - index - 1; i++)
            {
                cur_node = cur_node->prev();
            }
            return cur_node;
        }
    }

    d_node<T> *node_of(const T &entry) const
    {
        d_node<T> *cur_node = m_head;
        while (cur_node)
        {
            if (entry == cur_node->data())
            {
                return cur_node;
            }
            cur_node = cur_node->next();
        }
        throw no_such_element("Cannot find such entry in the container.");
    }

public:
    d_linked_container() : base_container()
    {
        m_head = nullptr;
        m_tail = nullptr;
    }

    virtual ~d_linked_container()
    {
        delete m_head;
        delete m_tail;
    }

    virtual void clear()
    {
        base_container<T>::clear();
        m_head = nullptr;
        m_tail = nullptr;
    }
};

#endif