#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "adt_list.h"
#include "s_linked_container.h"

namespace DSA
{
    // List implementation based on singly linked node.
    template <class T>
    class s_linked_list
        : public adt_list<T>
        , public s_linked_container<T>
    {
        typedef std::shared_ptr<s_node<T>> node_ptr;
    protected:
        node_ptr m_tail;    // Optimization for adding to the back.

    public:
        // Default constructor of the lsit.
        s_linked_list()
            : s_linked_container()
            , m_tail() {}

        s_linked_list(const s_linked_list<T> &list)
        {
            m_head = node_ptr(list.m_head);
            m_tail = node_ptr(list.m_tail);
            m_size = list.m_size;
        }

        s_linked_list(s_linked_list<T> &&list) noexcept
        {
            m_head = std::move(list.m_head);
            m_tail = std::move(list.m_tail);
            m_size = std::move(list.m_size);
        }

        // Build a list based on a given array of entries.
        s_linked_list(const T entries[], const size_t &size)
        {
            if (0 == size)
            {
                s_linked_list();
            }
            else
            {
                m_head.reset(new s_node<T>(entries[0]));
                node_ptr cur_node = m_head;
                node_ptr new_node;
                for (size_t i = 1; i < size; i++)
                {
                    new_node.reset(new s_node<T>(entries[i]));
                    cur_node->set_next(new_node);
                    cur_node = cur_node->next();
                }
                m_tail = new_node;
                m_size = size;
            }
        }

        // Default destructor of the list.
        virtual ~s_linked_list() { }

        // Return if the container is empty.
        virtual bool empty() const
        {
            return s_linked_container<T>::empty();
        }

        // Get the size of the container.
        virtual size_t size() const
        {
            return s_linked_container<T>::size();
        }

        // Add a given entry to the container.
        virtual void add(const T &entry)
        {
            node_ptr new_node
                = node_ptr(new s_node<T>(entry));
            // Empty list case.
            if (0 == m_size)
            {
                m_head = new_node;
                m_tail = new_node;
            }
            // Normal cases.
            else
            {
                m_tail->set_next(new_node);
                m_tail = new_node;
            }
            m_size++;
        }

        // Add a given entry to a given index of the list.
        virtual void add(const size_t &index, const T &entry)
        {
            index == m_size ? add(entry) : insert_entry(index, entry);
        }

        virtual void add(const T entries[], const size_t &size)
        {

        }

        virtual void add(const size_t &index,
            const T entries[],
            const size_t &size)
        {

        }

        // Remove the entry at a given index from the list.
        virtual T remove(const size_t &index)
        {
            if (index >= m_size)
            {
                throw index_error("Index out of bounds.");
            }

            T cur_entry;
            node_ptr cur_node;    // Node to be removed.
            // Case when removing the first entry from the list.
            if (0 == index)
            {
                cur_node = node_at(index);
                cur_entry = cur_node->data();
                m_head = cur_node->next();
                // Case when removing the last entry in the list.
                if (!m_head)
                {
                    m_tail = node_ptr();
                }
            }
            // Other cases.
            else
            {
                node_ptr prev_node = node_at(index - 1);
                cur_node = prev_node->next();
                cur_entry = cur_node->data();
                prev_node->set_next(cur_node->next());
                // Case when removing the last entry from the list.
                if (!cur_node->next())
                {
                    m_tail = prev_node;
                }
            }
            m_size--;
            return cur_entry;
        }

        // Remove a given entry from the list.
        virtual void remove(const T &entry)
        {
            // TODO Implement this.
        }

        // Get the entry at a given index.
        virtual T get(const size_t &index) const
        {
            return node_at(index)->data();
        }

        // Set the value of the entry at a given index to a given entry.
        virtual void set(const size_t &index, const T &entry)
        {
            node_ptr cur_node = node_at(index);
            cur_node->set_data(entry);
        }

        // Remove all the entries from the list, and free the memory.
        virtual void clear()
        {
            s_linked_container<T>::clear();
            m_tail = nullptr;
        }

        virtual size_t index_of(const T &entry) const
        {
            return s_linked_container<T>::index_of(entry);
        }

        // Return if the list contains a given entry.
        virtual bool contains(const T &entry) const
        {
            return s_linked_container<T>::contains(entry);
        }

        virtual T *to_array() const
        {
            return nullptr;
        }

        virtual s_linked_list& operator=(const s_linked_list &rhs)
        {
            return *this;
        }
        virtual s_linked_list& operator=(s_linked_list &&rhs)
        {
            return *this;
        }
    };
}

#endif