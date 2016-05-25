#ifndef ADT_CONTAINER_H
#define ADT_CONTAINER_H

template <class T>
class adt_container
{
public:
    // Default constructor of the container.
    adt_container() {};

    // Default destructor of the container.
    virtual ~adt_container() {};

    // Return if the container is empty.
    virtual bool empty() const = 0;

    // Get the size of the container.
    virtual size_t size() const = 0;

    // Add a given element to the container.
    virtual void add(const T & element) = 0;

    // Remove all the elements from the list, and free the memory.
    virtual void clear() = 0;

    // Return if the list contains a given element.
    virtual bool contains(const T & element) const = 0;
};

#endif