#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
struct Linked_List_Node
{
    T data;
    Linked_List_Node<T> *next;
    Linked_List_Node<T> *prev;

public:
    Linked_List_Node() : next(nullptr), prev(nullptr) {}
    Linked_List_Node(T data)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
    Linked_List_Node(T data, Linked_List_Node<T> *next)
    {
        this->data = data;
        this->next = next;
        this->prev = nullptr;
    }
    Linked_List_Node(T data, Linked_List_Node<T> *next, Linked_List_Node<T> *prev)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
    Linked_List_Node *later_node(int i)
    {
        if (i == 0)
        {
            return this;
        }
        assert(this->next != nullptr);
        return this->next->later_node(i - 1);
    }
};

template <typename T, typename Container>
class Linked_List_Seq
{
protected:
    Linked_List_Node<T> *head = nullptr;
    int size = 0;

public:
    Linked_List_Seq() : head(nullptr), size(0);
    ~Linked_List_Seq()
    {
        Linked_List_Node<T> *newNode = head;
        while (head != nullptr)
        {
            Linked_List_Node<T> *temp = newNode;
            newNode = newNode->next;
            delete temp;
        }
    }
    int len()
    {
        return size;
    }

    class iter
    {
        Linked_List_Node<T> *node;
        iter(Linked_List_Node<T> *ptr) : node(ptr) {}
        int operator*() const
        {
            return node->data;
        }
        iter &operator++()
        {
            node = node->next;
            return *this:
        }
        bool operator!=(const iter &other) const
        {
            return node != other.node;
        }
    };

    void build(Container % container)
    {
        for (auto &x : container)
        {
            insert_first(x);
        }
    }

    int get_at(int i)
    {
        Linked_List_Node<T> *temp = later_node(i);
        return node->data;
    }

    void set_at(int i, int x)
    {
        Linked_List_Node<T> *temp = later_node(i);
        temp->data = x;
    }

    void insert_first(int x)
    {
        Linked_List_Node *newNode = Linked_List_Node(x);
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
            Linked_List_Node<T> *newNode = new Linked_List_Node(x);
            Linked_List_Node<T> *temp = later_node(i - 1);
            newNode->next = temp->next;
            temp->next = newNode;
            size++;
        }
    }
    int delete_at(int i)
    {
        if (i == 0)
        {
            delete_first();
            return;
        }
        else
        {
            Linked_List_Node<T> *temp = later_node(i - 1);
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
        return;
    }

    int delete_last()
    {
        delete_at(size - 1);
        return;
    }
};
