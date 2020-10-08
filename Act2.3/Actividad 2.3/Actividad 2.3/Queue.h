//
//  Queue.h
//  Abstraccion de datos
//
//  Created by Ruben Robles on 10/5/20.
//

#include <stddef.h>

// NODE WITH ONLY ONE POINTER.
template<class T>
struct Node2 {
    T data;
    Node2<T>* next;
    Node2(T data);
    Node2(T data, Node2<T> *next);
};

template<class T>
Node2<T>::Node2(T data){
    this->data = data;
    this->next = NULL;
}

template<class T>
Node2<T>::Node2(T data, Node2<T>* next){
    this->data = data;
    this->next = next;
}


template <class T>
class Queue{
private:
    Node2<T>* head;
    Node2<T>* tail;
    int size;
public:
    //Queue default
    Queue();
    //Borra el primer nodo agregado al  Queue y regresa su valor
    T dequeue();
    
    //Agrega un nodo al Queue
    void enqueue (T data);

    //Obtiene el valor del primer nodo agregado al Queue
    T front();

    //Obtiene el valor del último nodo agregado al Queue
    T back();

    //Regresa el tamaño del Queue
    int getSize();

    //Elimina todos los elementos del Queue
    void clear();

    bool isEmpty();

    //Despliega todos los nodos del Queue
    void print();
    
    //just for the merge sort
    T getData(int index);
};


template <class T>
Queue<T>::Queue(){
  head = NULL;
  tail = NULL;
  size = 0;
}

//Borra el primer nodo (head) , se reasigna al siguiente valor y el anterior node se elimina y le das return.
template <class T>
T Queue<T>::dequeue(){
   if(!isEmpty()){
    //asigna el head a aux
    Node2<T>* aux = head;
    //head se convierte en el siguiente valor (next)
    head = aux-> next;
    T retVal = aux->data;
    //borra aux que era el anterior head
    delete aux;
    //reduce size
    size--;
    return retVal;
  }
  return 0;
}

//agrega al final (tail)
template <class T>
void Queue<T>::enqueue(T data){
    if (isEmpty()){
      head = new Node2<T>(data,head);
      size++;
      tail = head;
    }
    else{
      Node2<T>* aux = head;
      while(aux->next != NULL){
        aux=aux->next;
      }
      aux->next = new Node2<T>(data);
      tail = aux->next;
      size++;
    }
}

template <class T>
T Queue<T>::getData(int index){
    if (index >= 0 && index <= size-1){
        Node2<T>* aux = head;
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


//Obtiene el valor del primer nodo agregado al Queue
template <class T>
T Queue<T>::front(){
  return head->data;
}

//Obtiene el valor del último nodo agregado al Queue
template <class T>
T Queue<T>::back(){
  return tail->data;
}

//copiado de LinkedList
template <class T>
int Queue<T>::getSize() {
    return size;
}

template <class T>
void Queue<T>::clear(){
  while(!isEmpty()){
        Node2<T>* aux = head;
        head = aux-> next;
        delete aux;
        size--;
  }
}

template <class T>
void Queue<T>::print() {
    Node2<T>* aux = head;
    for (int i=0; i<size; i++){
        cout << aux->data << " ";
        aux = aux->next;
    }
    cout << endl;
}

template <class T>
bool Queue<T>::isEmpty() {
    return size == 0;
}
