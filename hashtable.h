#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
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

        this->upper = A.size();
        this->lower = A.size() * 100 * 100 / (r * r);
    }

    void _resize(int n)
    {
        if (this->lower >= n || n >= this->upper)
        {
            int f = this->r / 100;
            if (this->r % 100)
            {
                f += 1;
            }

            int m = std::max(n, 1) * f;
            std::vector<Set_from_Seq<T>> new_A(m);

            for (const T &x : this->chain_set)
            {
                int h = this->_hash(x.key, m);
                new_A[h].insert(x);
            }

            this->A = new_A;
            this->_compute_bounds();
        }
    }

    int _hash(int k, int m)
    {
        return ((this->a * k) % this->p) % m;
    }

public:
    Hash_Table_Set(int r = 200) : r(r), size(0), p(2147483647)
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

    public:
        Iterator(typename Set_from_Seq<T>::Iterator iter, typename std::vector<Set_from_Seq<T>>::const_iterator set_iter)
            : it(iter), set_it(set_iter) {}

        T operator*() const
        {
            return *this->it;
        }

        Iterator &operator++()
        {
            ++this->it;
            while (this->it == this->set_it->end())
            {
                ++this->set_it;
                if (this->set_it != this->set_it->end())
                {
                    this->it = this->set_it->begin();
                }
            }
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return this->it != other.it || this->set_it != other.set_it;
        }
    };

    Iterator begin() const
    {
        if (!this->A.empty())
        {
            return Iterator(this->chain_set.begin(), this->A.begin());
        }
        return end();
    }

    Iterator end() const
    {

        return Iterator(this->chain_set.end(), this->A.end());
    }

    void build(const std::vector<T> &X)
    {
        for (const T &x : X)
        {
            this->insert(x);
        }
    }

    bool find(int k) const
    {
        int h = this->_hash(k, this->A.size());
        return this->A[h].find(k);
    }

    bool insert(const T &x)
    {
        this->_resize(this->size + 1);
        int h = this->_hash(x, this->A.size());
        bool added = this->A[h].insert(x);
        if (added)
        {
            this->size++;
        }
        return added;
    }

    T remove(int k)
    {
        assert(this->size > 0);
        int h = this->_hash(k, this->A.size());
        T x = this->A[h].remove(k);
        this->size--;
        this->_resize(this->size);
        return x;
    }

    T find_min() const
    {
        T out;

        for (const T &x : this->chain_set)
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

        for (const T &x : this->chain_set)
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

        for (const T &x : this->chain_set)
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

        for (const T &x : this->chain_set)
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
            return this->current;
        }

        IteratorOrder &operator++()
        {
            this->current = this->hash_table->find_next(this->current.key);
            return *this;
        }

        bool operator!=(const IteratorOrder &other) const
        {
            return this->current != other.current;
        }

        bool isEnd() const
        {
            return this->current.isNull();
        }
    };

    IteratorOrder iter_order() const
    {
        return IteratorOrder(this);
    }
};