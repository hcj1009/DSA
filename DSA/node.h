#ifndef NODE_H
#define NODE_H

// Single-linked node
template <class T>
class node
{
private:
    T node_data;
    node<T> *node_next;

public:
    node(const T &data)
    {
        node_data = data;
        node_next = nullptr;
    }

    node(const T &data, const node<T> &next)
    {
        node_data = data;
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

    virtual node<T> next() const
    {
        return node_next;
    }

    virtual void set_next(const node<T> &next)
    {
        node_next = next;
    }
};

#endif