#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "no_such_element.h"
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

    // Helper function to get the node at a given index.
    s_node<T> *node_at(const size_t &index) const
    {
        if (index >= list_size)
        {
            throw out_of_range("Index out of range.");
        }
        s_node<T> *current = list_head;
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
        list_head = nullptr;
        list_tail = nullptr;
        list_size = 0;
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
        // delete list_head;
        // delete list_tail;
    }

    // Return if the container is empty.
    virtual bool empty() const
    {
        return (0 == list_size);
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
        if (0 == list_size)
        {
            list_head = new_node;
            list_tail = new_node;
        }
        // Normal cases.
        else
        {
            list_tail->set_next(new_node);
            list_tail = new_node;
        }
        list_size++;
    }

    // Add a given entry to a given index of the list.
    virtual void add(const size_t &index, const T &entry)
    {
        s_node<T> *new_node = new s_node<T>(entry);
        s_node<T> *prev_node = nullptr;
        // Case when adding to the frong of the list
        if (0 == index)
        {
            new_node->set_next(list_head);
            list_head = new_node;
        }
        // Other cases.
        else
        {
            prev_node = node_at(index - 1);
            new_node->set_next(prev_node->next());
            prev_node->set_next(new_node);
        }

        // Case when the list is empty.
        if ((!list_tail) || (prev_node == list_tail))
        {
            list_tail = new_node;
        }
        list_size++;
    }

    // Remove the entry at a given index from the list.
    virtual T remove(const size_t &index)
    {
        if (index >= list_size)
        {
            throw out_of_range("Index out of range.");
        }

        T rm;
        s_node<T> *cur_node;    // Node to be removed.
        // Case when removing the first entry from the list.
        if (0 == index)
        {
            cur_node = node_at(index);
            rm = cur_node->data();
            list_head = cur_node->next();
            // Case when removing the last entry in the list.
            if (!list_head)
            {
                list_tail = nullptr;
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
                list_tail = prev_node;
            }
        }
        delete cur_node;
        list_size--;
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
        s_node<T> *cur_node = list_head;

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
        // delete list_head;
        // delete list_tail;
        list_head = nullptr;
        list_tail = nullptr;
        list_size = 0;
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