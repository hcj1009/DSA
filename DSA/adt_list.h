#ifndef ADT_LIST_H
#define ADT_LIST_H

#include "adt_container.h"

// Abstract data structure List.
template <class T>
class adt_list : adt_container<T>
{
public:
    // Default constructor of the list.
    adt_list() : adt_container() {};

    // Build a list based on a given array of elements.
    adt_list(const T elements[], const size_t &size) : adt_container() {};

    // Default destructor of the list.
    virtual ~adt_list() {};

    // Add a given element to a given index of the list.
    virtual void add(const size_t &index, const T &element) = 0;

    // TO-DO Add an array/list to the current list.

    // Remove the element at a given index from the list.
    virtual void remove(const size_t &index) = 0;

    // Remove a given element from the list.
    // Throw no_such_element exception if not found.
    virtual void remove(const T &element) = 0;

    // Get the element at a given index.
    virtual T get(const size_t &index) const = 0;

    // Set the value of the element at a given index to a given element.
    virtual void set(const size_t &index, const T &element) = 0;

    // Get the index of a given element.
    virtual (size_t)index_of(const T &element) const = 0;

    // TO-DO Override operators
};

#endif