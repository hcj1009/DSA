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

    // Build a list based on a given array of entries.
    adt_list(const T entries[], const size_t &size) : adt_container() {};

    // Default destructor of the list.
    virtual ~adt_list() {};

    // Add a given entry to a given index of the list.
    virtual void add(const size_t &index, const T &entry) = 0;

    // TO-DO Add an array/list to the current list.

    // Remove the entry at a given index from the list.
    virtual T remove(const size_t &index) = 0;

    // Remove a given entry from the list.
    // Throw no_such_element exception if not found.
    virtual void remove(const T &entry) = 0;

    // Get the entry at a given index.
    virtual T get(const size_t &index) const = 0;

    // Set the value of the entry at a given index to a given entry.
    virtual void set(const size_t &index, const T &entry) = 0;

    // Get the index of a given entry.
    virtual size_t index_of(const T &entry) const = 0;

    // TO-DO Override operators
};

#endif