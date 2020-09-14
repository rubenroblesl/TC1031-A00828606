#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Dato {
  int fecha_hora;
  string ip;
  string razon;
  Dato(int,string,string);
  string imprimir();
};

Dato :: Dato (int fecha_hora, string ip, string razon){
  this->fecha_hora = fecha_hora;
  this->ip = ip;
  this->razon = razon;
}

string Dato :: imprimir(){
  //parte la hora
  string date_hour = to_string(fecha_hora);
  int size = date_hour.size()-1;
  string hour,mins,secs;
  secs = date_hour.substr(size-1,2);
  mins = date_hour.substr(size-3,2);
  hour = date_hour.substr(size-5,2);
  //parte la fecha
  string mes,dia;
  dia = date_hour.substr(size-7,2);
  //regresa el dia a su forma original: 06 = 6
  if (dia.substr(0,1) == "0"){
    dia = dia.substr(1,1);
  }
  
  if (size == 8){
    mes = date_hour.substr(size-8,1);
  }
  else{
    mes = date_hour.substr(size-9,2);
  }
  
  //regresar el mes a su string original
  if (mes == "6"){
    mes = "Jun";
  }
  else if (mes == "7"){
    mes = "Jul";
  }
  else if (mes == "8"){
    mes = "Aug";
  }
  else if (mes == "9"){
    mes = "Sep";
  }
  else if (mes == "10"){
    mes = "Oct";
  }
  return  mes + " " + dia + " " + hour + ":" + mins + ":" + secs + " " + ip + " " + razon;
}

int sort(vector<Dato> &lista, int first, int last){
  //el pivote será el primer elemento en la lista
  int piv = lista[first].fecha_hora;
  //tomamos el elemento siguiente del pivote
  int iz = first + 1;
  int der = last;
  while (iz != der){
    if (lista[iz].fecha_hora <= piv){
      iz++;
    }
    else{
      while ((iz != der)  && (piv < lista[der].fecha_hora)){
        der--;
      }
      //intercambio
      Dato aux = lista[der];
      lista[der] = lista[iz];
      lista[iz] = aux;
        
    }
  }
  if (lista[iz].fecha_hora > piv){
    iz--;
  }
  lista[first] = lista[iz];
  lista[iz].fecha_hora = piv;
  //retorna la posicion del pivote
  return iz;
}

void quickSort(vector<Dato> &lista, int first, int last){
  if(first < last) {
    int posPiv = sort(lista, first, last);
    //ahora ira partiendo la lista a partir de donde se encontraría el pivote
    //para el lado izquierdo del pivote
    quickSort(lista, first, posPiv - 1);
    //para el lado derecho del pivote
    quickSort(lista, posPiv + 1, last);
  }
}


void secuentialSearch(vector<Dato> &list, int value_min, int value_max){
  for (int i=0; i<list.size(); i++){
    if(list[i].fecha_hora >= value_min && list[i].fecha_hora <= value_max){
      cout << list[i].imprimir() << endl;
    }
  }
}


int main() {
  //leer archivo
  fstream fin;
  vector <string> dataRead;
  fin.open("bitacora.txt", ios::in);
  string linea;
  while(getline(fin,linea)){
    stringstream s(linea);
    dataRead.push_back(linea);
  }
  fin.close();

  //crear vector de objetos
  vector<Dato> datos;
  for (int i=0;i<dataRead.size();i++){
    string month,date,hour,ip,razon;
    //lee el mes como string y lo cambia a numero
    int pos = (int)dataRead[i].find(" ");
    string mes = dataRead[i].substr(0,pos);
    dataRead[i].erase(0,pos + 1);
    if (mes=="Jun"){
      month = "6";
    }
    else if (mes=="Jul"){
      month = "7";
    }
    else if (mes=="Aug"){
      month = "8";
    }
    else if (mes=="Sep"){
      month = "9";
    }
    else if (mes=="Oct"){
      month = "10";
    }
    //lee el dia
    pos = (int)dataRead[i].find(" ");
    string dia = dataRead[i].substr(0,pos);
    dataRead[i].erase(0,pos + 1);
    int day = std::stoi(dia);
    //rellena los dias menores a 10 con un 0: 5 = 05
    if (day<=9){
      dia= "0" + dia;
    }
    //concatena mes y dia: Sep 7 = 907
    date = month + dia;
    //lee la hora
    pos = (int)dataRead[i].find(":");
    string hora = dataRead[i].substr(0,pos);
    dataRead[i].erase(0,pos + 1);
    //lee los minutos
    pos = (int)dataRead[i].find(":");
    string mins = dataRead[i].substr(0,pos);
    dataRead[i].erase(0,pos + 1);
    //lee los seguntos
    pos = (int)dataRead[i].find(" ");
    string secs = dataRead[i].substr(0,pos);
    dataRead[i].erase(0,pos + 1);
    //concatena el tiempo: 07:23:03 = 072303
    hour = hora + mins + secs;
    string date_hour = date + hour;
    int fecha_hora = std::stoi(date_hour);
    //lee la direccion ip
    pos = (int)dataRead[i].find(" ");
    ip = dataRead[i].substr(0,pos);
    dataRead[i].erase(0,pos + 1);
    //lee la razon de falla
    razon = dataRead[i];
    datos.push_back(Dato(fecha_hora,ip,razon));
  }
  //ordena vector con fechas de más antigua a más reciente
  quickSort(datos,0,datos.size()-1);

  //almacena el vector ordenado en un archivo nuevo
  ofstream outdata ("output.txt");
  for (int i=0;i<datos.size();i++){
    outdata << datos[i].imprimir() << endl;

  }
  outdata.close();
  
  string start_month, start_day, start_hr, start_min, start_sec, end_month, end_day, end_hr, end_min, end_sec;

    cout << "Search from:\n\nMonth: ";
    cin >> start_month;
    cout << "Day: ";
    cin >> start_day;
    cout << "Hour: ";
    cin >> start_hr;
    cout << "Min: ";
    cin >> start_min;
    

  int valuemin, valuemax;




  return 0;

  
}
