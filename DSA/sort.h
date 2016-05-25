#pragma once
#include <functional>
#include <algorithm>

using std::swap;
using std::less;

// 
template <class T,
    class Compare = less<T>>
bool isSorted(T array[],
    const size_t &lo,
    const size_t &hi,
    Compare comp = Compare())
{
    for (size_t i = lo; i < hi; i++)
    {
        if (!comp(array[i], array[i + 1]))
        {
            return false;
        }
    }
    return true;
}

// Selection sort.
template <class T,
    class Compare = less<T>>
void selectionSort(T array[],
    const size_t &lo,
    const size_t &hi,
    Compare comp = Compare())
{
    for (size_t i = lo; i < hi; i++)
    {
        size_t min = i;
        for (size_t j = i + 1; j <= hi; ++j)
        {
            if (comp(array[j], array[min]))
            {
                min = j;
            }
        }
        if (min != i)
        {
            swap<T>(array[i], array[min]);
        }
    }
}

// Insertion sort.
template <class T,
    class Compare = less<T>>
void insertionSort(T array[],
    const size_t &lo,
    const size_t &hi,
    Compare comp = Compare())
{
    for (size_t i = lo; i <= hi; i++)
    {
        for (size_t j = i; j > 0; j--)
        {
            if (comp(array[j], array[j - 1]))
            {
                swap(array[j], array[j - 1]);
            }
            else
            {
                break;
            }
        }
    }
}

// Quick sort
template <class T,
    class Compare = less<T>>
size_t partition(T array[],
    const size_t &lo,
    const size_t &hi,
    Compare comp = Compare())
{
    size_t i = lo;
    for (size_t j = lo; j < hi; j++)
    {
        if (comp(array[j], array[hi]))
        {
            swap(array[i], array[j]);
            i++;
        }
    }
    swap(array[i], array[hi]);
    return i;
}

template <class T,
    class Compare = less<T>>
void quickSort(T array[],
    const size_t &lo,
    const size_t &hi,
    Compare comp = Compare())
{
    if (lo < hi)
    {
        size_t p = partition(array, lo, hi, comp);
        quickSort(array, lo, p - 1, comp);
        quickSort(array, p + 1, hi, comp);
    }
}