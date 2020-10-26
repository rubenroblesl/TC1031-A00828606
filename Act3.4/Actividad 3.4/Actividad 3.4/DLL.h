//
//  DLL.h
//  Heap
//
//  Created by Ruben Robles on 10/19/20.
//

#ifndef DLL_h
#define DLL_h

// NODE -------
using namespace std;

template<class T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
    Node(T data);
    Node(T data, Node<T> *next, Node<T> *prev);
};

template<class T>
Node<T>::Node(T data){
    this->data = data;
    this->next = NULL;
    this->prev = NULL;
}

template<class T>
Node<T>::Node(T data, Node<T>* next, Node<T> *prev){
    this->data = data;
    this->next = next;
    this->prev = prev;
}

//--------


template<class T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    DoublyLinkedList();
    void operator=(initializer_list<T> list);
    void operator=(DoublyLinkedList<T> list);
    T& operator[](int index);
    void addFirst(T data);
    void addLast(T data);
    T getData(int index);
    void updateAt(int index, T newData);
    //int findData(T data);
    void deleteAt(int index);
    void deleteLast();
    void erase(int index, int pos_in, int pos_f);
    int getSize();
    void clear();
    void print();
    bool isEmpty();
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = NULL;
    size = 0;
}

template<class T>
T& DoublyLinkedList<T>::operator[](int index) {
    if (index >= 1 && index <= size) {
        if (index <= size / 2) {
            Node<T>* aux = head;
            int i = 1; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux->data;
                }
                aux = aux->next;
                i++;
            }
        } else {
            Node<T>* aux = tail;
            int i = size; // The list starts with 1
            while (aux != NULL) {
                if (i == index) {
                    return aux->data;
                }
                aux = aux->prev;
                i--;
            }
        }
    }
    throw out_of_range("Invalid position");
}

template<class T>
void DoublyLinkedList<T>::operator=(initializer_list<T> list) {
    if (isEmpty()) {
        for (T i : list) {
            addLast(i);
        }
    } else {
        throw runtime_error("Error: DoublyLinkedList no esta vacia");
    }
}

template<class T>
void DoublyLinkedList<T>::operator=(DoublyLinkedList<T> list) {
    clear();
    for (int i=1; i<=list.size; i++) {
        addLast(list[i]);
    }

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
    throw out_of_range("Error");
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

template<class T>
void DoublyLinkedList<T>::deleteLast(){
    if (!isEmpty()){
        Node<T>* aux = tail;
        tail = tail->prev;
        if (tail == NULL){ //if the list is emptied
            head = NULL;
        }
        delete aux;
        size--;
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

template<class T>
void DoublyLinkedList<T>::clear() {
    int i = 1;
    while (i<=size) {
        Node<T>* aux = head;
        head = aux->next;
        delete aux;
        i++;
    }
    size = 0;
    tail = NULL;
}

template <class T>
void DoublyLinkedList<T>::print() {
    Node<T>* aux = head;
    for (int i=0; i<size; i++){
        cout << aux->data << " ";
        aux = aux->next;
    }
    cout << endl;
}

template <class T>
bool DoublyLinkedList<T>::isEmpty() {
    return size == 0;
}


#endif
