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
    protected:
        s_node<T> *m_head;

        // Get the node at a given position (index) in the linked chain.
        s_node<T> *node_at(const size_t &index) const
        {
            if (index >= m_size)
            {
                throw index_error("Index out of bounds.");
            }
            s_node<T> *cur_node = m_head;
            for (size_t i = 0; i < index; i++)
            {
                cur_node = cur_node->next();
            }
            return cur_node;
        }

        // Get the node that contains a given entry in the linked chain.
        s_node<T> *node_of(const T &entry) const
        {
            s_node<T> *cur_node = m_head;
            while (cur_node)
            {
                if (entry == cur_node->data())
                {
                    return cur_node;
                }
                cur_node = cur_node->next();
            }
            throw no_such_element("Cannot find such entry in the container.");
        }

        inline void delete_node(s_node<T> *node)
        {
            if (!node)
            {
                return;
            }
            delete_node(node->next());
            node->set_next(nullptr);
            delete node;
        }

        void insert_front(const T &entry)
        {
            s_node<T> *new_node = new s_node<T>(entry);
            new_node->set_next(m_head);
            m_head = new_node;
            m_size++;
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
                s_node<T> *new_node = new s_node<T>(entry);
                s_node<T> &prev_node = *node_at(index - 1);
                new_node->set_next(prev_node.next());
                prev_node.set_next(new_node);
                m_size++;
            }
        }

    public:
        s_linked_container() : base_container()
        {
            m_head = nullptr;
        }

        virtual ~s_linked_container()
        {
            delete_node(m_head);
        }

        virtual void clear()
        {
            base_container<T>::clear();
            delete_node(m_head);
            m_head = nullptr;
        }

        // Get the index of a given entry.
        // Throw no_such_element exception when the given entry is not found.
        virtual size_t index_of(const T &entry) const
        {
            size_t index = 0;
            s_node<T> *cur_node = m_head;

            while (cur_node)
            {
                if (entry == cur_node->data())
                {
                    return index;
                }
                index++;
                cur_node = cur_node->next();
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