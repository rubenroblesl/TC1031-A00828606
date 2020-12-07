
//
//  Hash.h
//  Hash
//
//  Created by Ruben Robles on 12/3/20.
//
#ifndef HashQ_h
#define HashQ_h

using namespace std;

template<class T>
class HashQ {
public:
    vector<T> table;
    vector<bool> status; // falsoedad=ocupado, true= libre
    HashQ();
    int size;
    int qty;
    bool isFull();
    int hashing(T data);
    int quadTest(int index, int cont);
    HashQ(int size);
    HashQ(vector<T> list);
    void addData(T data);
    void deleteData(T data);
    int findData(T data);
    void print();
};
template<class T>
HashQ<T> :: HashQ(){
    size = 0;
    qty = 0;
    vector<T> tempList;
    table = tempList;
    vector<bool> tempStatus;
    status = tempStatus;
}

template<class T>
HashQ<T>::HashQ(int size) {
    this->size = size;
    qty = 0;
    vector<T> tempTable(size);
    table = tempTable;
    vector<bool> tempStatus(size,true);
    status = tempStatus;
}

template<class T>
HashQ<T>::HashQ(vector<T> list) {
    qty = 0;
    cout << "size: " << list.size() << endl;
    size = list.size();
    vector<T> tempTable(size);
    table = tempTable;
    vector<bool> tempStatus(size,true);
    status = tempStatus;
    for (auto data : list) {
        addData(data);
    }
}

template<class T>
void HashQ<T>::addData(T data) {
    if (!isFull()) {
        int index = hashing(data);
        if (status[index] == true) { // Revisar si esta vacio
            table[index] = data;
            status[index] = false; // Ocupado
            qty++;
        } else {
            int i = index;
            // Validar si ya existe
            while(status[i] != true){
                if (i == table.size()-1){
                    i = 0;
                }
                else {
                    i++;
                }
            }
            table[i] = data;
            status[i] = false; // Ocupadp
            qty++;
        }
    } else {
        throw out_of_range("La tabla ya esta llena");
    }
}

template<class T>
int HashQ<T>::findData(T data) {
    int cont = 1;
    int index = hashing(data);
    while (status[index] != 0 && cont < size) {
        if (status[index] == 1 && table[index] == data) {
            return index;
        }
        index = quadTest(index,cont);
        cont++;
    }
    return -1;
}

template<class T>
int HashQ<T>::quadTest(int index, int cont) {
    int newIndex;
    if (index + int(pow(-1, cont - 1)) * int(pow((cont + 1) / 2, 2)) < 0) {
        newIndex = size - fmod(size - int(pow(-1, cont - 1)) * int(pow((cont + 1) / 2, 2)), size);
    } else {
        newIndex = fmod(index + int(pow(-1, cont - 1)) * int(pow((cont + 1) / 2, 2)), size);
    }
    return newIndex;
}

void removeDots(std::string &x)
{
  auto it = std::remove_if(std::begin(x),std::end(x),[](char c){return (c == '.');});
  x.erase(it, std::end(x));
}

template<class T>
int HashQ<T>::hashing(T data) {
    int key;
    removeDots(data);
    data.erase(0,8);
    int newData = stoi(data);
    return newData;
}

template<class T>
bool HashQ<T>::isFull() {
    return qty == size;
}

template<class T>
void HashQ<T>::print() {
    cout << "Hash Table" << endl;
    for(int i=0; i<size; i++) {
        cout << i << "-" << table[i] << endl;
    }
}
#endif /* HashQ_h */

