#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// List implementation based on single-linked node.
template <class T>
class linked_list : adt_list<T>
{
private:
    (size_t)list_size;
    node<T> *list_head;
    node<T> *list_tail;    // Optimization for adding to the back.

    node<T> *node_at(const size_t &index)
    {
        return nullptr;
    }

public:
    // Default constructor of the lsit.
    linked_list() : adt_list()
    {
        list_size = 0;
        list_head = nullptr;
        list_tail = nullptr;
    }
    
    // Build a list based on a given array of elements.
    linked_list(const T elements[], const size_t &size)
        : adt_list(element, size)
    {
        // STUB
    }

    // Default destructor of the list.
    virtual ~linked_list()
    {
        // STUB
    }

    // Return if the container is empty.
    virtual bool empty() const
    {
        return (list_size == 0);
    }

    // Get the size of the container.
    virtual (size_t)size() const
    {
        return size;
    }

    // Add a given element to the container.
    virtual void add(const T &element)
    {
        node<T> new_node = new node<T>(element);
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
            list_size++;
        }
    }

    // Add a given element to a given index of the list.
    virtual void add(const size_t &index, const T &element)
    {
        // STUB
    }

    // Remove the element at a given index from the list.
    virtual void remvoe(const size_t &index)
    {
        // STUB
    }

    // Remove a given element from the list.
    virtual void remove(const T &element)
    {
        // STUB
    }

    // Get the element at a given index.
    virtual T get(const size_t &index) const
    {
        return T();
    }

    // Set the value of the element at a given index to a given element.
    virtual void set(const size_t &index, const T &element)
    {
        // STUB
    }

    // Get the index of a given element.
    // Throw no_such_element exception when the given element is not found.
    virtual (size_t)index_of(const T &element) const
    {
        return 0;
    }

    // Remove all the elements from the list, and free the memory.
    virtual void clear()
    {
        // STUB
    }

    // Return if the list contains a given element.
    virtual bool contains(const T &element) const
    {
        // STUB
        return false;
    }
};

#endif