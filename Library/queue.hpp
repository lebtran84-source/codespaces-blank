#pragma once
#include<iostream>
using namespace std;
template <typename T>
struct queue{
    T* data;
    int capacity, front, rear, sz;
};
template<typename T>
// Khoi tao hang doi voi so phan tu toi da la cap
queue<T>* initQueue(int cap){
    queue<T>* q = new queue<T>();
    q->capacity = cap;
    q->data = new T[cap];
    q->front =0;
    q->rear = -1;
    q->sz =0;
    return q;
}
template<typename T>
// Them phan tu val vao cuoi hang doi
void enqueue(queue<T>* q, T val){
    if(q->sz == q->capacity){
        cout<<"Queue is full\n";
        return;
    }
    q->rear++;
    if(q->rear ==q->capacity){
        q->rear = 0;
    }
    q->sz++;
    q->data[q->rear]= val;
}
template<typename T>
// Xoa phan tu dau ra khoi hang doi va tra ve gia tri do 
T dequeue(queue<T>* q){
    if(q->sz ==0){
        cout<<"Queue is empty\n";
        return T();
    }
    T val = q->data[q->front];
    q->front++;
    if(q->front == q->capacity){
        q->front = 0;
    }
    q->sz--;
    return val;
}
template<typename T>
// Tra ve phan tu dau trong hang doi
T peek(queue<T>* q){
    if(q->sz == 0){
        cout<<"Queue is empty\n";
        return T();
    }
    return q->data[q->front];
}
template<typename T>
// Kiem tra xem hang doi co rong khong
bool empty(queue<T>* q){
    return q->sz ==0;
}
template<typename T>
// Tra ve so luong phan tu hien co trong hang doi
int size(queue<T>* q){
    return q->sz;
}
template<typename T>
// Giai phong bo nho khi xoa queue
void clearQueue(queue<T>* q){
    if(!q)return;
    delete[] q->data;
    delete q;
}
