#ifndef MIXED_CONTAINER
#define MIXED_CONTAINER

#include <memory>

namespace DSA
{
    template <class T>
    class mixed_container<T>
        : virtual public adt_container<T>
        , virtual public d_linked_container<std::unique_ptr<std::shared_ptr<T>[]>>
    {
        typedef std::ptrdiff_t ptrdiff_t;
        typedef std::shared_ptr<T> entry_ptr;
        typedef std::unique_ptr<entry_ptr[]> array_ptr;
        typedef d_node<array_ptr> node_ptr;
        typedef std::shared_ptr<node_ptr> data_ptr;
        typedef d_linked_container<data_ptr> base_impl;
    protected:
        static const size_t DEFAULT_BASE_CAPACITY = 10;

        // m_head => [ unique_ptr array [shared_ptr object]] <= m_tail
        // m_head/m_tail is a doubly linked node pointer that contains a
        // unique pointer pointing to an array that contains shared pointers
        // pointing to objects of type T.
        // node_ptr m_head;
        // node_ptr m_tail;

        // The capacity of each array cell in the doubly linked chain.
        size_t m_array_capacity;

        // [_, _, _, _, *entry, *entry] <=> [*entry, ...]
        //  0  1  2  3    ^ m_front = 4
        //             ^ m_head                  ^ m_head->next()
        // The first entry in the container.
        size_t m_front;

        // Shift every entry lies after a given index a given displacement.
        inline void shift(const size_t &index, const ptrdiff_t &disp);
        // Insert a given entry to the front of the container.
        inline void insert_front(const T &entry);
        // Insert a given entry to the back of the container.
        inline void insert_back(const T &entry);
        // Remove the first entry in the container.
        inline T remove_front();
        // Remove the last entry (in position) in the container.
        inline T remove_back();

        // Insert entry to the container.
        // If index == 0, call insert_front();
        // If index == m_size, call insert_back();
        // Else, determine which direction to shift, and call shift();
        inline void insert_entry(const size_t &index, const T &entry);

        inline void remove_entry(const size_t &index);

    public:
        mixed_container(const size_t &array_capacity = DEFAULT_BASE_CAPACITY);
        virtual ~mixed_container();
        inline virtual bool empty() const;
        inline virtual bool contains(const T &entry) const;
    };
}

#include "mixed_container_impl.h"

#endif