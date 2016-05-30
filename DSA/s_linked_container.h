#ifndef S_LINKED_CONTAINER_H
#define S_LINKED_CONTAINER_H

#include "dsa_except.h"
#include "base_container.h"
#include "s_node.h"

namespace DSA
{
    template <class T>
    class s_linked_container
        : virtual public base_container<T>
    {
        typedef base_container<T> base_impl;
        typedef std::shared_ptr<s_node<T>> node_ptr;
    protected:
        node_ptr m_head;

        // Get the node at a given position (index) in the linked chain.
        node_ptr node_at(const size_t &index) const
        {
            if (index >= base_impl::m_size)
            {
                throw index_error("Index out of bounds.");
            }
            node_ptr cur_node
                = node_ptr(m_head);
            for (size_t i = 0; i < index; i++)
            {
                cur_node = std::move(cur_node->next());
            }
            return cur_node;
        }

        // Get the node that contains a given entry in the linked chain.
        node_ptr node_of(const T &entry) const
        {
            node_ptr cur_node = m_head;
            while (&cur_node)
            {
                if (entry == cur_node->data())
                {
                    return cur_node;
                }
                cur_node = cur_node->next();
            }
            throw no_such_element("Cannot find such entry in the container.");
        }

        void insert_front(const T &entry)
        {
            node_ptr new_node 
                = node_ptr(new s_node<T>(entry));
            new_node->set_next(m_head);
            m_head = std::move(new_node);
            base_impl::m_size++;
        }

        void insert_entry(const size_t &index, const T &entry)
        {
            // Case when adding to the frong of the list
            if (0 == index)
            {
                insert_front(entry);
            }
            // Other cases.
            else
            {
                node_ptr new_node 
                    = node_ptr(new s_node<T>(entry));
                node_ptr prev_node 
                    = std::move(node_at(index - 1));
                new_node->set_next(prev_node->next());
                prev_node->set_next(new_node);
                base_impl::m_size++;
            }
        }

    public:
        s_linked_container() : base_container<T>()
        {
            m_head = node_ptr();
        }

        virtual ~s_linked_container() {}

        virtual void clear()
        {
            base_container<T>::clear();
        }

        // Get the index of a given entry.
        // Throw no_such_element exception when the given entry is not found.
        virtual size_t index_of(const T &entry) const
        {
            size_t index = 0;
            node_ptr cur_node = std::move(m_head);

            while (cur_node)   // cur_node != nullptr;
            {
                // Fix this:
                if (entry == cur_node->data())
                {
                    return index;
                }
                index++;
                cur_node = std::move(cur_node->next());
            }

            throw no_such_element("Cannot get the index of an entry that \
is not in the list.");
        }

        virtual bool contains(const T &entry) const
        {
            try
            {
                index_of(entry);
            }
            catch (no_such_element exception)
            {
                return false;
            }
            return true;
        }
    };
}

#endif
