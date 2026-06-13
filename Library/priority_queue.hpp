#pragma once
#include<iostream>
#include "utility.hpp"
using namespace std;

template <typename T>
struct priorityqueue{
    T* heap;
    int capacity, sz; 
};
template<typename T>
// Khoi tao mang voi cap la so phan tu toi da
priorityqueue<T>* initpriQueue(int newcap){
    priorityqueue<T>* pq = new priorityqueue<T>();
    pq->capacity = newcap;
    pq->sz = 0;
    pq->heap = new T[newcap];
    return pq;
}

// Dua phan tu thu i di xuong de giu tinh chat max heap
template <typename T>
void maxHeapify(priorityqueue<T>* pq, int i) {
    if (!pq) return;
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < pq->sz && pq->heap[l] > pq->heap[largest]) {
        largest = l;
    }
    if (r < pq->sz && pq->heap[r] > pq->heap[largest]) {
        largest = r;
    }
    if (i != largest) {
        swap(pq->heap[largest], pq->heap[i]);
        maxHeapify(pq, largest);
    }
}
template<typename T>
// Dua phan tu thu i di len de giu tinh chat max heap
void heapifyup(priorityqueue<T>* pq, int i){
    while(i > 0){
        int p = (i-1)/2;
        if(pq->heap[p] >=  pq->heap[i])break;
        swap(pq->heap[p],pq->heap[i]);
        i = p;
    }
}
template<typename T>
// Them mot phan tu val vao cuoi mang
void insert(priorityqueue<T>* pq, T val){
    if(pq->sz == pq->capacity){
        cout<<"Priority queue is full\n";
        return;
    }
    pq->heap[pq->sz]= val;
    pq->sz++;
    heapifyup(pq,pq->sz-1);
}
// Loai bo va tra ve phan tu lon nhat cua mang
template <typename T>
T extract(priorityqueue<T>* pq) {
    if (!pq || pq->sz == 0) {
        cout << "Priority queue is empty\n";
        return T();
    }
    T tmp = pq->heap[0];
    pq->heap[0] = pq->heap[pq->sz - 1];
    pq->sz--;
    maxHeapify(pq, 0);
    return tmp;
}
template<typename T>
// Tra ve phan tu lon nhat cua mang
T peek(priorityqueue<T>* pq){
    if(pq->sz==0){
        cout<<"Priority queue is empty\n";
        return T();
    }
    return pq->heap[0];
}
template<typename T>
// Kiem tra xem hang doi uu tien co rong khong
bool empty(priorityqueue<T>* pq){
    return pq->sz==0;
}
template<typename T>
// Tra ve so phan tu co trong hang doi uu tien hien co
int size(priorityqueue<T>* pq){
    return pq->sz;
}
template <typename T>
// Giai phong bo nho khi priority queue bi huy
void clearPriQueue(priorityqueue<T>* pq) {
    if (!pq) return;
    delete[] pq->heap; 
    delete pq;         
}
