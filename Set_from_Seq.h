#include <iostream>
#include <vector>
#include <algorithm>
#include "Linked_Lists.h"
#include <algorithm>
using namespace std;

template <typename T>
class Set_from_Seq {
private:
    Seq<T>S;
public:
    Set_from_Seq() : S() {}
    int size() const {
        return S.len();
    }
    void build(vector<T> A) {
        S.build(A);
    }
    void insert(T x) {
        for (int i = 0; i < S.len(); i++) {
            if (S.get_at(i).key == x.key) {
                S.set_at(i, x);
                return;
            }
        }
        S.insert_last(x);
    }
    T delete(T k) {
        for (int i = 0; i < S.len(); i++) {
            if (S.get_at(i).key == k) {
                S.delete_at(i);
                return S.get_at(i);
            }
        }
    }
    T find(T k) {
        for (int i = 0; i < S.len(); i++) {
            if (S.get_at(i).key == k) {
                return S.get_at(i);
            }
        }
        return NULL;
    }
    T find_min() {
        T out = NULL;
        for (int i = 0; i < S.len(); i++) {
            if (out == NULL || S.get_at(i).key < out.key) {
                out = S.get_at(i);
            }
        }
        return out;
    }
    T find_max() {
        T out = NULL;
        for (int i = 0; i < S.len(); i++) {
            if (out == NULL || S.get_at(i).key > out.key) {
                out = S.get_at(i);
            }
        }
        return out;
    }
    T find_next(T k) {
        T out = NULL;
        for (int i = 0; i < S.len(); i++) {
            if (S.get_at(i).key > k) {
                if (out == NULL || S.get_at(i).key < out.key) {
                    out = S.get_at(i);
                }
            }
        }
        return out;
    }
    T find_prev(T k) {
        T out = NULL;
        for (int i = 0; i < S.len(); i++) {
            if (S.get_at(i).key < k) {
                if (out == NULL || S.get_at(i).key > out.key) {
                    out = S.get_at(i);
                }
            }
        }
        return out;
    }
    void iter_ord() {
        T x = find_min();
        while (x) {
            cout << x.key << endl;
            x = find_next(x.key);
        }
    }
};

/*
def Set_from_Seq(seq):
    class set_from_seq:
    def __init__(self): self.S = seq()
    def __len__(self): return len(self.S)
    def __iter__(self): yield from self.S

    def build(self, A):
        self.S.build(A)
    def insert(self, x):
        for i in range(len(self.S)):
            if self.S.get_at(i).key == x.key:
                self.S.set_at(i, x)
                return
        self.S.insert_last(x)
    def delete(self, k):
        for i in range(len(self.S)):
            if self.S.get_at(i).key == k:
                return self.S.delete_at(i)
    def find(self, k):
        for x in self:
            if x.key == k: return x
        return None
    def find_min(self):
        out = None
        for x in self:
        if (out is None) or (x.key < out.key):
            out = x
        return out
    def find_max(self):
        out = None
        for x in self:
        if (out is None) or (x.key > out.key):
            out = x
        return out

    def find_next(self, k):
        out = None
        for x in self:
            if x.key > k:
                if (out is None) or (x.key < out.key):
                    out = x
        return out

    def find_prev(self, k):
        out = None
        for x in self:
            if x.key < k:
                if (out is None) or (x.key > out.key):
                out = x
        return out
    
    def iter_ord(self):
        x = self.find_min()
        while x:
            yield x
            x = self.find_next(x.key)
    return set_from_seq*/