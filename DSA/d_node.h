#ifndef D_NODE_H
#define D_NODE_H

#include <memory>

namespace DSA
{
    // Doubly linked node
    template <class T>
    class d_node
    {
        typedef std::shared_ptr<d_node<T>> node_ptr;
    protected:
        T m_data;
        node_ptr m_prev;
        node_ptr m_next;

    public:
        d_node(const T &data) : m_data(data), m_prev(), m_next() {}

        d_node(const node_ptr &prev,
            const T &data, 
            const node_ptr &next)
            : m_data(data), m_prev(prev), m_next(next) {}

        virtual ~d_node() {}

        inline virtual T data() const
        {
            return m_data;
        }

        inline virtual void set_data(const T &data)
        {
            m_data = data;
        }

        inline virtual node_ptr next()
        {
            return m_next;
        }

        inline virtual void set_next(const node_ptr &next)
        {
            m_next = next;
        }

        inline virtual node_ptr prev()
        {
            return m_prev;
        }

        inline virtual void set_prev(const node_ptr &prev)
        {
            m_prev = prev;
        }
    };
}

#endif
