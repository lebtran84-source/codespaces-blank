#pragma once
#include<iostream>
using namespace std;
// Dung de doi cho 2 bien a va b cung kieu du lieu
template<typename T>
void myswap(T &a, T &b){
    T tmp = b;
    b = a;
    a = tmp;
}
// Dung de sap xep cho mang tu nho den lon
// Goi bubbleSort(arr,n, greater<T>()) de sap xep tu lon den be
template<typename T, typename Comp = less<T>>
void bubbleSort(T arr[], int n, Comp cmp = Comp()){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-i-1; j++){
            if(cmp(arr[j+1],arr[j])){
                myswap(arr[j],arr[j+1]);
            }
        }
    }
}
// Dung de sap xep mang tu nho den lon
// Goi selectionSort(arr,n, greater<T>()) de sap xep tu lon den be
template <typename T, typename Comp = std::less<T>>
void selectionSort(T arr[], int n, Comp cmp = Comp()){
    for(int i = 0; i < n; i++){
        int idx = i;
        for(int j = i+1; j < n; j++){
            if(cmp(arr[j],arr[idx])) idx = j;
        }
        myswap(arr[idx],arr[i]);
    }
}
// Dung de sap xep mang tu nho den lon
// Goi insertionSort(arr,n, greater<T>()) de sap xep tu lon den be
template <typename T, typename Comp = std::less<T>>
void insertionSort(T arr[], int n, Comp cmp = Comp()){
    for(int i = 0; i < n; i++){
        T key = arr[i];
        int j = i-1;
        while(j >= 0 && cmp(key,arr[j])){
            arr[j+1] = arr[j];
            j --;
        }
        arr[j+1] = key;
    }
}
// Dung de sap xep mang tu nho den lon
// Goi heapSort(arr,n, greater<T>()) de sap xep tu lon den be
template <typename T, typename Comp = std::less<T>>
void heapify(T arr[], int n, int i, Comp cmp = Comp()){
    int best = i;
    int l = 2*i+1;
    int r = 2*i+2;
    if(l < n && cmp(arr[best],arr[l])) best = l;
    if(r < n && cmp(arr[best],arr[r])) best = r;
    if(best != i){
        myswap(arr[best],arr[i]);
        heapify(arr,n,best,cmp);
    }
}
template <typename T, typename Comp = std::less<T>>
void heapSort(T arr[], int n, Comp cmp = Comp()){
    for(int i = n/2 -1; i >= 0; i--){
        heapify(arr,n,i,cmp);
    }
    for(int i = n-1; i >= 0; i--){
        myswap(arr[0],arr[i]);
        heapify(arr,i,0,cmp);
    }
}

// Dung de sap xep mang tu nho den lon
// Goi quickSort(arr,n, greater<T>()) de sap xep tu lon den be
template <typename T, typename Comp = std::less<T>>
int partition(T arr[], int l, int r, Comp cmp = Comp()){
    T pivot = arr[l+ (r-l)/2];
    int i = l-1, j = r+1;
    while(true){
        do{
            i++;
        }while(cmp(arr[i],pivot));
        do{
            j--;
        }while(cmp(pivot,arr[j]));
        if(i>= j)return j;
        myswap(arr[i],arr[j]);
    }
}
template <typename T, typename Comp = std::less<T>>
void quickSort(T arr[], int l, int r, Comp cmp = Comp()){
    if(l >= r)return;
    int pivot = partition(arr,l,r,cmp);
    quickSort(arr,l,pivot,cmp);
    quickSort(arr,pivot+1,r,cmp);
}

// Dung de sap xep mang tu nho den lon
// Goi mergeSort(arr,n, greater<T>()) de sap xep tu lon den be
template <typename T, typename Comp = std::less<T>>
void merge(T arr[], int l, int mid, int r, Comp cmp = Comp()){
    int n1 = mid -l+1, n2 = r-mid;
    T* left = new T[n1], *right = new T[n2];
    for(int i = 0; i < n1; i++) left[i] = arr[i+l];
    for(int i = 0; i < n2; i++) right[i] = arr[mid + 1 +i];
    int i =0, j =0, k =l;
    while(i < n1 && j < n2){
        if(cmp(left[i],right[j])){
            arr[k++] = left[i++];
        }
        else{
            arr[k++] = right[j++];
        }
    }
    while(i <n1) arr[k++]=left[i++];
    while(j <n2) arr[k++]=right[j++];
    delete[] left;
    delete[] right;
}
template <typename T, typename Comp = std::less<T>>
void mergeSort(T arr[], int l, int r, Comp cmp = Comp()){
    if(l >= r)return;
    int mid = l + (r-l)/2;
    mergeSort(arr,l,mid,cmp);
    mergeSort(arr,mid+1,r,cmp);
    merge(arr,l,mid,r,cmp);
}

// Dung de tim kiem tuyen tinh trong mot mang chua sap xep gia tri val
template<typename T>
int linearSearch(T arr[], int n, T key){
    for(int i = 0; i < n; i++){
        if(arr[i] == key){
            return i;
        }
    }
    return -1;
}
// Dung de tim kiem nhi phan trong mot mang da duoc sap xep, se nhanh hon linearSearch(O(n)) la O(logn)
template<typename T, typename Comp = std::less<T>>
int binarySearch(T arr[], int n, T key, Comp cmp = Comp()){
    int l = 0, r = n-1;
    while(l <= r){
        int mid = l + (r-l)/2;
        if(arr[mid]==key)return mid;
        else if(cmp(arr[mid], key)) l = mid +1;
        else r = mid-1;
    }
    return -1;
}
