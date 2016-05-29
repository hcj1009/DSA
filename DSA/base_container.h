#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

#include "adt_container.h"

template <class T>
class base_container : virtual public adt_container<T>
{
protected:
    size_t m_size;

public:
    base_container() : adt_container<T>()
    {
        m_size = 0;
    }

    virtual ~base_container() {}

    virtual bool empty() const
    {
        return (0 == m_size);
    }

    virtual size_t size() const
    {
        return m_size;
    }

    virtual void clear()
    {
        m_size = 0;
    }

    virtual bool contains(const T &entry) const
    {
        return false;
    }
};

#endif