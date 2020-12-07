//
//  Graph.h
//  Grafos
//
//  Created by Ruben Robles on 11/10/20.
//

#ifndef Graph_h
#define Graph_h
#include "Stack.h"
#include "HashQ.h"

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
class Graph {
private:
    vector< vector<T> > adjList;
    vector<T> vertices;
    int qtyVertices;
    int qtyEdges;
    int findVertex(T vertex);
    void dfsR(T vertex, vector<bool> &status);
    HashQ<string> hashTable;
public:
    Graph(vector< vector<T> > list, int qtyVertices, int qtyEdges);
    void print();
    void bfs();
    void dfs();
    void ipysusvertices(vector<Bundle>*);
    void busquedaChida(T ip);
};

template<class T>
Graph<T>::Graph(vector< vector<T> > list, int qtyVertices, int qtyEdges) {
    this->qtyVertices = qtyVertices;
        this->qtyEdges = qtyEdges;
        int source = 0; //origin
        int target = 1; //destiny
        for (vector<T> edge : list){ //create list of vertices
            T temp = edge[source];
            int pos = findVertex(temp);
            if (pos < 0){ //vertex was not found
                vertices.push_back(temp);
            }
            temp = edge[target];
            pos = findVertex(temp);
            if (pos < 0){ //vertex was not found
                vertices.push_back(temp);
            }
        }
        HashQ<T> hashTabletemp(vertices);
        hashTable = hashTabletemp;
        sort(vertices.begin(),vertices.end()); //sort list of vertices
        
        for (auto vertex : vertices){ //add vertices to list of adj
            vector<T> temp;
            temp.push_back(vertex);
            adjList.push_back(temp);
        }
        
        for (auto edge: list){ //add targets/destinies for each vertex
            int pos = findVertex(edge[source]);
            adjList[pos].push_back(edge[target]); //add the targets
        }
}
//modify to work with hashing
template<class T>
int Graph<T>::findVertex(T vertex) {
    int key = hashTable.hashing(vertex);
    while(hashTable.table[key] != vertex){
        if (key == hashTable.table.size()-1){
            key = 0;
        }
        else {
            key++;
        }
    }
    return key;
}

template<class T>
void Graph<T>::busquedaChida(T ip){
    int pos = findVertex(ip);
    for (auto vertex : adjList[pos]){
        cout << vertex << " ";
    }
}

template<class T>
void Graph<T>::ipysusvertices(vector<Bundle>* vector){
    string origen;
    string returnlist;
    int i;
    int vertices;
    for (auto edge : adjList){
        i = 0;
        for (auto vertex : edge){
            if (i==0){
                origen = vertex;
            }
            //cout << vertex << " ";
            vertices = i;
            i++;
        }
        //cout<< endl;
        vector->push_back(Bundle(origen,vertices));
        
    }
}

template<class T>
void Graph<T> :: print(){
    for (auto edge : adjList){
        for (auto vertex : edge){
            cout << vertex << " ";
        }
        cout<< endl;
    }
}

template<class T>
void Graph<T>::bfs() {
    vector<bool> status(vertices.size(),false);
    Stack<int> q;
    //agregamos el primer vertice a la fila
    q.push(0);
    //le cambiamos el status al primer vértice
    status[0] = true;
    while (!q.isEmpty()) {
        int vertex = q.front();
        cout << vertices[vertex] << " ";
        for (auto adj : adjList[vertex]) {
            int pos = findVertex(adj);
            if (!status[pos]) {
                q.push(pos);
                status[pos] = true;
            }
        }
        q.pop();
    }
    cout << endl;
}

template<class T>
void Graph<T>::dfs() {
    vector<bool> status(vertices.size(),false);
    dfsR(vertices[0],status);//revisa si el status del nodo está procesado
}

template<class T>
void Graph<T>::dfsR(T vertex, vector<bool> &status){
    int pos = findVertex(vertex);
    if (!status[pos]) {//no procesado
        cout << vertex << " ";
        status[pos] = true;
        for (auto adj : adjList[pos]) {
            int posAdj = findVertex(adj);
            if (!status[posAdj]) {
                dfsR(adj,status);
            }
        }
    }
}

#endif /* Graph_h */
