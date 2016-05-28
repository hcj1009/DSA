#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "dsaexcept.h"
#include "adt_stack.h"
#include "s_node.h"

// Singly linked node implementation of LIFO Stack data structure.
template<class T>
class linked_stack : public adt_stack<T>
{
protected:
    s_node<T> *stack_top;
    size_t stack_size;

public:
    linked_stack() : adt_stack()
    {
        stack_top = nullptr;
        stack_size = 0;
    }

    linked_stack(const linked_stack<T> &stack)
        : adt_stack()
    {

    }

    virtual ~linked_stack()
    {
        stack_top = nullptr;
        delete stack_top;
    }

    // Return if the stack is empty.
    virtual bool empty() const
    {
        return (0 == stack_size);
    }

    // Get the size of the stack.
    virtual size_t size() const
    {
        return stack_size;
    }

    // Get the entry on the top of the stack.
    virtual T peek() const
    {
        if (0 == stack_size)
        {
            throw empty_container("Cannot pop from an empty stack.");
        }
        return stack_top->data();
    }

    // Add a given entry to the stack.
    virtual void add(const T &entry)
    {
        push(entry);
    }

    // Push an entry to the top of the stack.
    // Alias for add(const T &entry)
    virtual void push(const T &entry)
    {
        s_node<T> *new_node = new s_node<T>(entry, stack_top);
        stack_top = new_node;
        stack_size++;
    }

    // Pop the top entry from the stack.
    virtual T pop()
    {
        if (0 == stack_size)
        {
            throw empty_container("Cannot pop from an empty stack.");
        }
        s_node<T> *top_node = stack_top;
        stack_top = stack_top->next();
        stack_size--;
        return top_node->data();
    }

    // Remove all the entries from the stack, and free the memory.
    virtual void clear()
    {
        stack_top = nullptr;
        stack_size = 0;
    }

    // Return if the stack contains a given entry.
    virtual bool contains(const T &entry) const
    {
        s_node<T> *cur_node = stack_top;
        while (cur_node)
        {
            if (entry == cur_node->data())
            {
                return true;
            }
            cur_node = cur_node->next();
        }
        return false;
    }

    linked_stack& operator=(const linked_stack<T> &stack)
    {
        return *this;
    }

    linked_stack& operator=(linked_stack<T> &&stack)
    {
        return *this;
    }
};

#endif