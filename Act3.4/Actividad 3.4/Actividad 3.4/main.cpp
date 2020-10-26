//
//  main.cpp
//  Actividad 3.4
//
//  Created by Ruben Robles on 10/25/20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <unistd.h>
#include "Heap.h"

using namespace std;

struct Dato {
  string fecha_hora;
  string ip;
    string port;
    string ip_port;
  string razon;
  Dato();
  Dato(string,string,string,string);
  string imprimir();
    bool operator>(Dato);
};

Dato::Dato(){
    fecha_hora = "0";
    ip = "0";
    port = "0";
    ip_port = "0";
    razon = "0";
}
Dato :: Dato (string fecha_hora, string ip, string port, string razon){
  this->fecha_hora = fecha_hora;
  this->ip = ip;
    this->port = port;
    ip_port = ip + port;
  this->razon = razon;
}

string Dato :: imprimir(){
  return  fecha_hora + " " + ip + ":" + port + " " + razon;
}
bool Dato :: operator>(Dato dato){
    return this->ip_port > dato.ip_port;
}

struct Bundle{
    string IP;
    int count;
    Bundle();
    Bundle(string, int);
    bool operator>(Bundle);
};

Bundle::Bundle(){
    IP = "0";
    count = 0;
}

Bundle::Bundle(string IP, int count){
    this->IP = IP;
    this->count = count;
}
bool Bundle :: operator>(Bundle IPBundle){
    return this->count > IPBundle.count;
}

template<class T>
void HeapSort(DoublyLinkedList<T> &list, string order = "ascending") {
    if (!list.isEmpty()) {
        Heap<T> heapAux(list);
        list.clear();
        while (!heapAux.isEmpty()) {
            T aux = heapAux.remove();
            if (order == "ascending") {
                list.addFirst(aux);
            } else {
                list.addLast(aux);
            }
        }
    }
}


int main() {
    
    //leer archivo
    cout << "Reading file... ";
    fstream fin;
    //debe de ser DLL de strings
    DoublyLinkedList<string> dataRead;
    
    fin.open("bitacora2.txt", ios::in);
    string linea;
    while(getline(fin,linea)){
      stringstream s(linea);
        dataRead.addLast(linea);
    }
    
    fin.close();
    cout << "Done! " << endl;
    cout << "Creating Doubly Linked List... ";
    
    //crear dll de OBJETOS tipo DATO
    DoublyLinkedList<Dato> datos;
    
    int size = dataRead.getSize();
    for (int i=0;i<size;i++){
      string date_hour,ip,port,razon;
      //lee el mes como string y lo cambia a numero
      int pos = (int)dataRead.getData(i).find(" ");
      date_hour = dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
      //lee el dia
      pos = (int)dataRead.getData(i).find(" ");
      date_hour = date_hour + " " + dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
        

      //concatena mes y dia: Sep 7 = 907
      //lee la hora
      pos = (int)dataRead.getData(i).find(" ");
      date_hour = date_hour + " " + dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);



      //lee la direccion ip
      pos = (int)dataRead.getData(i).find(":");
      ip = dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
        
        //lee el puerto
        pos = (int)dataRead.getData(i).find(" ");
        port = dataRead.getData(i).substr(0,pos);
        dataRead.erase(i,0,pos + 1);
      //lee la razon de falla
      razon = dataRead.getData(i);
        
      datos.addLast(Dato(date_hour, ip, port, razon));
        
    }
    
    cout << "Done! ";
    
    cout << size << " entries were loaded." << endl;

    // ----------
    
    
    
    cout << "Sorting database by IP using Heap... ";
    //ordena vector con fechas de más antigua a más reciente
    //sort(datos,0,datos.getSize()-1);
    Heap<Dato> heap(datos);
    HeapSort(datos);
    
    cout << "Done! " << endl;
    cout << "Saving sorted database in a file... ";
    //almacena el vector ordenado en un archivo nuevo
    ofstream outdata ("output.txt");
    for (int i=0;i<datos.getSize();i++){
      outdata << datos.getData(i).imprimir() << endl;

    }
    outdata.close();
    cout << "Done! Sorted database was saved in 'output.txt'" << endl;
    int counter = 1;
    cout << "Creating IP bundles in a Heap data structure... ";
    
    DoublyLinkedList<Bundle> IPBundle;
    
    for(int i=0; i<datos.getSize(); i++){
        string next; //TO AVOID comparing last value to a non existant next index (i+1)
        try{next = datos.getData(i+1).ip;}
        catch(out_of_range oor){next = "EOF";}
        
        if(datos.getData(i).ip == next){
            counter++;
        }
        else{
            IPBundle.addLast(Bundle(datos.getData(i).ip,counter));
            counter = 1;
        }
    }
    Heap<Bundle> heapIP(IPBundle);
    cout << "Done!" << endl;
    cout << "Sorting the number of accesses (Descending)... ";
    HeapSort(IPBundle, "descending");
    cout << "Done!" << endl << endl;
    
    cout << "The 5 IP addresses with the most accesses were:" << endl << endl;
    for (int i=0;i<5;i++){
        cout << IPBundle.getData(i).IP << " accesed " << IPBundle.getData(i).count << " times." << endl;
    }
    cout << endl;
    cout << "Do you want to acquire the 5 IP addresses with the fewest accesses? (Y/N): ";
    string option;
    cin >> option;
    if (option == "Y" || option == "y"){
        cout << "\nSorting the number of accesses (Acending)... ";
        HeapSort(IPBundle);
        cout << "Done!" << endl << endl;
        cout << "The 5 IP addresses with the fewest accesses were:" << endl << endl;
        for (int i=0;i<5;i++){
            cout << IPBundle.getData(i).IP << " accesed " << IPBundle.getData(i).count << " times." << endl;
        }
        cout << endl;
    }
    return 0;
}


