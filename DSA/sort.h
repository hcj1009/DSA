#pragma once
#include <functional>
#include <algorithm>

using std::swap;
using std::less;

template <class T,
    class Compare = less<T>>
bool isSorted(T array[],
    const int & lo,
    const int & hi,
    Compare comp = Compare())
{
    for (int i = lo; i < hi; i++)
    {
        if (!comp(array[i], array[i + 1]))
        {
            return false;
        }
    }
    return true;
}

/*
* Selection sort.
*/
template <class T,
    class Compare = less<T>>
void selectionSort(T array[],
    const int & lo,
    const int & hi,
    Compare comp = Compare())
{
    for (int i = lo; i < hi; i++)
    {
        int min = i;
        for (int j = i + 1; j <= hi; ++j)
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

/*
 * Insertion sort.
 */
template <class T,
    class Compare = less<T>>
void insertionSort(T array[],
    const int & lo,
    const int & hi,
    Compare comp = Compare())
{
    for (int i = lo; i <= hi; i++)
    {
        for (int j = i; j > 0; j--)
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

/*
 * Quick sort.
 */
template <class T,
    class Compare = less<T>>
int partition(T array[],
    const int & lo,
    const int & hi,
    Compare comp = Compare())
{
    int i = lo;
    for (int j = lo; j < hi; j++)
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
    const int & lo,
    const int & hi,
    Compare comp = Compare())
{
    if (lo < hi)
    {
        int p = partition(array, lo, hi, comp);
        quickSort(array, lo, p - 1, comp);
        quickSort(array, p + 1, hi, comp);
    }
}