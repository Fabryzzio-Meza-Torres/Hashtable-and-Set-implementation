#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class Set_from_Seq
{
private:
    Linked_List_Seq<T> A;

public:
    int len()
    {
        return A.len();
    }
    void build(vector<T> X)
    {
        for (int x; x < X.size(); x++)
        {
            insert(x);
        }
    }
    void insert(int x)
    {
        A.insert(x);
    }
    void deletee(int i)
    {
        A.deletee(i);
    }
    T find_min()
    {
        return A.find_min();
    }
    T find_max()
    {
        return A.find_max();
    }
    T find_next(int i)
    {
        return A.find_next(i);
    }
    T find_prev(int i)
    {
        return A.find_prev(i);
    }
    T iter_oder(int i)
    {
        return A.iter_oder(i);
    }
};

template <class T>
class Hash_Table_Set
{
private:
    vector<T> A;
    Set_from_Seq<Linked_List_Seq<T>> chain_set;
    int size = 0;
    int r;
    int p;
    int a;
    int upper;
    int lower;
    int f;

    void compute_bound()
    {
        upper = A.size();
        lower = A.size() * 100 * 100;
    }
    void resize(int n)
    {
        if (lower >= n || n >= upper)
        {
            f = r / 100;
            if (r % 100 != 0)
            {
                f += 1;
            }
            int m = max(n, 1) * f;
            A = chain_set.chain_set(m);
            for (int x; x < A.size(); x++)
            {
                int h = hash(x, m);
                A[h].insert(x);
            }
            A = A;
            compute_bound();
        }
    }

public:
    int len()
    {
        return A.size();
    }
    T iter()
    {
        for (int i = 0; i < A.size(); i++)
        {
            for (int j = 0; j < A[i].len(); j++)
            {
                return A[i].iter_oder(j);
            }
        }
    }
    void build(vector<T> X)
    {
        for (int x; x < X.size(); x++)
        {
            insert(x);
        }
    }

    int hash(int k, int m)
    {
        return ((this->a * k) % this->p) % m;
    }
    T find(int k)
    {
        int h = hash(k, A.size());
        return A[h].find(k);
    }
    T insert(T x)
    {
        resize(A.size() + 1);
        int h = hash(x, A.size());
        T added = A[h].insert(x);
        if (added)
        {
            r++;
        }
        return added;
    }
    T deletee(int k)
    {
        assert(len() > 0);
        int h = hash(k, len());
        T deleted = A[h].deletee(k);
        size--;
        this->resize(A.size());
        return deleted;
    };
    T find_min()
    {
        T out;
        for (int i = 0; i < A.size(); i++)
        {
            if (out = None || A[i].find_min() < out)
            {
                out = A[i].find_min();
                break;
            }
        }
    };
    T find_max()
    {
        T out;
        out = nullptr;
        for (int i = 0; i < A.size(); i++)
        {
            if (out = NULL || A[i].find_max() > out)
            {
                out = A[i].find_max();
                break;
            }
        }
        return out;
    };
    T find_next()
    {
        T out;
        out = NULL;
        for (int i = 0; i < A.size(); i++)
        {
            if (out = NULL || A[i].find_next() > out)
            {
                out = A[i].find_next();
                break;
            }
        }
        return out;
    };
    T find_prev(int k)
    {
        T out = None;
        for (int x = 0; x < A.size(); x++)
        {
            if (A[x].find_prev() > k)
            {
                if (out == None || find_prev(A[x]) > out)
                    out = x;
            }
        }
        return out;
    };
    T iter_oder()
    {
        int x = A.find_min();
        while (x != NULL)
        {
        }
    };
};
int main()
{
}
