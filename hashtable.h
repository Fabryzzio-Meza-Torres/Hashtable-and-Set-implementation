#include <iostream>
#include <vector>
#include <algorithm>
#include "Linked_Lists.h"
using namespace std;

template <class T>

class Hash_Table_Set
{
private:
    Set_from_Seq<T> chain_set;
    std::vector<Set_from_Seq<T>> A;
    int size;
    int r;
    int p;
    int a;

    void _compute_bounds()
    {
        upper = A.size();
        lower = A.size() * 100 * 100 / (r * r);
    }

    void _resize(int n)
    {
        if (lower >= n || n >= upper)
        {
            int f = r / 100;
            if (r % 100)
            {
                f += 1;
            }

            int m = std::max(n, 1) * f;
            std::vector<Set_from_Seq<T>> new_A(m);

            for (const T &x : *this)
            {
                int h = _hash(x.key, m);
                new_A[h].insert(x);
            }

            A = new_A;
            _compute_bounds();
        }
    }

    int _hash(int k, int m)
    {
        return ((a * k) % p) % m;
    }

public:
    Hash_Table_Set(int r = 200) : r(r), size(0), p(2147483647)
    {
        a = rand() % (p - 1) + 1;
        _compute_bounds();
        _resize(0);
    }

    int len() const
    {
        return size;
    }

    class Iterator
    {
    private:
        typename Set_from_Seq<T>::Iterator it;
        typename std::vector<Set_from_Seq<T>>::const_iterator set_it;

    public:
        Iterator(typename Set_from_Seq<T>::Iterator iter, typename std::vector<Set_from_Seq<T>>::const_iterator set_iter)
            : it(iter), set_it(set_iter) {}

        T operator*() const
        {
            return *it;
        }

        Iterator &operator++()
        {
            ++it;
            while (it == set_it->end())
            {
                ++set_it;
                if (set_it != set_it->end())
                {
                    it = set_it->begin();
                }
            }
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return it != other.it || set_it != other.set_it;
        }
    };

    Iterator begin() const
    {
        if (!A.empty())
        {
            return Iterator(A[0].begin(), A.begin());
        }
        return end();
    }

    Iterator end() const
    {
        return Iterator(Set_from_Seq<T>::Iterator(nullptr), A.end());
    }

    void build(const std::vector<T> &X)
    {
        for (const T &x : X)
        {
            insert(x);
        }
    }

    bool find(int k) const
    {
        int h = _hash(k, A.size());
        return A[h].find(k);
    }

    bool insert(const T &x)
    {
        _resize(size + 1);
        int h = _hash(x.key, A.size());
        bool added = A[h].insert(x);
        if (added)
        {
            size++;
        }
        return added;
    }

    T remove(int k)
    {
        assert(size > 0);
        int h = _hash(k, A.size());
        T x = A[h].remove(k);
        size--;
        _resize(size);
        return x;
    }

    T find_min() const
    {
        T out;
        for (const T &x : *this)
        {
            if (out.isNull() || (x.key < out.key))
            {
                out = x;
            }
        }
        return out;
    }

    T find_max() const
    {
        T out;
        for (const T &x : *this)
        {
            if (out.isNull() || (x.key > out.key))
            {
                out = x;
            }
        }
        return out;
    }

    T find_next(int k) const
    {
        T out;
        for (const T &x : *this)
        {
            if (x.key > k)
            {
                if (out.isNull() || (x.key < out.key))
                {
                    out = x;
                }
            }
        }
        return out;
    }

    T find_prev(int k) const
    {
        T out;
        for (const T &x : *this)
        {
            if (x.key < k)
            {
                if (out.isNull() || (x.key > out.key))
                {
                    out = x;
                }
            }
        }
        return out;
    }

    class IteratorOrder
    {
    private:
        const Hash_Table_Set<T> *hash_table;
        T current;

    public:
        IteratorOrder(const Hash_Table_Set<T> *ht) : hash_table(ht), current(ht->find_min()) {}

        T operator*() const
        {
            return current;
        }

        IteratorOrder &operator++()
        {
            current = hash_table->find_next(current.key);
            return *this;
        }

        bool operator!=(const IteratorOrder &other) const
        {
            return current != other.current;
        }

        bool isEnd() const
        {
            return current.isNull();
        }
    };

    IteratorOrder iter_order() const
    {
        return IteratorOrder(this);
    }
};
