#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "adt_list.h"
#include "s_node.h"

// List implementation based on singly linked node.
template <class T>
class s_linked_list : adt_list<T>
{
private:
    size_t list_size;
    s_node<T> *list_head;
    s_node<T> *list_tail;    // Optimization for adding to the back.

    s_node<T> *node_at(const size_t &index)
    {
        return nullptr;
    }

public:
    // Default constructor of the lsit.
    s_linked_list() : adt_list()
    {
        list_head = nullptr;
        list_tail = nullptr;
        list_size = 0;
    }
    
    // Build a list based on a given array of entries.
    s_linked_list(const T entries[], const size_t &size)
        : adt_list(entries, size)
    {
        if (size == 0)
        {
            s_linked_list();
        }
        else
        {
            list_head = new s_node<T>(entries[0]);
            s_node<T> *current = list_head;
            s_node<T> *new_node = nullptr;
            for (size_t i = 1; i < size; i++)
            {
                new_node = new s_node<T>(entries[i]);
                current->set_next(new_node);
                current = current->next();
            }
            list_tail = new_node;
            list_size = size;
        }
    }

    // Default destructor of the list.
    virtual ~s_linked_list()
    {
        delete list_head;
        delete list_tail;
        list_head = nullptr;
        list_tail = nullptr;
    }

    // Return if the container is empty.
    virtual bool empty() const
    {
        return (list_size == 0);
    }

    // Get the size of the container.
    virtual size_t size() const
    {
        return list_size;
    }

    // Add a given entry to the container.
    virtual void add(const T &entry)
    {
        s_node<T> *new_node = new s_node<T>(entry);
        // Empty list case.
        if (list_size == 0)
        {
            list_head = new_node;
            list_tail = new_node;
        }
        // Normal cases.
        else
        {
            list_tail->set_next(new_node);
            list_tail = new_node;
            list_size++;
        }
    }

    // Add a given entry to a given index of the list.
    virtual void add(const size_t &index, const T &entry)
    {
        // STUB
    }

    // Remove the entry at a given index from the list.
    virtual void remove(const size_t &index)
    {

    }

    // Remove a given entry from the list.
    virtual void remove(const T &entry)
    {
        // STUB
    }

    // Get the entry at a given index.
    virtual T get(const size_t &index) const
    {
        return T();
    }

    // Set the value of the entry at a given index to a given entry.
    virtual void set(const size_t &index, const T &entry)
    {
        // STUB
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    virtual size_t index_of(const T &entry) const
    {
        return 0;
    }

    // Remove all the entries from the list, and free the memory.
    virtual void clear()
    {
        // STUB
    }

    // Return if the list contains a given entry.
    virtual bool contains(const T &entry) const
    {
        // STUB
        return false;
    }
};

#endif