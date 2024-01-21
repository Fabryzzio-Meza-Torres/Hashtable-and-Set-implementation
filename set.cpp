#include <iostream>
#include <vector>
#include <algorithm>
#include "hashtable.h"

using namespace std;

template <typename T>
class Set
{
private:
    Hash_Table_Set<T> hashTable;

public:
    Set() {}

    void Insert(T data)
    {
        hashTable.insert(data);
    }

    bool Remove(T data)
    {
        return hashTable.remove(data);
    }

    bool Contains(T data)
    {
        return hashTable.find(data);
    }

    Set Union(const Set &other)
    {
        Set result;

        for (const T &element : *this)
        {
            result.Insert(element);
        }

        for (const T &element : other)
        {
            result.Insert(element);
        }

        return result;
    }

    Set Intersect(const Set &other)
    {
        Set result;

        for (const T &element : *this)
        {
            if (other.Contains(element))
            {
                result.Insert(element);
            }
        }

        return result;
    }

    Set Difference(const Set &other)
    {
        Set result;

        for (const T &element : *this)
        {
            if (!other.Contains(element))
            {
                result.Insert(element);
            }
        }

        return result;
    }

    ~Set() {}

    class Iterator
    {
    private:
        typename Hash_Table_Set<T>::IteratorOrder hashTableIterator;

    public:
        Iterator(const Hash_Table_Set<T> *hashTable) : hashTableIterator(hashTable->iter_order()) {}

        T operator*() const
        {
            return *hashTableIterator;
        }

        Iterator &operator++()
        {
            ++hashTableIterator;
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return hashTableIterator != other.hashTableIterator;
        }
    };

    Iterator begin() const
    {
        return Iterator(&hashTable);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }
};

int main()
{
    Set<int> set1;
    set1.Insert(1);
    set1.Insert(2);
    set1.Insert(3);

    Set<int> set2;
    set2.Insert(2);
    set2.Insert(3);
    set2.Insert(4);

    Set<int> unionSet = set1.Union(set2);
    Set<int> intersectSet = set1.Intersect(set2);
    Set<int> differenceSet = set1.Difference(set2);

    cout << "Set 1: ";
    for (const int &element : set1)
    {
        cout << element << " ";
    }
    cout << endl;

    cout << "Set 2: ";
    for (const int &element : set2)
    {
        cout << element << " ";
    }
    cout << endl;

    cout << "Union: ";
    for (const int &element : unionSet)
    {
        cout << element << " ";
    }
    cout << endl;

    cout << "Intersection: ";
    for (const int &element : intersectSet)
    {
        cout << element << " ";
    }
    cout << endl;

    cout << "Difference: ";
    for (const int &element : differenceSet)
    {
        cout << element << " ";
    }
    cout << endl;

    return 0;
}