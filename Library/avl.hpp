#pragma once
#include<iostream>
using namespace std;
template<typename T>
struct Node{
    T key;
    Node *left, *right;
    int balance;
    int height;
    Node(T data){
        key = data;
        left = NULL;
        right = NULL;
        balance = 0;
        height = 1;
    }
};
template<typename T>
// Tra ve kieu du lieu so nguyen la chieu cao cua cay 
int getheight(Node<T>* root){
        if(!root)return 0;
        return root->height;
    }
template<typename T>
// Ham nay dung de cap nhat chieu cao cua mot node va chi so can bang (= chieu cao cay con phai tru cay con trai)
void update(Node<T> * root){
        int heightleft = getheight<T>(root->left);
        int heightright = getheight<T>(root->right);
        root->balance = heightright - heightleft;
        root->height = max<int>(heightleft, heightright) +1;
    }
template<typename T>
// Tra ve Node root cua cay da duoc xoay trai
    Node<T>* rotateLeft(Node<T>* root){
        Node<T>* y = root->right;
        root->right = y->left;
        y->left = root;
        update<T>(root);
        update<T>(y);
        return y;
    }
template<typename T>
// Tra ve Node root cua cay da duoc xoay phai
    Node<T>* rotateRight(Node<T>* root){
        Node<T>* x = root->left;
        root->left= x->right;
        x->right = root;
        update<T>(root);
        update<T>(x);
        return x;
    }
template<typename T>
// Tra ve root cua cay da duoc can bang
    Node<T>* balancedTree(Node<T>* root){
        if(!root)return NULL;
        update(root);
        // left left
        if(root->balance < -1 && root->left && root->left->balance <= 0){
            return rotateRight<T>(root);
        }
        // left right
        if(root->balance < -1 && root->left && root->left->balance > 0){
            root->left = rotateLeft<T>(root->left);
            return rotateRight<T>(root);
        }
        // right right
        if(root->balance > 1 && root->right && root->right->balance >= 0){
            return rotateLeft<T>(root);
        }
        // right left
        if(root->balance > 1 && root->right && root->right->balance < 0){
            root->right = rotateRight<T>(root->right);
            return rotateLeft<T>(root);
        }
        return root;
    }
template<typename T>
// Them mot node vao cay 
    Node<T>* insert(Node<T>* root, T val){
        if(!root){
            return new Node(val);
        }
        if(val < root->key) root->left = insert<T>(root->left,val);
        else if(val > root->key) root->right = insert<T>(root->right,val);
        else return root;
        return balancedTree<T>(root);
    }  
template<typename T>
// Tra ve Node co gia tri nho nhat
Node<T>* findMin(Node<T>* root){
        if(!root)return NULL;
        while(root->left)root= root->left;
        return root;
    }
template<typename T>
// Tra ve true/false de kiem tra co tim thay gia tri val khong
bool search(Node<T>* root, T val){
        if(!root)return false;
        if(root->key == val)return true;
        else if(val < root->key)return search<T>(root->left,val);
        else return search<T>(root->right,val);
        return false;
    }
template<typename T>
// Dung de xoa Node gia tri val ra khoi root, va tra ve Node root
    Node<T>* deleteNode(Node<T>* root, T val){
        if(!root)return NULL;
        if(val < root->key)root->left = deleteNode<T>(root->left,val);
        else if(val > root->key) root->right =deleteNode<T>(root->right,val);
        else{
            if(!root->left && !root->right){
                delete root;
                return NULL;
            }
            else if(!root->left){
                Node<T>* tmp = root;
                root= root->right;
                delete tmp;
                return root;
            }
            else if(!root->right){
                Node<T>* tmp = root;
                root = root->left;
                delete tmp;
                return root;
            }
            else{
                Node<T>* p = findMin<T>(root->right);
                root->key = p->key;
                root->right = deleteNode<T>(root->right,p->key);
            }
        }
        return balancedTree<T>(root);
    }