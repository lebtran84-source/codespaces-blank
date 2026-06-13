#pragma once
#include "avl.hpp"
#include "utility.hpp"
template<typename K, typename V>
// Khoi tao struct mymap gom mot root co cau truc du lieu la cac node cay avl va moi node mang kieu du lieu pair, va dem so phan tu hien co trong map.
struct mymap{
    Node<pair<K,V>>* root;
    int sz;
};
template<typename K, typename V>
// Khoi tao mymap
mymap<K,V>* initMap(){
    mymap<K,V>* mp = new mymap<K,V>();
    mp->root =NULL;
    mp->sz =0;
    return mp;
}
template<typename K, typename V>
// Tra ve node can tim chua key
Node<pair<K,V>>* findNodeMap(Node<pair<K,V>>* root, K key){
    if(!root)return NULL;
    if(root->key.first == key)return root;
    if(key < root->key.first){
        return findNodeMap<K,V>(root->left,key);
    }
    return findNodeMap<K,V>(root->right,key);
}
template<typename K, typename V>
// Kiem tra xem map co ton tai node co gia tri key khong
bool containMap(mymap<K,V>* mp, K key){
    if(!mp)return false;
    return findNodeMap(mp->root,key)!=NULL;
}
template<typename K, typename V>
// Neu map chua khoi tao thi khoi tao. Sau do, kiem tra xem map co ton tai node co key do chua, neu co roi thi cho gia tri cua node do bang val.
// Neu khong tim thay node do thi insert vao theo kieu cau truc cay avl, sau do, tang kich thuoc map.
void insertMap(mymap<K,V>*& mp, K key, V val){
    if(!mp){
        mp = initMap<K,V>();
    }
    Node<pair<K,V>>* found = findNodeMap(mp->root,key);
    if(found){
        found->key.second = val;
    }
    else{
        pair<K,V> p(key,val);
        mp->root = insert(mp->root,p);
        mp->sz ++;
    }
}
template<typename K, typename V>
// Tra ve con tro den gia tri cua phan tu chua key trong map.
V* valueMap(mymap<K,V>* mp, K key){
    if(!mp)return NULL;
    Node<pair<K,V>>* found = findNodeMap(mp->root,key);
    if(found){
        return & found->key.second;
    }
    return NULL;
}
template<typename K, typename V>
// Xoa phan tu co chua key trong map.
void removeMap(mymap<K,V>* mp, K key){
    if(!mp)return;
    Node<pair<K,V>>* found = findNodeMap(mp->root,key);
    if(found){
        mp->root = deleteNode(mp->root,found->key);
        mp->sz--;
    }
}
template<typename K, typename V>
// Giai phong vung nho cho map
void clearMap(mymap<K,V> *mp){
    if(!mp)return;
    clearTree(mp->root);
    delete mp;
}
