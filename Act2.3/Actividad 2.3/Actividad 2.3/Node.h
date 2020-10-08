//
//  Node.h
//  Actividad 2.3
//
//  Created by Ruben Robles on 10/6/20.
//

#ifndef Node_h
#define Node_h
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


#endif /* Node_h */
