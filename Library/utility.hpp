#pragma once
// Khoi tao struct cua 1 pair gom first va second
template<typename K, typename V>
struct pair{
    K first;
    V second;
    pair(){
        first = T1();
        second = T2();
    }
    pair(const K& t1, const V& t2){
        first = t1;
        second = t2;
    }
};
// Khoi tao pair
template<typename K, typename V>
pair<K,V> initPair(const K& t1, const V& t2){
    return pair<K,V>(t1,t2);
}
// Doi cho phan tu a va b
template<typename T>
void swap(T& a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}
