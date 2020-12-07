//
//  Heap.h
//  Heap
//
//  Created by Ruben Robles on 10/19/20.
//

#ifndef Heap_h
#define Heap_h


template<class T>
class Heap {
private:
    vector<T> heap;
    int size;
    void downSort(int index);
    void swap(int a, int b);
    void upSort();
public:
    Heap();
    Heap(vector<T> list);
    T remove();
    void insert(T data);
    bool isEmpty();
    void print();
};

template<class T>
Heap<T>::Heap() {
    size = 0;
}

template<class T>
void Heap<T>::swap(int a, int b) {
    T aux = heap[a];
    heap[a] = heap[b];
    heap[b] = aux;
}

template<class T>
T Heap<T>::remove() {
    if (!isEmpty()) {
        T aux = heap[1];
        swap(1,size);
        heap.pop_back();
        size--;
        downSort(1);
        return aux;
    }
    throw runtime_error("The Heap is empty");
}

template<class T>
void Heap<T>::downSort(int index){
    while (index>=1){
        int pos = index;
        while (pos*2 <= size){
            int s1 = pos*2; //si la lista empieza en 0, sería pos*2+1
            int s2 = pos*2+1; //si la lista empieza en 0. sería pos*2+2
            int max;
            if (s2 > size) {
                max = s1;
            } else {
                heap[s1] > heap[s2] ? max = s1: max = s2;
            }
            if (heap[max] > heap[pos]) {
                swap(pos,max);
                pos = max;
            } else {
                pos = size; //to end while cycle
            }
        }
        index--;
    }
}

template<class T>
void Heap<T>::upSort() {
    int pos = size;
    while (pos > 1) {
        int father = pos / 2;
        if (heap[pos] > heap[father]) {
            swap(father, pos);
            pos = father;
        } else {
            pos = 1; // para salir del ciclo
        }
    }
}

template<class T>
void Heap<T>::insert(T data) {
    heap.addLast(data);
    size++;
    upSort();
}

template<class T>
Heap<T>::Heap(vector<T> list) {
    if (!list.empty()){
        heap = list;
        size = heap.size();
        int index = size/2;
        downSort(index);
    }
    
}

template<class T>
bool Heap<T>::isEmpty() {
    return size == 0;
}

template<class T>
void Heap<T>::print() {
    heap.print();
}
#endif /* Heap_h */
