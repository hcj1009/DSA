#ifndef D_NODE_H
#define D_NODE_H

// Doubly linked node
template <class T>
class d_node
{
protected:
    T m_data;
    d_node<T> *m_prev;
    d_node<T> *m_next;

public:
    d_node(const T &data)
    {
        m_data = data;
        m_prev = nullptr;
        m_next = nullptr;
    }

    s_node(d_node<T> *&prev, const T &data, s_node<T> *&prev)
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

    virtual d_node<T> *&next()
    {
        return m_next;
    }

    virtual void set_next(d_node<T> *&next)
    {
        m_next = next;
    }

    virtual d_node<T> *&prev()
    {
        return m_prev;
    }

    virtual void set_prev(d_node<T> *&prev)
    {
        m_prev = prev;
    }
};

#endif