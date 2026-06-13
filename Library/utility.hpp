#pragma once
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
template<typename K, typename V>
pair<K,V> initPair(const K& t1, const V& t2){
    return pair<K,V>(t1,t2);
}
template<typename T>
void swap(T& a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}