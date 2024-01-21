#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

template <class T>
struct Linked_List_Node
{
    T data;
    Linked_List_Node<T> *next;
    Linked_List_Node<T> *prev;

public:
    Linked_List_Node() : next(nullptr), prev(nullptr) {}
    Linked_List_Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    Linked_List_Node(T data, Linked_List_Node<T> *next) : data(data), next(next), prev(nullptr) {}
    Linked_List_Node(T data, Linked_List_Node<T> *next, Linked_List_Node<T> *prev) : data(data), next(next), prev(prev) {}

    Linked_List_Node<T> *later_node(int i)
    {
        if (i == 0 || this == nullptr)
        {
            return this;
        }
        assert(this->next != nullptr);
        return this->next->later_node(i - 1);
    }

    class iter
    {
        Linked_List_Node<T> *node;

    public:
        iter(Linked_List_Node<T> *ptr) : node(ptr) {}

        T operator*() const
        {
            if (node->data != T())
            {
                return node->data;
            }
            else
            {
                return T();
            }
        }

        iter &operator++()
        {
            node = node->next;
            return *this;
        }

        bool operator!=(const iter &other) const
        {
            return node != other.node;
        }

        bool operator==(const iter &other) const
        {
            return node == other.node;
        }
    };
};

template <typename T>
class Linked_List_Seq
{
protected:
    Linked_List_Node<T> *head = nullptr;
    int size = 0;

public:
    Linked_List_Seq() : head(nullptr), size(0) {}

    int len() const
    {
        return size;
    }

    typename Linked_List_Node<T>::iter begin() const
    {
        return typename Linked_List_Node<T>::iter(head);
    }

    typename Linked_List_Node<T>::iter end() const
    {
        return typename Linked_List_Node<T>::iter(nullptr);
    }

    template <typename Container>
    void build(Container &container)
    {
        for (auto &x : container)
        {
            insert_first(x);
        }
    }

    int get_at(int i) const
    {
        Linked_List_Node<T> *node = later_node(i);
        return node->data;
    }

    void set_at(int i, int x)
    {
        Linked_List_Node<T> *temp = later_node(i);
        temp->data = x;
    }

    void insert_first(int x)
    {
        Linked_List_Node<T> *newNode = new Linked_List_Node<T>(x);
        newNode->next = head;
        head = newNode;
        size++;
    }

    int delete_first()
    {
        int x = head->data;
        Linked_List_Node<T> *temp = head;
        head = head->next;
        delete temp;
        size--;
        return x;
    }

    void insert_at(int i, int x)
    {
        if (i == 0)
        {
            insert_first(x);
            return;
        }
        else
        {
            Linked_List_Node<T> *newNode = new Linked_List_Node<T>(x);
            Linked_List_Node<T> *temp = this->later_node(i - 1);
            newNode->next = temp->next;
            temp->next = newNode;
            size++;
        }
    }

    int delete_at(int i)
    {
        if (i == 0)
        {
            return delete_first();
        }
        else
        {
            Linked_List_Node<T> *temp = this->later_node(i - 1);
            int x = temp->next->data;
            Linked_List_Node<T> *temp2 = temp->next;
            temp->next = temp->next->next;
            delete temp2;
            size--;
            return x;
        }
    }

    void insert_last(int x)
    {
        insert_at(size, x);
    }

    int delete_last()
    {
        return delete_at(size - 1);
    }

    Linked_List_Node<T> *later_node(int i) const
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        return head->later_node(i);
    }
};

template <typename T>
class Set_from_Seq
{
public:
    Linked_List_Seq<T> Seq;

    Set_from_Seq<T>() : Seq() {}

    int size() const
    {
        return Seq.len();
    }

    class Iterator
    {
    public:
        typename Linked_List_Node<T>::iter it;

        Iterator(typename Linked_List_Node<T>::iter iter) : it(iter) {}

        T operator*() const
        {
            if (it != typename Linked_List_Node<T>::iter(nullptr))
            {
                return *it;
            }
            else
            {
                return T();
            }
        }

        Iterator &operator++()
        {
            ++it;
            return *this;
        }

        bool operator!=(const Iterator &other) const
        {
            return it != other.it;
        }

        bool operator==(const Iterator &other) const
        {
            return it == other.it;
        }
    };

    friend class Iterator;

    template <typename Container>
    void build(Container &container)
    {
        Seq.build(container);
    }

    Iterator begin() const
    {
        return Iterator(Seq.begin());
    }

    Iterator end() const
    {
        return Iterator(Seq.end());
    }

    void insert(const T &x)
    {
        for (int i = 0; i < Seq.len(); i++)
        {
            if (Seq.get_at(i) == x)
            {
                Seq.set_at(i, x);
                return;
            }
        }
        Seq.insert_first(x);
    }

    bool empty() const
    {
        return Seq.len() == 0;
    }
};

#endif // LINKED_LISTS_H