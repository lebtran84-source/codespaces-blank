#pragma once
#include<iostream>
using namespace std;
template <typename T>
// Ham doi cho 2 bien a va b cung kieu du lieu T
void swap(T& a, T& b){
    T tmp = a;
    a =b;
    b = tmp;
}
template <typename T>
struct prioiryqueue{
    T* heap;
    int capacity, sz;
    // Khoi tao mang voi cap la so phan tu toi da
    prioiryqueue(int cap){
        capacity = cap;
        sz = 0;
        heap = new T[capacity];
    }
    // Giai phong bo nho khi priority queue bi huy
    ~prioiryqueue(){
        delete[] heap;
    }
    // Dua phan tu thu i di xuong de giu tinh chat max heap
    void maxheapify(int i){
        int largest = i;
        int l = 2*i+1, r = 2*i+2;
        if(l < sz && heap[l]>heap[largest]){
            largest = l;
        }
        if(r < sz && heap[r]> heap[largest]){
            largest = r;
        }
        if(i!= largest){
            swap(heap[largest], heap[i]);
            maxheapify(largest);
        }
    }
    // Dua phan tu thu i di len de giu tinh chat max heap
    void heapifyup(int i){
        while(i > 0){
            int p = (i-1)/2;
            if(heap[p] >=  heap[i])break;
            swap(heap[p],heap[i]);
            i = p;
        }
    }
    // Them mot phan tu val vao cuoi mang
    void insert(T val){
        if(sz == capacity){
            cout<<"Priority queue is full\n";
            return;
        }
        heap[sz]= val;
        sz++;
        heapifyup(sz-1);
    }
    // Tra ve phan tu lon nhat cua mang
    T peek(){
        if(sz==0){
            cout<<"Priority queue is empty\n";
            return T();
        }
        return heap[0];
    }
    // Loai bo va tra ve phan tu lon nhat cua mang
    T extract(){
        if(sz==0){
            cout<<"Priority queue is empty\n";
            return T();
        }
        T tmp = heap[0];
        heap[0] = heap[sz-1];
        sz--;
        maxheapify(0);
        return tmp;
    }
    // Kiem tra xem hang doi uu tien co rong khong
    bool empty(){
        return sz==0;
    }
    // Tra ve so phan tu co trong hang doi uu tien hien co
    int size(){
        return sz;
    }
};