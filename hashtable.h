#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "Linked_Lists.h"
#include "hashtable.h"

template <typename T>
class Hash_Table_Set
{
private:
    Set_from_Seq<T> chain_set;
    std::vector<Set_from_Seq<T>> A;
    int size;
    int r;
    int p;
    int a;
    int upper;
    int lower;

    void _compute_bounds()
    {
        this->upper = A.size();
        this->lower = A.size() * 100 * 100 / (r * r);
    }

    void _resize(int n)
    {
        if (this->lower >= n || n >= this->upper)
        {
            int f = this->r / 100;
            f += (this->r % 100) ? 1 : 0;

            int m = std::max(n, 1) * f;
            std::vector<Set_from_Seq<T>> new_A(m);

            for (const T &x : this->chain_set)
            {
                int h = this->_hash(x, m);
                new_A[h].insert(x);
            }

            this->A = new_A;
            this->_compute_bounds();
        }
    }

    int _hash(T k, int m) const
    {
        return ((this->a * k) % this->p) % m;
    }

public:
    Hash_Table_Set(int r = 200) : r(r), size(0), p(3647)
    {
        this->a = rand() % (this->p - 1) + 1;
        this->_compute_bounds();
        this->_resize(0);
    }

    int len() const
    {
        return this->size;
    }

    class Iterator
    {
    private:
        typename Set_from_Seq<T>::Iterator it;
        typename std::vector<Set_from_Seq<T>>::const_iterator set_it;
        const Hash_Table_Set<T> *hash_table;

    public:
        Iterator(typename Set_from_Seq<T>::Iterator iter, typename std::vector<Set_from_Seq<T>>::const_iterator set_iter, const Hash_Table_Set<T> *ht)
            : it(iter), set_it(set_iter), hash_table(ht) {}

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
                if (set_it != hash_table->A.end())
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
            return Iterator(A[0].begin(), A.begin(), this);
        }
        return end();
    }

    Iterator end() const
    {
        return Iterator(Set_from_Seq<T>().end(), A.end(), this);
    }

    void build(const std::vector<T> &X)
    {
        for (const T &x : X)
        {
            insert(x);
        }
    }

    bool find(T k) const
    {
        int h = _hash(k, A.size());
        return A[h].find(k);
    }

    bool insert(const T &x)
    {
        _resize(size + 1);
        int h = _hash(x, A.size());
        A[h].insert(x);
        size++;
        chain_set.insert(x);
        return true;
    }

    T remove(T k)
    {
        assert(size > 0);
        int h = _hash(k, A.size());
        T x = A[h].remove(k);
        size--;
        _resize(size);
        chain_set.build(A);
        return x;
    }

    T find_min() const
    {
        T out;

        for (const T &x : chain_set)
        {
            if (out.isNull() || (x < out))
            {
                out = x;
            }
        }
        return out;
    }

    T find_max() const
    {
        T out;

        for (const T &x : chain_set)
        {
            if (out.isNull() || (x > out))
            {
                out = x;
            }
        }
        return out;
    }

    T find_next(T k) const
    {
        T out;

        for (const T &x : chain_set)
        {
            if (x > k)
            {
                if (out.isNull() || (x < out))
                {
                    out = x;
                }
            }
        }
        return out;
    }

    T find_prev(T k) const
    {
        T out;

        for (const T &x : chain_set)
        {
            if (x < k)
            {
                if (out.isNull() || (x > out))
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
            current = hash_table->find_next(current);
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

#endif // MY_HEADER_H