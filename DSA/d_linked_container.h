#ifndef D_LINKED_CONTAINER_H
#define D_LINKED_CONTAINER_H

#include "base_container.h"
#include "d_node.h"

namespace DSA
{
    template <class T>
    class d_linked_container
        : virtual public base_container<T>
    {
        typedef base_container<T> base_impl;
        typedef std::shared_ptr<d_node<T>> node_ptr;
    protected:
        node_ptr m_head;
        node_ptr m_tail;
        inline node_ptr node_at(const size_t &index) const;
        inline node_ptr node_of(const T &entry) const;
        inline void insert_front(const T &entry);
        inline void insert_back(const T &entry);
        inline void insert_entry(const size_t &index, const T &entry);

    public:
        d_linked_container();
        virtual ~d_linked_container();
        inline virtual void clear();
        // TODO Optimize this:
        // Get the index of a given entry.
        // Throw no_such_element exception when the given entry is not found.
        inline virtual size_t index_of(const T &entry) const;
        inline virtual bool contains(const T &entry) const;
    };
}

#endif
