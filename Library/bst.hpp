#pragma once
template<typename T>
struct Node{
    T key;
    Node *left, *right;
    Node(T data){
        key = data;
        left = NULL;
        right = NULL;
    };  
};
template<typename T>
// Them mot Node co gia tri val vao root, tra ve cay da them phan tu
Node<T>* insert(Node<T>* root, T val){
    if(!root){
        return new Node(val);
    }
    if(val < root->key)root->left = insert(root->left,val);
    else if(val > root->key) root->right = insert(root->right,val);
    return root;
}
template<typename T>
// Tra ve Node co gia tri nho nhat
Node<T>* findMin(Node<T>* root){
    if(!root)return NULL;
    while(root->left) root = root->left;
    return root;
}
template<typename T>
// Tra ve root cua cay khi da xoa phan tu val ra khoi cay
Node<T>* remove(Node<T>* root, T val){
    if(!root)return NULL;
    if(val < root->key) root->left = remove<T>(root->left,val);
    else if(val > root->key) root->right = remove<T>(root->right, val);
    else{
        if(!root->left && !root->right){
            delete root;
            root = NULL;
        }
        else if(!root->left){
            Node<T>* tmp = root;
            root = root->right;
            delete tmp;
        }
        else if(!root->right){
            Node<T>* tmp = root;
            root = root->left;
            delete tmp;
        }
        else{
            Node<T>* p = findMin<T>(root->right);
            root->key = p->key;
            root->right = remove<T>(root->right,p->key);
        }
    }
    return root;
}
template<typename T>
// Tra ve true/false de kiem tra co phan tu val trong cay khong
bool search(Node<T>* root, T val){
    if(!root)return false;
    if(val == root->key)return true;
    else if(val < root->key) return search<T>(root->left,val);
    else return search<T>(root->right,val);
    return false;
}
template<typename T>
// duyet cay theo tien to
    void preorder(Node<T>* root){
    if(!root)return;
    cout<<root->key<<' ';
    preorder<T>(root->left);
    preorder<T>(root->right);
}
template<typename T>
// duyet cay theo trung to
void inorder(Node<T>* root){
    if(!root)return;
    inorder<T>(root->left);
    cout<<root->key<<' ';
    inorder<T>(root->right);
}
template<typename T>
// duyet cay theo hau to
void postorder(Node<T>* root){
    if(!root)return;
    postorder<T>(root->left);
    postorder<T>(root->right);
    cout<<root->key<<' ';
}
template<typename T>
void clearTree(Node<T>* root){
    if(!root)return;
    clearTree<T>(root->left);
    clearTree<T>(root->right);
    delete root;
}
