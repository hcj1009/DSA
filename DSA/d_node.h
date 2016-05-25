#ifndef D_NODE_H
#define D_NODE_H

// Doubly linked node
template <class T>
class d_node
{
private:
    T node_data;
    d_node<T> *node_prev;
    d_node<T> *node_next;

public:
    d_node(const T &data)
    {
        node_data = data;
        node_prev = nullptr;
        node_next = nullptr;
    }

    s_node(d_node<T> *&prev, const T &data, s_node<T> *&prev)
    {
        node_data = data;
        node_prev = prev;
        node_next = next;
    }

    virtual T data() const
    {
        return node_data;
    }

    virtual void set_data(const T &data)
    {
        node_data = data;
    }

    virtual d_node<T> *&next()
    {
        return node_next;
    }

    virtual void set_next(d_node<T> *&next)
    {
        node_next = next;
    }

    virtual d_node<T> *&prev()
    {
        return node_prev;
    }

    virtual void set_prev(d_node<T> *&prev)
    {
        node_prev = prev;
    }
};

#endif