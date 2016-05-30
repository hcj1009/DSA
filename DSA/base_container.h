#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

#include "adt_container.h"

namespace DSA
{
    template <class T>
    class base_container : virtual public adt_container<T>
    {
    protected:
        size_t m_size;
    public:
        base_container();
        virtual ~base_container();
        inline virtual bool empty() const;
        inline virtual size_t size() const;
        inline virtual void clear();
        inline virtual bool contains(const T &entry) const;
    };
}

#include "base_container_impl.h"

#endif