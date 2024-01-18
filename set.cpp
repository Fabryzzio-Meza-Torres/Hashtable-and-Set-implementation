#include <iostream>
using namespace std;
template<typename T>
class Set
{
private:
//TODO: atributos
public:
    Set();
    void Insert(T data);
    bool Remove(T data);
    bool Contains(T data);
    Set Union(const Set &other);
    Set Intersect(const Set &other);
    Set Difference(const Set &other);
    ~Set();
};
int main(){

}