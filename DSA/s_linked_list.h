#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "dsaexcept.h"
#include "adt_list.h"
#include "s_node.h"

// List implementation based on singly linked node.
template <class T>
class s_linked_list : adt_list<T>
{
private:
    size_t m_size;
    s_node<T> *m_head;
    s_node<T> *m_tail;    // Optimization for adding to the back.

    // Helper function to get the node at a given index.
    s_node<T> *node_at(const size_t &index) const
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds.");
        }
        s_node<T> *current = m_head;
        for (int i = 0; i < index; i++)
        {
            current = current->next();
        }
        return current;
    }

public:
    // Default constructor of the lsit.
    s_linked_list() : adt_list()
    {
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }
    
    // Build a list based on a given array of entries.
    s_linked_list(const T entries[], const size_t &size)
        : adt_list(entries, size)
    {
        if (0 == size)
        {
            s_linked_list();
        }
        else
        {
            m_head = new s_node<T>(entries[0]);
            s_node<T> *current = m_head;
            s_node<T> *new_node = nullptr;
            for (size_t i = 1; i < size; i++)
            {
                new_node = new s_node<T>(entries[i]);
                current->set_next(new_node);
                current = current->next();
            }
            m_tail = new_node;
            m_size = size;
        }
    }

    // Default destructor of the list.
    virtual ~s_linked_list()
    {
        // delete m_head;
        // delete m_tail;
    }

    // Return if the container is empty.
    virtual bool empty() const
    {
        return (0 == m_size);
    }

    // Get the size of the container.
    virtual size_t size() const
    {
        return m_size;
    }

    // Add a given entry to the container.
    virtual void add(const T &entry)
    {
        s_node<T> *new_node = new s_node<T>(entry);
        // Empty list case.
        if (0 == m_size)
        {
            m_head = new_node;
            m_tail = new_node;
        }
        // Normal cases.
        else
        {
            m_tail->set_next(new_node);
            m_tail = new_node;
        }
        m_size++;
    }

    // Add a given entry to a given index of the list.
    virtual void add(const size_t &index, const T &entry)
    {
        s_node<T> *new_node = new s_node<T>(entry);
        s_node<T> *prev_node = nullptr;
        // Case when adding to the frong of the list
        if (0 == index)
        {
            new_node->set_next(m_head);
            m_head = new_node;
        }
        // Other cases.
        else
        {
            prev_node = node_at(index - 1);
            new_node->set_next(prev_node->next());
            prev_node->set_next(new_node);
        }

        // Case when the list is empty.
        if ((!m_tail) || (prev_node == m_tail))
        {
            m_tail = new_node;
        }
        m_size++;
    }

    // Remove the entry at a given index from the list.
    virtual T remove(const size_t &index)
    {
        if (index >= m_size)
        {
            throw index_error("Index out of bounds.");
        }

        T rm;
        s_node<T> *cur_node;    // Node to be removed.
        // Case when removing the first entry from the list.
        if (0 == index)
        {
            cur_node = node_at(index);
            rm = cur_node->data();
            m_head = cur_node->next();
            // Case when removing the last entry in the list.
            if (!m_head)
            {
                m_tail = nullptr;
            }
        }
        // Other cases.
        else
        {
            s_node<T> *prev_node = node_at(index - 1);
            cur_node = prev_node->next();
            rm = cur_node->data();
            prev_node->set_next(cur_node->next());
            // Case when removing the last entry from the list.
            if (!cur_node->next())
            {
                m_tail = prev_node;
            }
        }
        delete cur_node;
        m_size--;
        return rm;
    }

    // Remove a given entry from the list.
    virtual void remove(const T &entry)
    {
        // TODO Implement this.
    }

    // Get the entry at a given index.
    virtual T get(const size_t &index) const
    {
        return node_at(index)->data();
    }

    // Set the value of the entry at a given index to a given entry.
    virtual void set(const size_t &index, const T &entry)
    {
        s_node<T> *cur_node = node_at(index);
        cur_node->set_data(entry);
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    virtual size_t index_of(const T &entry) const
    {
        size_t index = 0;
        s_node<T> *cur_node = m_head;

        while (cur_node)
        {
            if (entry == cur_node->data())
            {
                return index;
            }
            index++;
            cur_node = cur_node->next();
        }

        throw no_such_element("Cannot get the index of an entry that \
is not in the list.");
    }

    // Remove all the entries from the list, and free the memory.
    virtual void clear()
    {
        // delete m_head;
        // delete m_tail;
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    // Return if the list contains a given entry.
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