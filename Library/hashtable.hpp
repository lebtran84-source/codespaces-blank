#pragma once
#include <iostream>
#include "AVL.hpp"
using namespace std;
using ll = long long;
template<typename K, typename V>
struct hashTable {
    Node<pair<K,V>>** table;
    int capacity;
    int cnt;
};
// Tinh vi tri trong bang bam tu gia tri key
//  cho int, float, double, long long, char
template<typename V>//error
int gethash(hashTable<int,V>* htable, int key){
    ll h = key;
    return (int)((ll)h % htable->capacity + htable->capacity) % htable->capacity;
}
template<typename V>
int gethash(hashTable<long long,V>* htable, long long key){
    ll h = key;
    return (int)(h % htable->capacity + htable->capacity) % htable->capacity;
}
// cho string
template<typename V>
int gethash(hashTable<string,V>* htable, string key){
    long long h = 0;
    for(char c: key){
        h = (h*31 + c)% htable->capacity;
    }
    return (int)h;
}
// Tim Node co gia tri key va tra ve Node do
template<typename K, typename V>
Node<pair<K,V>>* findNode(Node<pair<K,V>>* root, K key){
    if(!root)return NULL;
    if(root->key.first == key) return root;
    if(key < root->key.first) return findNode<K,V>(root->left,key);
    return findNode<K,V>(root->right,key);
}
// Them key-val vao bang bam, neu da ton tai key thi cap nhat value
template<typename K, typename V>
void insert(hashTable<K,V>* htable, K key, V val){
    int idx = gethash(htable,key);
    Node<pair<K,V>> * p = findNode<K,V>(htable->table[idx],key);
    if(p){
        p->key.second=val;
        return;
    }
    htable->table[idx] = insert<pair<K,V>>(htable->table[idx],{key,val});
    htable->cnt ++;
}
// Xoa phan tu co key khoi bang bam neu co ton tai
template<typename K, typename V>
void remove(hashTable<K,V>* htable, K key){
    int idx = gethash(htable,key);
    Node<pair<K,V>> * p = findNode<K,V>(htable->table[idx],key);
    if(p){
        htable->table[idx] = deleteNode<pair<K,V>>(htable->table[idx],{key,p->key.second});
        htable->cnt --;
    }
    else return;
}
// Tra ve con tro toi Node co value cua key
template<typename K, typename V>
V* find(hashTable<K,V>* htable, K key){
    int idx = gethash<K,V>(htable,key);
    Node<pair<K,V>> * p = findNode<K,V>(htable->table[idx],key);
    if(!p)return NULL;
    return & p->key.second;
}
// Kiem tra xem co ton tai key trong bang bam khong
template<typename K, typename V>
bool contains(hashTable<K,V> * htable, K key){
    int idx = gethash(htable,key);
    Node<pair<K,V>> * p = findNode<K,V>(htable->table[idx],key);
    return p!=NULL;
}
// Tra ve so luong phan tu hien co trong toan bo bang bam
template<typename K, typename V>
int size(hashTable<K,V> * htable){
    return htable->cnt;
}
// Tao bang bam voi so phan tu bang bam toi da la cap phan tu
template<typename K, typename V>
hashTable<K,V>* initHashTable(int cap){
    hashTable<K,V> * htable = new hashTable<K,V>();
    htable->capacity = cap;
    htable->cnt=0;
    htable->table = new Node<pair<K,V>>*[cap];
    for(int i = 0; i < cap; i++){
        htable->table[i] = NULL;
    }
    return htable;
}
// Xoa tat ca Node trong cay AVL
template<typename K, typename V>
void clearAVL(Node<pair<K,V>>* root){
    if(!root)return;
    clearAVL<K,V>(root->left);
    clearAVL<K,V>(root->right);
    delete root;
}
// Xoa toan bo bang bam
template<typename K, typename V>
void clear(hashTable<K,V>* htable){
    for(int i = 0; i < htable->capacity; i++){
        clearAVL<K,V>(htable->table[i]);
        htable ->table[i] = NULL;
    }
    htable->cnt =0;
}
// Giai phong bo nho khi xoa bang bam
template<typename K, typename V>
void clearHashTable(hashTable<K,V>* htable){
    clear<K,V>(htable);
    delete[] htable->table;
    delete htable;
}