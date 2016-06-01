#ifndef DOUBLY_LINKED_CONTAINER_H
#define DOUBLT_LINKED_CONTAINER_H

#include "dsa_except.h"
#include"adt_sequence_container.h"
#include "d_node.h"

namespace DSA
{
    template <class T>
    class doubly_linked_container
    {
        typedef std::shared_ptr<d_node<T>> node_ptr;
    protected:
        size_t m_size;
        node_ptr m_head;
        node_ptr m_tail;
        inline node_ptr node_at(const size_t &index) const;
        inline node_ptr node_of(const T &entry) const;

    public:
        doubly_linked_container();
        virtual ~doubly_linked_container();

        // Return if the container is empty.
        // A container is empty when it does not contain any entry.
        inline virtual bool empty() const;

        // Get the number of entries in the container.
        inline virtual size_t size() const;

        // Remove all the entries from the container, and free the memory.
        inline virtual void clear();

        // Insert a given entry to the front of the container.
        // Same as insert_entry(0, entry);
        inline virtual void push_front(const T &entry);

        // Insert a given entry to the back of the container.
        // Same as insert_entry(m_size, entry);
        inline virtual void push_back(const T &entry);

        // Insert a given entry to a given place in the container.
        inline virtual void insert(const size_t &index, const T &entry);

        // Remove and return the object at the front of the container.
        inline virtual T pop_front();

        // Remove and return the object at the end of the container.
        inline virtual T pop_back();

        // Remove a given entry from the container.
        // Note that only one entry will be removed if there are duplicates.
        // Throw no_such_element exception if the entry is not found.
        inline virtual void remove(const T &entry);

        // Remove the entry at a given index.
        // Throw index_error exception when index out of bounds.
        inline virtual T remove(const size_t &index);

        // Return the entry at a given position in the container.
        // Throw index_error exception when index out of bounds.
        inline virtual T at(const size_t &index) const;

        // Get the index of a given entry.
        // Throw no_such_element exception when the given entry is not found.
        inline virtual size_t index_of(const T &entry) const;

        // Return if the container contains a given entry.
        inline virtual bool contains(const T &entry) const;

        inline virtual T *to_array() const;
    };

    template <class T>
    struct sequence_container_traits<doubly_linked_container<T>>
    {
    public:
        const static bool is_sequence_container = true;
        const static bool support_push_front = true;
        const static bool support_push_back = true;
        const static bool support_insert = true;
        const static bool support_pop_front = true;
        const static bool support_pop_back = true;
        const static bool support_index_remove = true;
        const static bool support_entry_remove = true;
        const static bool support_index_of = true;
        const static bool support_at = true;
        const static bool support_reserve = false;
        const static bool support_shrink = false;
    };
}

#include "doubly_linked_container_impl.h"

#endif
