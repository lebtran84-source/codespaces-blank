#pragma once
#include<iostream>
using namespace std;
template <typename T>
struct stack{
    T* data;
    int top, capacity;
};

template<typename T>
// Khoi tao ngan xep voi cap phan tu toi da
stack<T>* initStack(int cap){
    stack<T>* st = new stack<T>();
    st->capacity = cap;
    st->data = new T[cap];
    st->top = -1;
    return st;
}
template<typename T>
// Them mot phan tu vao cuoi 
void push(stack<T>* st, T val){
    if (!st) return;
    if(st->top== st->capacity -1){
        cout<<"Stack is full\n";
        return;
    }
    st->top++;
    st->data[st->top] = val;
}
template<typename T>
// Loai bo phan tu cuoi cung ra khoi ngan xep
T pop(stack<T>* st){ 
    if(!st || st->top== -1){
        cout<<"Stack is empty\n";
        return T();
    }
    T val = st->data[st->top];
    st->top--;
    return val;
}
template<typename T>
T top(stack<T>* st){
    if(!st || st->tp == -1){
        cout<<"Stack is empty\n";
        return T();
    } 
    return st->data[st->top];
}
template<typename T>
// Kiem tra xem ngan xep co trong khong
bool empty(stack<T>* st){
    return st->top == -1;
}
template<typename T>
// Tra ve so phan tu hien co trong ngan xep
int size(stack<T>* st){
    return st->top+1;
}
template<typename T>
// Giai phong ngan xep khi stack bi xoa
void clearStack(stack<T>* st){
    if(!st)return;
    delete[] st->data;
    delete st;
}
