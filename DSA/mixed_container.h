#ifndef MIXED_CONTAINER
#define MIXED_CONTAINER

#include <memory>

namespace DSA
{
    template <class T>
    class mixed_container<T>
        : virtual public d_linked_container<std::unique_ptr<std::shared_ptr[]>>
    {
        typedef std::ptrdiff_t ptrdiff_t;
        typedef std::shared_ptr<T> entry_ptr;
        typedef std::unique_ptr<entry_ptr[]> array_ptr;
        typedef d_node<array_ptr> node_ptr;
        typedef std::shared_ptr<node_ptr> data_ptr;
    protected:
        // m_head => [ unique_ptr array [shared_ptr object]] <= m_tail
        // m_head/m_tail is a doubly linked node pointer that contains a
        // unique pointer pointing to an array that contains shared pointers
        // pointing to objects of type T.

        // m_data 
    public:
    };
}

#endif