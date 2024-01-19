#include <iostream>
#include <vector>
#include <algorithm>
#include "Linked_Lists.h"
#include "hashtable.h"
using namespace std;

int main()
{

    Hash_Table_Set<int> hashTable;

    hashTable.insert(5);
    hashTable.insert(3);
    hashTable.insert(7);
    hashTable.insert(10);

    cout << "Iterating:" << endl;
    for (int x : hashTable)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "Iterating in order:" << endl;
    Hash_Table_Set<int>::IteratorOrder it = hashTable.iter_order();
    while (!it.isEnd())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    return 0;
}
