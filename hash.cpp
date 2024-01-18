#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template<class T>
class Hash_Table_Set{
private:
    vector<int>A;
    int r;
    int p;
    int a;
    int upper;
    int lower;
    int f;
public:
    //falta algunas funciones no esta al cien
    void init(int r = 200){
        //falta algunas cosas
        this->r = r;

    }
    int len(){

    }
    void build(vector<T>X){
        for (int x; x < X.size();x++) {
            insert(x);
        }
    }
    vector<int> chain_set(int m){
        for(int i=0; i < m; i++){
            A.push_back(i);
        }
        return A;
    }
    void resize(int n){
        if(lower >= n || n >= upper){
            f = r/100;
            if(r % 100 !=0){
                int m = max(n,1)*f;
                chain_set(m);
            }
        }

    }
    void insert(int x){

    }
    T hash(int k, int m){
        return ((this->a * k) % this->p) %m;
    }
    void compute_bound(){
     upper = A.size();
     lower = A.size()*100*100;
    }
    T deletee(){};
    T find_min(){};
    T find_max(){};
    T find_next(){};
    T find_prev(){};
    T iter_oder(){};
};
int main(){

}