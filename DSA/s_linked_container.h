#ifndef S_LINKED_CONTAINER_H
#define S_LINKED_CONTAINER_H

#include "dsa_except.h"
#include "base_container.h"
#include "s_node.h"

namespace DSA
{
    // Sequence container implemented by a singly linked chain.
    // Each linked node contains a pointer pointing to its next node.
    // 
    template <class T>
    class s_linked_container
        : virtual public base_container<T>
    {
        typedef base_container<T> base_impl;
        typedef std::shared_ptr<s_node<T>> node_ptr;
    protected:
        // Pointer to the head of the linked chain.
        node_ptr m_head;

        // Helper function node_at(const size_t &index)
        // Get the node at a given position (index) in the linked chain.
        inline virtual node_ptr node_at(const size_t &index) const;

        // Helper function node_of(const T &entry) const
        // Get the node that contains a given entry in the linked chain.
        inline virtual node_ptr node_of(const T &entry) const;

        inline virtual T entry_at(const size_t &index) const;

        // Insert a given entry to the front of the container.
        inline virtual void insert_front(const T &entry);

        // Insert a given entry to the back of the container.
        inline virtual void insert_back(const T &entry);

        // Insert a given entry to a given position in the container.
        // If index == 0, call insert_front(entry);
        // If index == m_size, call insert_back(entry);
        // Else, get the node at the previous position of the given index,
        // change linked nodes' prev/next pointers accordingly.
        inline virtual void insert_entry(const size_t &index, const T &entry);



    public:
        s_linked_container();
        virtual ~s_linked_container();
        inline virtual void clear();
        // Get the index of a given entry.
        // Throw no_such_element exception when the given entry is not found.
        inline virtual size_t index_of(const T &entry) const;
        inline virtual bool contains(const T &entry) const;
    };
}

#include "s_linked_container_impl.h"

#endif
