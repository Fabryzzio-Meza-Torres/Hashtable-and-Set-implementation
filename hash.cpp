#include <iostream>
#include <vector>
#include "Linked_Lists.h"
#include "hashtable.h"
using namespace std;

int main()
{
    // Ejemplo de uso de Linked_List_Seq
    Linked_List_Seq<int> linkedList;
    linkedList.insert_first(10);
    linkedList.insert_first(10);
    linkedList.insert_first(10);
    linkedList.insert_first(10);
    linkedList.insert_first(20);
    linkedList.insert_first(20);
    linkedList.insert_first(20);
    linkedList.insert_first(30);

    cout << "Linked List: ";
    for (const auto &element : linkedList)
    {
        cout << element << " ";
    }
    cout << "\n\n";

    // Ejemplo de uso de Set_from_Seq
    Set_from_Seq<int> set;
    set.insert(10);
    set.insert(20);
    set.insert(30);

    cout << "Set: ";
    for (const auto &element : set)
    {
        cout << element << " ";
    }
    cout << "\n\n";

    // Ejemplo de uso de Hash_Table_Set
    Hash_Table_Set<int> hashTable;

    vector<int> data = {15, 25, 35, 10, 20};
    hashTable.build(data);

    cout << "Hash Table Set: ";
    for (const auto &element : hashTable)
    {
        cout << element << " ";
    }
    cout << "\n\n";

    return 0;
}