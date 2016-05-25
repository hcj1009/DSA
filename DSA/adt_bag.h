#pragma once

template <class T>
class adt_bag
{
public:
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;

    virtual void add(const T & entry) = 0;
    virtual T remove() = 0;
    virtual void remove(const T & entry) = 0;
    virtual void clear() = 0;

    virtual size_t count(const T & entry) const = 0;
    virtual bool contains(const T & entry) const = 0;
    
    /*
    virtual const T[] to_array() const = 0;
    virtual const char[] c_str() const = 0;

    virtual adt_bag & operator+(const adt_bag & bag1, 
        const adt_bag & bag2) const = 0;

    virtual adt_bag & operator+=(const adt_bag & bag) = 0;
    virtual adt_bag & operator-=(const adt_bag & bag) = 0;
    virtual bool operator==(const adt_bag & bag1,
        const adt_bag & bag2) const = 0;
        */
};