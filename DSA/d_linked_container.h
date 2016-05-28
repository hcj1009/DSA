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
        d_node<T> *cur_node;
        if (index <= (float)m_size / 2)
        {
            cur_node = m_head;
            for (size_t i = 0; i < index; i++)
            {
                cur_node = cur_node->next();
            }
        }
        // When index is on the right side of the linked chain.
        else
        {
            cur_node = m_tail;
            for (size_t i = 0; i < m_size - index - 1; i++)
            {
                cur_node = cur_node->prev();
            }
        }
        return cur_node;
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

    void insert_front(const T &entry)
    {
        d_node<T> *new_node = new d_node<T>(entry);
        if (m_head)
        {
            m_head->set_prev(new_node);
        }
        // If m_head is nullptr, then m_tail must be nullptr,
        // container must be empty.
        else
        {
            m_tail = new_node;
        }
        new_node->set_next(m_head);     // new_node->prev == nullptr
        m_head = new_node;
        m_size++;
    }

    void insert_back(const T &entry)
    {
        d_node<T> *new_node = new d_node<T>(entry);
        new_node->set_prev(m_tail);
        m_tail->set_next(new_node);
        m_tail = new_node;
        m_size++;
    }

    void insert_entry(const size_t &index, const T &entry)
    {
        // Insert entry to the front.
        if (0 == index)
        {
            insert_front(entry);
        }
        // Insert entry to the back. (m_size must not equal to 0)
        else if (m_size == index)
        {
            insert_back(entry);
        }
        // General cases.
        else
        {
            d_node<T> *new_node = new d_node<T>(entry);
            d_node<T> &old_node = node_at(index);
            new_node->set_prev(old_node.prev());
            new_node->set_next(old_node);
            if (!new_node->prev())
            {
                new_node->prev()->set_next(new_node);
            }
            old_node.set_prev(new_node);
            m_size++;
        }
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

    // TODO Optimize this:
    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    virtual size_t index_of(const T &entry) const
    {
        d_node<T> *forward_node = m_head;
        d_node<T> *backward_node = m_tail;

        for (int i = 0; i < m_size / 2; i++)
        {
            if (entry == forward_node->data())
            {
                return i;
            }
            if (entry == backward_node->data())
            {
                return m_size - index - 1;
            }
            index++;
            forward_node = forward_node->next();
            backward_node = backward_node->prev();
        }

        throw no_such_element("Cannot get the index of an entry that \
is not in the list.");
    }


    virtual bool contains(const T &entry) const
    {
        try
        {
            index_of(entry);
        }
        catch (no_such_element exception)
        {
            return false;
        }
        return true;
    }
};

#endif