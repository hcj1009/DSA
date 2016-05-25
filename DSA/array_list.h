#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cmath>
#include <stdexcept>
#include "no_such_element.h"
#include "adt_list.h"

using std::out_of_range;
using std::range_error;

// Array-based List implementation.
template <class T,
    size_t BASE_CAPACITY = 10>
class array_list : adt_list<T>
{
private:
    // Natural log 2, used in function capacity_of(const size_t &)
    const double LOG2 = 0.6931471805599453;

    T *list_data;
    size_t list_size;
    size_t list_capacity;

    // Helper function to determine the capacity needed to hold a
    // given size of list.
    size_t capacity_of(const size_t &size)
    {
        return (size_t)pow(2, ceil(log((double) size / BASE_CAPACITY) \
            / LOG2)) * BASE_CAPACITY;
    }

    // Helper function to shift a range of entries starting at a
    // given index with a given displacement.
    void shift(const size_t &index, const ptrdiff_t &displacement)
    {
        if (displacement == 0)
        {
            return;
        }

        if (index + displacement < 0)
        {
            throw range_error("Invalid displacement: index/indeces smaller \
than 0 after shifting.");
        }

        size_t new_size = list_size + displacement;
        size_t new_capacity = capacity_of(new_size);

        if (new_capacity > list_capacity)
        {
            list_capacity = new_capacity;
            T *new_data = new T[list_capacity];
            for (size_t i = 0; i < list_size; i++)
            {
                if (i < index)
                {
                    new_data[i] = list_data[i];
                }
                else
                {
                    new_data[i + displacement] = list_data[i];
                }
            }
            delete[] list_data;
            list_data = new_data;
        }
        else if ((displacement > 0) &&(list_size >= 1))  // shifting right
        {
            for (size_t i = list_size - 1; i >= index; i--)
            {
                list_data[i + displacement] = list_data[i];
            }
        }
        else    // case when displacement < 0, shifting left
        {
            for (size_t i = index; i < list_size; i++)
            {
                list_data[i + displacement] = list_data[i];
            }
        }
        list_size = new_size;
    }

public:
    // Default constructor of the list.
    array_list() : adt_list()
    {
        list_capacity = BASE_CAPACITY;
        list_data = new T[list_capacity];
        list_size = 0;
    }

    // Build a list based on a given array of entries.
    array_list(const T entries[], const size_t &size)
        : adt_list(entries, size)
    {
        list_capacity = capacity_of(size);
        list_data = new T[list_capacity];
        list_size = size;
        for (size_t i = 0; i < size; i++)
        {
            list_data[i] = entries[i];
        }
    }

    // Build a list based on a given list.
    array_list(const array_list<T, BASE_CAPACITY> &list) : adt_list(list)
    {
        list_capacity = list.capacity();
        list_data = new T[list_capacity];
        list_size = list.size();
        // TO-DO: Change the following code using iterator
        // Create a shallow copy of each entry in the given list.
        /*
        for (size_t i = 0; i < list_size; i++)
        {
            list_data[i] = list.get(i);
        }
        */
    }

    // Default destructor fo the list.
    virtual ~array_list()
    {
        delete[] list_data;
    }

    // Return if the container is empty.
    virtual bool empty() const
    {
        return (list_size == 0);
    }

    // Get the size of the list.
    virtual size_t size() const
    {
        return list_size;
    }
    
    // Get the capacity of the list;
    virtual size_t capacity() const
    {
        return list_capacity;
    }

    // Add a given entry to the container.
    virtual void add(const T &entry)
    {
        shift(list_size, 1);
        list_data[list_size - 1] = entry;
    }

    // Add a given entry to a given index of the list.
    virtual void add(const size_t &index, const T &entry)
    {
        if (index > list_size)
        {
            throw out_of_range("Index out of range.");
        }
        shift(index, 1);
        list_data[index] = entry;
    }

    // Remove the entry at a given index from the list.
    virtual void remove(const size_t &index)
    {
        if (index >= list_size)
        {
            throw out_of_range("Index out of range.");
        }
        shift(index + 1, -1);
    }

    // Remove a given entry from the list.
    virtual void remove(const T &entry)
    {
        size_t index = index_of(entry);
        remove(index);
    }

    // Get the entry at a given index.
    virtual T get(const size_t &index) const
    {
        if (index >= list_size)
        {
            throw out_of_range("Index out of range.");
        }
        return list_data[index];
    }

    // Set the value of the entry at a given index to a given entry.
    // Throw out_of_range exception.
    virtual void set(const size_t &index, const T &entry)
    {
        if (index >= list_size)
        {
            throw out_of_range("Index out of range.");
        }
        list_data[index] = entry;
    }

    // Get the index of a given entry.
    // Throw no_such_element exception when the given entry is not found.
    virtual size_t index_of(const T &entry) const
    {
        for (size_t i = 0; i < list_size; i++)
        {
            if (list_data[i] == entry)
            {
                return i;
            }
        }
        throw no_such_element("Cannot get the index of an entry that \
is not in the list.");
    }

    // Remove all the entries from the list, and free the memory.
    virtual void clear()
    {
        delete[] list_data;
        list_capacity = BASE_CAPACITY;
        list_data = new T[list_capacity];
        list_size = 0;
    }

    // Return if the list contains a given entry.
    virtual bool contains(const T &entry) const
    {
        size_t index = 0;
        try
        {
            index = index_of(entry);
        }
        catch (no_such_element exception)
        {
            return false;
        }
        return true;
    }
};

#endif