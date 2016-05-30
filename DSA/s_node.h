#ifndef SL_NODE_H
#define SL_NODE_H

#include "memory"

namespace DSA
{
    // Singly linked node
    template <class T>
    class s_node
    {
        typedef std::shared_ptr<s_node<T>> node_ptr;
    protected:
        T m_data;
        node_ptr m_next;
    public:
        s_node(const T &data) : m_data(data) {}
        s_node(const T &data, node_ptr next)
            : m_data(data), m_next(next) {}
        virtual ~s_node() {}
        virtual T data() const { return m_data; }
        virtual void set_data(const T &data) { m_data = data; }
        node_ptr next() { return m_next; }
        virtual void set_next(node_ptr next)
        {
            m_next = std::move(next);
        }
    };
}

#endif