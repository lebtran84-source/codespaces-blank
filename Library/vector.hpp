#pragma once
#include<iostream>
using namespace std;
template <typename T>
struct vector{
    T* v;
    int capacity, size;
    vector(){
        v =NULL;
        capacity =0;
        size =0;
    }
    ~vector(){
        delete []v;
    }
};
// Dung de cap phat lai bo nho khi bo nho bi day hay rong
template<typename T>
void reallocate(vector<T>& vec, int newcap){
    T* newv = new T[newcap];
    for(int i = 0;i < vec.size; i++){
        newv[i] = vec.v[i];
    }
    delete[] vec.v;
    vec.v = newv;
    vec.capacity = newcap;
}
// Them phan tu vao cuoi mang
template<typename T>
void push_back(vector<T>& vec, T val){
    if(vec.size == vec.capacity){
        int newcap;
        if(vec.capacity == 0)newcap =1;
        else newcap = vec.capacity*2;
        reallocate(vec,newcap);
    }
    vec.v[vec.size] = val;
    vec.size++;
}
// Xoa phan tu o cuoi mang
template<typename T>
void pop_back(vector<T>& vec){
    if(vec.size >0){
        vec.size--;
    }
}
// Lay ra phan tu co so thu tu la idx
template <typename T>
T atIdx(vector<T> & vec, int idx){
    if(idx < 0 || idx >= vec.size)cout<<"Out of range.\n";
    return vec.v[idx];
}
// Tra ve so phan tu hien co trong mang
template<typename T>
int size(vector<T> vec){
    return vec.size;
}
template<typename T>
bool empty(vector<T> vec){
    return sz == 0;
}