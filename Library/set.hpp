#pragma once
#include<iostream>
#include"avl.hpp"
template<typename T>
struct myset{
    Node<T>* root;
    int sz;
};
template<typename T>
myset<T>* initSet(){
    myset<T>* s = new myset<T>();
    s->root = NULL;
    s->sz =0;
    return s;
}
template<typename T>
bool contain(myset<T>* s, T val){
    if(!s)return false;
    return search(s->root,val);
}
template<typename T>
void insertSet(myset<T>*& s, T val){
    if(!s){
        s = new myset<T>();
    }
    if(!contain(s,val)){
        s->root = insert(s->root,val);
        s->sz ++;
    }
}
template<typename T>
void clearSet(myset<T>* s){
    if(!s)return;
    clearTree(s->root);
    delete s;
}