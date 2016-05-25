#ifndef SL_NODE_H
#define SL_NODE_H

// Singly linked node
template <class T>
class s_node
{
private:
    T node_data;
    s_node<T> *node_next;

public:
    s_node(const T &data)
    {
        node_data = data;
        node_next = nullptr;
    }

    s_node(const T &data, s_node<T> *&next)
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

    virtual s_node<T> *next() const
    {
        return node_next;
    }

    virtual void set_next(s_node<T> *&next)
    {
        node_next = next;
    }
};

#endif