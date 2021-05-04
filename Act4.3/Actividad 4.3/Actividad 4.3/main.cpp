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
#include <vector>

#include "Graph.h"
#include "Heap.h"

using namespace std;

template<class T>
void HeapSort(vector<T> &list) {
    if (!list.empty()) {
        Heap<T> heapAux(list);
        list.clear();
        while (!heapAux.isEmpty()) {
            T aux = heapAux.remove();
            list.push_back(aux);
        }
    }
}

template<class T>
void printVector(vector<vector<T>> const &mat) {
    for (vector<T> row: mat) {
        for (T val: row) {
            cout << val << " ";
        }
        cout << '\n';
    }
}

int main() {
    
    //leer archivo
    cout << "Reading file... ";
    fstream fin;
    //debe de ser vector de strings
    vector<string> dataRead;
    fin.open("bitacoraACT4_3.txt", ios::in);
    if(fin.fail()){
        cout << "Failed to open file.\nTerminating program." << endl;
        return 0;
    }
    string linea;
    while(getline(fin,linea)){
      stringstream s(linea);
        dataRead.push_back(linea);
    }
    
    fin.close();
    cout << "Done! " << endl;
    cout << "Creating Graph... ";
    
    //crear dos vectores, uno con iporigen y ipdestino y otro vector con este vector adentro actualizado, el vectorgrandote
    
    vector<string> ips;
    vector <vector<string> > vectorgrandote;
    vector<string> temp = {"0","0"};
    
    //LEE EL PRIMER NUMERO DONDE DICE CUANTAS IPS ORIGEN
    int firstline_pos = (int)dataRead[0].find(" ");
    string cantIP = dataRead[0].substr(0,firstline_pos);
    dataRead[0].erase(0,firstline_pos + 1);
    //LEE CUANTAS INCIDENCIAS HAY EL SEGUNDO NUMERO
    
    int incid_pos = (int)dataRead[0].find(" ");
    string incid = dataRead[0].substr(0,incid_pos);
    dataRead[0].erase(0,incid_pos + 1);
    
    
    int size = dataRead.size();
    
    //read from line 2 to the first number read
    for (int i=1;i<=stoi(cantIP);i++){
        string ipread;
        ipread = dataRead[i];
        ips.push_back(ipread); //dll de ips nadamas
    }
    
    //read the incidences
    for (int i=stoi(cantIP)+1;i<size;i++){ //CAMBIAR A SIZE!!
        string ipdestino;
        string ip;
        //buscar cuarto espacio antes de la IP
        for(int j=0;j<3;j++){
            int posespacio= (int)dataRead[i].find(" ");
            dataRead[i].erase(0,posespacio + 1);
        }
        
        //ahora si guardamos ip desde el tercer espacio
        int posespacio=(int)dataRead[i].find(" ");
        ip = dataRead[i].substr(0,posespacio-5);
        dataRead[i].erase(0,posespacio + 1);
        posespacio=(int)dataRead[i].find(" ");
        ipdestino = dataRead[i].substr(0,posespacio);
        
        temp[0] = ip;//esto
        temp[1] = ipdestino;//y esto
        vectorgrandote.push_back(temp);
        //datos.push_back(Dato(ip,ipdestino));
        
    }
    cout << "Done! " << endl;
    cout << "Sorting IPs in descending order by adjacencies (2 minutes average)... ";
    Graph<string> graph(vectorgrandote,stoi(cantIP),stoi(incid));
    //create a struct for IP origin and vertex qty...
    vector<Bundle> finalList;
    //this will modify the DLL and will kindly add
    graph.ipysusvertices(&finalList);
    Heap<Bundle> heap(finalList);
    HeapSort(finalList);
    cout << "Done! " << endl;
    cout << "\nThe IP address with the most adjacencies was: " << finalList[0].IP << " with " << finalList[0].count << " adjacencies." << endl << endl;
    cout << "Do you want to acquire the 10 IP addresses with the most adjacencies? (Y/N): ";
    string option;
    cin >> option;
    if (option == "Y" || option == "y"){
        for (int i=0;i<10;i++){
            try{
                cout << finalList[i].IP << " with " << finalList[i].count << " adjacencies." << endl;
            }
            catch(out_of_range oor){
                cout << "No more IPs" << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
