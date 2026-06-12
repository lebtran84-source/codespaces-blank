#pragma once
#include<iostream>
using namespace std;
template <typename T>
struct stack{
    T* data;
    int top, capacity;
    // Khoi tao ngan xep voi cap phan tu toi da
    stack(int cap){
        capacity = cap;
        data = new T[capacity];
        top = -1;
    }
    // Giai phong ngan xep khi stack bi xoa
    ~stack(){
        delete[] data;
    }
    // Them mot phan tu vao cuoi 
    void push(T val){
        if(top== capacity -1){
            cout<<"Stack is full\n";
            return;
        }
        top++;
        data[top] = val;
    }
    // Loai bo phan tu cuoi cung ra khoi ngan xep
    T pop(){ 
        if(top== -1){
            cout<<"Stack is empty\n";
            return T();
        }
        T val = data[top];
        top--;
        return val;
    }
    // Kiem tra xem ngan xep co trong khong
    bool empty(){
        return top == -1;
    }
    // Tra ve so phan tu hien co trong ngan xep
    int size(){
        return top+1;
    }
};
