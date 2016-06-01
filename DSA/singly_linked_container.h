#ifndef SINGLY_LINKED_CONTAINER_H
#define SINGLY_LINKED_CONTAINER_H

#include "dsa_except.h"
#include "adt_sequence_container.h"
#include "s_node.h"

namespace DSA
{
    // Sequence container implemented by a singly linked chain.
    // Each linked node contains a pointer pointing to its next node.
    // 
    template <class T>
    class singly_linked_container
        : virtual public adt_sequence_container<T>
    {
        typedef std::shared_ptr<s_node<T>> node_ptr;
    protected:
        // Pointer to the first node of the linked chain.
        node_ptr m_head;
        size_t m_size;

        // Tail reference disabled by default.
#ifdef SINGLY_LINKED_CONTAINER_TAIL_REFERENCE_FLAG
        // Pointer to the last node of the linked chain.
        node_ptr m_tail;
#endif

        // Helper function node_at(const size_t &index)
        // Get the node at a given position (index) in the linked chain.
        inline virtual node_ptr node_at(const size_t &index) const;

        // Helper function node_of(const T &entry) const
        // Get the node that contains a given entry in the linked chain.
        inline virtual node_ptr node_of(const T &entry) const;

    public:
        singly_linked_container();
        virtual ~singly_linked_container();

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
    struct sequence_container_traits<singly_linked_container<T>>
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
    };
}

#include "singly_linked_container_impl.h"

#endif
