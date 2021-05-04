//
//  Stack.h
//  Abstraccion de datos
//
//  Created by Ruben Robles on 10/5/20.
//

#ifndef Stack_h
#define Stack_h
#include <stddef.h>
using namespace std;

template<class T>
struct Node {
    T data;
    Node<T>* next;
    Node(T data);
    Node(T data, Node<T> *next);
};

template<class T>
Node<T>::Node(T data){
    this->data = data;
    this->next = NULL;
}

template<class T>
Node<T>::Node(T data, Node<T>* next){
    this->data = data;
    this->next = next;
}


template <class T>
class Stack{
private:
    Node<T>* head;
    int size;
public:
  Stack();

  //deletes last value added (first) y regresa lo que borro
  T pop();
  
  //Agrega un nodo al Stack al principio
  void push (T data);

  //Obtiene el valor del último nodo agregado al Stack
  T top();
  bool isEmpty();

  //Regresa el tamaño del Stack
  int getSize();
  
  //Elimina todos los elementos del Stack
  void clear();
  
  //Despliega todos los nodos del stack
  void print();
    
    //from queue
    T front();
};

template <class T>
T Stack<T>::front(){
  return head->data;
}

template <class T>
Stack<T>::Stack(){
  head = NULL;
  size = 0;
}

template <class T>
T Stack<T>::pop(){
  if(!isEmpty()){
    Node<T>*aux = head;
    head = aux->next;
    T aux2 = aux->data;
    delete aux;
    size--;
    return aux2;
  }
    return 0;
}

template <class T>
void Stack<T>::push(T data){
  head = new Node<T>(data, head);
  size++;
}

template <class T>
T Stack<T>::top(){
  return head -> data;
}

//copiado de LinkedList
template <class T>
int Stack<T>::getSize() {
    return size;
}

template <class T>
void Stack<T>::clear(){
    while(!isEmpty()){
        Node<T>* aux = head;
        head = aux-> next;
        delete aux;
        size--;
    }
}

template <class T>
void Stack<T>::print() {
    Node<T>* aux = head;
    for (int i=0; i<size; i++){
        cout << aux->data << " ";
        aux = aux->next;
    }
    cout << endl;
}

template <class T>
bool Stack<T>::isEmpty() {
    return size == 0;
}

#endif
