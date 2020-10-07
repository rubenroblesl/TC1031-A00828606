//
//  DoublyLinkedList.h
//  Actividad 2.3
//
//  Created by Ruben Robles on 10/6/20.
//

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "Node.h"
//#include "Queue.h"


template<class T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    DoublyLinkedList();
    void addFirst(T data);
    void addLast(T data);
    T getData(int index);
    void updateAt(int index, T newData);
    //int findData(T data);
    void merge(int start,int mid, int end);
    void mergeSort(int start, int end);
    void deleteAt(int index);
    void erase(int index, int pos_in, int pos_f);
    void sort();
    int getSize();
    void print();
    bool isEmpty();
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = NULL;
    size = 0;
}

template <class T>
void DoublyLinkedList<T>::addFirst(T data) {
  if(isEmpty()){
    head = new Node<T>(data);
    tail = head;
  } else{
    head = new Node<T>(data,head,NULL);
    head->next->prev = head;
    
  }
  size++;
}

template <class T>
void DoublyLinkedList<T>::addLast(T data) {
    if (isEmpty()){
    head = new Node<T>(data);
    tail = head;
    size++;
} else{
  tail = new Node<T>(data,NULL,tail);
  tail -> prev -> next = tail;
  size++;
  }
}

template <class T>
T DoublyLinkedList<T>::getData(int index){
    if (index >= 0 && index <= size-1){
        Node<T>* aux = head;
        int i = 0;
        while (aux != NULL){
            if(i == index){
                return aux -> data;
            }
            aux = aux->next;
            i++;
        }
    }
    cout << "Error" << endl;
    throw runtime_error("Error");
}

template <class T>
void DoublyLinkedList<T>::erase(int index, int pos_in, int pos_f){
    
    T aux = getData(index);
    T newData = aux.erase(pos_in,pos_f);
    updateAt(index, newData);
}



template <class T>
void DoublyLinkedList<T>::deleteAt(int index){
    if (index >= 1 && index <=size){
        if (index == 1){
            Node<T>* aux = head;
            head = aux->next;
            delete aux;
            size --;
        }else {
            if (head->next != NULL){
                Node<T>* aux = head->next;
                Node<T>* prev = head;
                int i = 2;
                while (aux != NULL){
                    if (i == index){
                        prev -> next = aux->next;
                        delete aux;
                        size --;
                    } else {
                        prev = aux;
                        aux = aux->next;
                    }
                    i++;
                }
            }
        }
    }
}

/*
template <class T>
int DoublyLinkedList<T>::findData(T data){
    int posI = 1;
    int posF = size;
    int posM = (posI + posF) / 2;
    bool found = false;
    sort();
    while (posI <= posF && !found){
        if (data < getData(posM)){
            posF = posM + 1;
        }else {
            if (data == getData(posM)){
                posI = posM + 1;
            }else {
                if (data == getData(posM)){
                    found = true;
                }
            }
        }
        posM = (posI + posF) / 2;
    }
    if (found) {
        return posM;
    } else {
        return 0;
    }
}
*/

template <class T>
int DoublyLinkedList<T>::getSize() {
    return size;
}


template <class T>
void DoublyLinkedList<T>::updateAt(int index, T newData){
  //index++;
  // check if value is on the range
    if (index >= 0 && index <= size-1){
      // asignar a aux el head actual
        Node<T>* aux = head;
        int i = 0;
        while (aux != NULL){
          //in case its found, it'll be given a new value
            if(i == index){
                aux -> data = newData;
                aux = NULL;
            }
            else{
              aux = aux->next;
              i++;
            }
        }
    }
    else {
      cout << "Error" << endl;
    }
}


template <class T>
void DoublyLinkedList<T>::print() {
    Node<T>* aux = head;
    for (int i=0; i<size; i++){
        cout << aux->data << endl;
        aux = aux->next;
    }
    cout << endl;
}

template <class T>
bool DoublyLinkedList<T>::isEmpty() {
    return size == 0;
}

template <class T>
void DoublyLinkedList<T>::sort() {
    if (!isEmpty()){
      mergeSort(0,size-1);
    }
    else{
      throw runtime_error("Error. List is empty");
    }
}

template <class T>
void DoublyLinkedList<T>::mergeSort(int st, int ed) {
  if (st < ed){
    int mid = (st + ed)/2;
    mergeSort(st, mid);
    mergeSort(mid+1, ed);
    merge(st, mid, ed);
  }
}

template <class T>
void DoublyLinkedList<T>::merge(int st,int mid, int ed) {
  DoublyLinkedList<T> listaL;
  DoublyLinkedList<T> listaR;
  int i, j;
  int pos = st;
  int s1 = mid - st + 1;
  int s2 = ed-mid;
  for(i=0; i< s1; i++){
    listaL.addLast(getData(st+i));
  }
  for(j=0; j < s2; j++){
    listaR.addLast(getData(mid+1+j));
  }
  i=0;
  j=0;
  while(i < s1 && j < s2){
    if (listaL.getData(i).fecha_hora <= listaR.getData(j).fecha_hora){
      updateAt(pos, listaL.getData(i));
      i++;
    }else {
      updateAt(pos, listaR.getData(j));
      j++;
    }
    pos++;
  }
  while (i<s1){
    updateAt(pos,listaL.getData(i));
    i++;
    pos++;
  }
while (j<s2){
    updateAt(pos,listaR.getData(j));
    j++;
    pos++;
}
}



#endif
