#ifndef S_LINKED_CONTAINER_H
#define S_LINKED_CONTAINER_H

#include "dsa_except.h"
#include "base_container.h"
#include "s_node.h"

namespace DSA
{
    template <class T>
    class s_linked_container
        : virtual public base_container<T>
    {
        typedef base_container<T> base_impl;
        typedef std::shared_ptr<s_node<T>> node_ptr;
    protected:
        node_ptr m_head;
        // Get the node at a given position (index) in the linked chain.
        inline node_ptr node_at(const size_t &index) const;
        // Get the node that contains a given entry in the linked chain.
        inline node_ptr node_of(const T &entry) const;
        inline void insert_front(const T &entry);
        inline void insert_entry(const size_t &index, const T &entry);

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
