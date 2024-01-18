#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<class T>
class Linked_List_Seq{
private:
    vector<T> A;
    int n;
public:
    Linked_List_Seq(){
        n = 0;
    }
    int len(){
        return n;
    }
    void build(vector<T>X){
        for (int x; x < X.size();x++) {
            insert(x);
        }
    }
    void insert(int x){
        A.push_back(x);
        n++;
    }
    void deletee(int i){
        A.erase(A.begin()+i);
        n--;
    }
    T find_min(){
        return *min_element(A.begin(), A.end());
    }
    T find_max(){
        return *max_element(A.begin(), A.end());
    }
    T find_next(int i){
        return A[i+1];
    }
    T find_prev(int i){
        return A[i-1];
    }
    T iter_oder(int i){
        return A[i];
    }
};

template<class T>
class Set_from_Seq {
private:
    Linked_List_Seq<T> A;
public:
    int len(){
        return A.len();
    }
    void build(vector<T>X){
        for (int x; x < X.size();x++) {
            insert(x);
        }
    }
    void insert(int x){
        A.insert(x);
    }
    void deletee(int i){
        A.deletee(i);
    }
    T find_min(){
        return A.find_min();
    }
    T find_max(){
        return A.find_max();
    }
    T find_next(int i){
        return A.find_next(i);
    }
    T find_prev(int i){
        return A.find_prev(i);
    }
    T iter_oder(int i){
        return A.iter_oder(i);
    }
};

template<class T>   
class Hash_Table_Set{
private:
    vector<T> A;
    Set_from_Seq<Linked_List_Seq<T>> chain_set;
    int size;
    int r;
    int p;
    int a;
    int upper;
    int lower;
    int f;

    void compute_bound(){
     upper = A.size();
     lower = A.size()*100*100;
    }
    void resize(int n){
        if(lower >= n || n >= upper){
            f = r/100;
            if(r % 100 !=0){
                f += 1;
            }
            int m = max(n,1)*f;
            A = chain_set.chain_set(m);
            for(int x; x < A.size();x++){
                int h = hash(x,m);
                A[h].insert(x);
            }
            A = A;
            compute_bound();
        }
    }


public:
    int len(){
        return A.size();
    }
    T iter (){
        for(int i=0; i < A.size(); i++){
            for(int j=0; j < A[i].len(); j++){
                return A[i].iter_oder(j);
                }
        }
    }
    void build(vector<T>X){
        for (int x; x < X.size();x++) {
            insert(x);
        }
    }

    int hash(int k, int m){
        return ((this->a * k) % this->p) %m;
    }
    T find(int k){
        int h = hash(k,A.size());
        return A[h].find(k);
    }
    T insert(T x){
        resize(A.size()+1);
        int h = hash(x,A.size());
        T added =A[h].insert(x);
        if(added){
            r++;
        }
        return added;

    }
    T delete(int k){
        assert(len() > 0);
        int h = hash(k,len());
        T deleted = A[h].delete(k);
        size--;
        this->resize(A.size());
        return deleted;
    };
    T find_min(){
        T out;
        for (int i = 0; i < A.size(); i++) {
            if( out = None || A[i].find_min() < out){
                out = A[i].find_min();
                break;
            }
        }
    };
    T find_max(){};
    T find_next(){};
    T find_prev(){};
    T iter_oder(){};
};
int main(){

}
