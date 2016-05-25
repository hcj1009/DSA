#pragma once
#include "no_such_element.h"
#include "adt_bag.h"

template <class T,
    size_t base_capacity = 10>
class array_bag : adt_bag<T>
{
private:
    size_t _size;
    size_t _capacity;
    T * _data;

    size_t find(const T & entry)
    {
        for (int i = 0; i < _size; i++)
        {
            if (_data[i] == entry)
            {
                return i;
            }
        }
    }

    void ensure_capacity()
    {
        if (_size == _capacity)
        {
            _capacity *= 2;
            T * _tmp = new T[_capacity];
            for (int i = 0; i < _size; i++)
            {
                _tmp[i] = _data[i];
            }
            delete[] _data;
            _data = _tmp;
        }
    }

public:
    array_bag()
    {
        _size = 0;
        _capacity = base_capacity;
        _data = new T[_capacity];
    }

    ~array_bag()
    {
        delete[] _data;
    }

    bool empty() const
    {
        return (_size == 0);
    }

    size_t size() const
    {
        return _size;
    }

    size_t capacity() const
    {
        return _capacity;
    }

    void add(const T & entry)
    {
        ensure_capacity();
        _data[_size] = entry;
        _size++;
    }

    T remove()
    {
        T removed = _data[--_size];
        _data[_size] = T();
        return removed;
    }

    void remove(const T & entry)
    {
        if (!contains(entry))
        {
            throw no_such_element("Removing an element that is not in the bag.");
        }
        size_t index = find(entry);
        _data[index] = _data[--_size];
        _data[_size] = T();
    }

    void clear()
    {
        delete[] _data;
        array_bag();
    }

    size_t count(const T & entry) const
    {
        size_t c = 0;
        for (int i = 0; i < _size; i++)
        {
            if (_data[i] == entry)
            {
                c++;
            }
        }
        return c;
    }

    bool contains(const T & entry) const
    {
        return (count(entry) != 0);
    }
};