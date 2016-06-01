#ifndef ADT_SEQUENCE_CONTAINER_H
#define ADT_SEQUENCE_CONTAINER_H

#include <iterator>

namespace DSA
{
    template <class T>
    class adt_sequence_container
    {
    public:
        // Default constructor of the container.
        adt_sequence_container() = default;

        // Return if the container is empty.
        // A container is empty when it does not contain any entry.
        virtual bool empty() const = 0;

        // Get the number of entries in the container.
        virtual size_t size() const = 0;

        // Remove all the entries from the container, and free the memory.
        virtual void clear() = 0;

        /*
        // Add a given entry to the container.
        // If the sequence container has a maximum capacity,
        // will throw full_container exception if full.
        virtual void add(const T &entry) = default;

        // Add a given sequence container to the current container.
        // All derived sequence container must implement 
        // sequence_container_traits, and stactic_check before adding.
        // If the sequence container has a maximum capacity,
        // will throw invalid_argument exception if the container
        // will exceed its limit after adding the given container,
        // and the given container should not be added.
        template <class E>
        virtual void add(const E &container) = default;

        virtual void remove(const T &entry) = default;

        template <class E>
        virtual void remove(const E &container) = default;

        */

        // Return if a given entry is in the container.
        virtual bool contains(const T &entry) const = 0;

        // Return an array of all the entries in the container.
        virtual T *to_array() const = 0;
    };

    template <class T>
    struct sequence_container_traits
    {
    public:
        const static bool is_sequence_container = false;
        const static bool support_push_front = false;
        const static bool support_push_back = false;
        const static bool support_insert = false;
        const static bool support_pop_front = false;
        const static bool support_pop_back = false;
        const static bool support_index_remove = false;
        const static bool support_entry_remove = false;
        const static bool support_index_of = false;
        const static bool support_at = false;
        const static bool support_reserve = false;
        const static bool support_shrink = false;
    };
}

#endif
