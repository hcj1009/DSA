#ifndef ADT_SET_H
#define ADT_SET_H

#include "adt_container.h"

template <class T>
class adt_set : virtual public adt_container<T>
{
public:
    adt_set() : adt_container<T>() {}
    virtual ~adt_set() {}

    virtual void add(const T &entry) = 0;
    virtual T remove() = 0;
    virtual void remove(const T &entry) = 0;
};

#endif