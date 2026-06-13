#pragma once
#include "avl.hpp"
#include "utility.hpp"
template<typename K, typename V>
struct mymap{
    Node<pair<K,V>>* root;
    int sz;
};
template<typename K, typename V>
mymap<K,V>* initMap(){
    mymap<K,V>* mp = new mymap<K,V>();
    mp->root =NULL;
    mp->sz =0;
    return mp;
}
template<typename K, typename V>
Node<pair<K,V>>* findNodeMap(Node<pair<K,V>>* root, K key){
    if(!root)return NULL;
    if(root->key.first == key)return root;
    if(key < root->key.first){
        return findNodeMap<K,V>(root->left,key);
    }
    return findNodeMap<K,V>(root->right,key);
}
template<typename K, typename V>
bool containMap(mymap<K,V>* mp, K key){
    if(!mp)return false;
    return findNodeMap(mp->root,key)!=NULL;
}
template<typename K, typename V>
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
V* valueMap(mymap<K,V>* mp, K key){
    if(!mp)return NULL;
    Node<pair<K,V>>* found = findNodeMap(mp->root,key);
    if(found){
        return & found->key.second;
    }
    return NULL;
}
template<typename K, typename V>
void removeMap(mymap<K,V>* mp, K key){
    if(!mp)return;
    Node<pair<K,V>>* found = findNodeMap(mp->root,key);
    if(found){
        mp->root = deleteNode(mp->root,found->key);
        mp->sz--;
    }
}
template<typename K, typename V>
void clearMap(mymap<K,V> *mp){
    if(!mp)return;
    clearTree(mp->root);
    delete mp;
}