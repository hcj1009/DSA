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
        inline void insert_node(const size_t &index, const node_ptr &node);
        inline void remove_node(const size_t &index);
        inline void remove_node(const node_ptr &node);
        inline size_t index_of(const T &entry) const;

    public:
        d_linked_container();
        virtual ~d_linked_container();
        inline virtual void clear();
        inline virtual bool contains(const T &entry) const;
    };
}

#include "d_linked_container_impl.h"

#endif
