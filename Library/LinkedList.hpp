#pragma once
#include<iostream>
using namespace std;
template<typename T>
struct Node{
    T key;
    Node* next;
    Node(T val){
        key = val;
        next = NULL;
    }
};
template<typename T>
// Tra ve Node head cua cay da them phan tu gia tri val vao dau danh sach lien ket
    Node<T>* insertFront(Node<T>* root, T val){
        if(!root){
            return new Node(val);
        }
        Node* p = new Node(val);
        p->next = root;
        return p;
    }
template<typename T>
 // Tra ve Node head cua cay da them phan tu gia tri val vao cuoi danh sach lien ket
    Node<T>* insertBack(Node<T>* root, T val){
        if(!root){
            return new Node(val);
        }
        Node* cur = root;
        while(cur->next)cur = cur->next;
        cur->next = new Node(val);
        return root;
    }
template<typename T>//Error
// Tra ve Node head cua cay da them phan tu vao vi tri thu i (chi so index bat dau tu 0)
    Node<T>* insertAt(Node<T>* root, T val, int index){// index based-0
        if(index == 0)return insertFront<T>(root,val);
        if(!root){
            cout<<"index out of range\n";
            return root;
        }
        Node<T>* cur = root;
        int step = index -1;
        while(cur->next && step > 0){
            cur = cur->next;
            step--;
        }
        if(step > 0){
            cout<<"index out of range\n";
            return root;
        }
        Node<T>* p= new Node(val);
        Node<T>* tmp = cur->next;
        p->next = tmp;
        cur->next = p;
        return root;
    }
template<typename T>
// Tra ve Node head cua cay da xoa phan tu gia tri val
    Node<T>* remove(Node<T>* root, T val){
        if(!root)return NULL;
        if(root->key == val){
            Node<T>* p = root;
            root = root->next;
            delete p;
            return root;
        }
        Node<T>* cur = root;
        while(cur->next && cur->next->key != val)cur = cur->next;
        if(cur->next){
            Node<T>* p = cur->next;
            cur->next = cur->next->next;
            delete p;
        }
        return root;
    }
template<typename T>
// Tra ve Node head cua cay da xoa phan tu tai vi tri thu i (theo index bat dau tu 0)
    Node<T>* removeAt(Node<T>* root, int index){
        if(!root || index < 0)return NULL;
        if(index == 0){
            Node<T>* p = root;
            root = root->next;
            delete p;
            return root;
        }
        Node<T>* cur = root;
        while(cur->next && index > 1){
            cur = cur->next;
            index--;
        }
        if(cur->next){
            Node<T>* p = cur->next;
            cur->next = cur->next->next;
            delete p;
        }
        return root;
    }
template<typename T>
// Tra ve chi so cua phan tu do trong danh sach lien ket
    int find(Node<T>* root, T val){
        int index = 0;
        for(Node<T>* p = root; p!=NULL; p = p->next){
            if(p->key != val) index ++;
            else return index;
        }
        return -1;
    }
template<typename T>
// Tra ve so phan tu hien co trong danh sach lien ket don
    int size(Node<T>* root){
        if(!root)return 0;
        int len = 0;
        for(Node<T>* p = root; p != NULL; p=p->next)len ++;
        return len;
    }
template<typename T>
// Tra ve Node head cua danh sach lien ket don da duoc dao nguoc
    Node<T>* reverseList(Node<T>* root){
        if(!root)return NULL;
        Node<T>* pre = NULL;
        Node<T>* cur = root;
        while(cur){
            Node<T>* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        root = pre;
        return root;
    }