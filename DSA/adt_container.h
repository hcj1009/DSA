#ifndef ADT_CONTAINER_H
#define ADT_CONTAINER_H

#include "dsaexcept.h"

template <class T>
class adt_container
{
public:
    // Default constructor of the container.
    adt_container() {}

    // Default destructor of the container.
    virtual ~adt_container() {}

    // Return if the container is empty.
    virtual bool empty() const = 0;

    // Get the size of the container.
    virtual size_t size() const = 0;

    // Remove all the entries from the container, and free the memory.
    virtual void clear() = 0;

    // Return if the container contains a given entry.
    virtual bool contains(const T &entry) const = 0;
};

#endif