#include "Set.h"

template <typename T>
Set<T> intersection(Set<T> &a, Set<T> &b)
{
    Set c = Set<T>();
    for (int i = 0; i < a.size(); i++)
    {
        if (b.contains(a[i]))
        {
            c.add(a[i]);
        }
    }
    return c;
}

template <typename T>
Set<T> union_(Set<T> &a, Set<T> &b)
{
    Set c = Set<T>();
    for (int i = 0; i < a.size(); i++)
    {
        c.add(a[i]);
    }
    for (int i = 0; i < b.size(); i++)
    {
        c.add(b[i]);
    }
    return c;
}

template <typename T>
Set<T> difference(Set<T> &a, Set<T> &b)
{
    Set c = Set<T>();
    for (int i = 0; i < a.size(); i++)
    {
        if (!b.contains(a[i]))
        {
            c.add(a[i]);
        }
    }
    return c;
}