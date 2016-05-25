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
};

#endif