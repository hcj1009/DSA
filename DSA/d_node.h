#ifndef D_NODE_H
#define D_NODE_H

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
        d_node(const T &data)
        {
            m_data = data;
            m_prev = nullptr;
            m_next = nullptr;
        }

        d_node(const node_ptr &prev, const T &data, const node_ptr &next)
        {
            m_data = data;
            m_prev = prev;
            m_next = next;
        }

        virtual T data() const
        {
            return m_data;
        }

        virtual void set_data(const T &data)
        {
            m_data = data;
        }

        virtual node_ptr next()
        {
            return m_next;
        }

        virtual void set_next(const node_ptr &next)
        {
            m_next = next;
        }

        virtual d_node<T> *&prev()
        {
            return m_prev;
        }

        virtual void set_prev(const node_ptr &prev)
        {
            m_prev = prev;
        }
    };
}

#endif