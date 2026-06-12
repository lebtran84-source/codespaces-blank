#pragma once
#include<iostream>
using namespace std;
template <typename T>
struct queue{
    T* data;
    int capacity, front, rear, sz;
    // Khoi tao hang doi voi so phan tu toi da la cap
    queue(int cap){
        capacity = cap;
        data = new T[capacity];
        front =0;
        rear = -1;
        sz =0;
    }
    // Giai phong bo nho khi xoa queue
    ~queue(){
        delete[] data;
    }
    // Them phan tu val vao cuoi hang doi
    void enqueue(T val){
        if(sz == capacity){
            cout<<"Queue is full\n";
            return;
        }
        rear++;
        if(rear ==capacity){
            rear = 0;
        }
        sz++;
        data[rear]= val;
    }
    // Xoa phan tu dau ra khoi hang doi va tra ve gia tri do 
    T dequeue(){
        if(sz ==0){
            cout<<"Queue is empty\n";
            return T();
        }
        T val = data[front];
        front++;
        if(front == capacity){
            front = 0;
        }
        sz--;
        return val;
    }
    // Tra ve phan tu dau trong hang doi
    T peek(){
        if(sz == 0){
            cout<<"Queue is empty\n";
            return T();
        }
        return data[front];
    }
    // Kiem tra xem hang doi co rong khong
    bool empty(){
        return sz ==0;
    }
    // Tra ve so luong phan tu hien co trong hang doi
    int size(){
        return sz;
    }

};
