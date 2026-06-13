#pragma once
#include<iostream>
#include"avl.hpp"
// Khoi tao 1 struct gom mot root co kieu du lieu la cay avl, va cap kich thuoc cho set
template<typename T>
struct myset{
    Node<T>* root;
    int sz;
};
template<typename T>
// Khoi tao mot set rong
myset<T>* initSet(){
    myset<T>* s = new myset<T>();
    s->root = NULL;
    s->sz =0;
    return s;
}
template<typename T>
// Kiem tra co ton tai val trong set chua
bool contain(myset<T>* s, T val){
    if(!s)return false;
    return search(s->root,val);
}
template<typename T>
// Neu set chua khoi tao thi khoi tao set. Neu khong thi tiep tuc kiem tra trong set co ton tai val khong, neu khong co moi them vao set
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
//  Giai phong vung nho cua set
void clearSet(myset<T>* s){
    if(!s)return;
    clearTree(s->root);
    delete s;
}
