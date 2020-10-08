//
//  main.cpp
//  Actividad 2.3
//
//  Created by Ruben Robles on 10/6/20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <unistd.h>
#include "DoublyLinkedList.h"

using namespace std;

struct Dato {
  int fecha_hora;
  string ip;
  string razon;
  Dato();
  Dato(int,string,string);
  string imprimir();
};

Dato::Dato(){
    fecha_hora = 0;
    string ip = "0";
    string razon = "0";
}
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
  if (mes == "1"){
    mes = "Jan";
  }
    else if (mes == "2"){
      mes = "Feb";
    }
    else if (mes == "3"){
      mes = "Mar";
    }
    else if (mes == "4"){
      mes = "Apr";
    }
    else if (mes == "5"){
      mes = "May";
    }
    else if (mes == "6"){
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
    else if (mes == "11"){
      mes = "Nov";
    }
    else if (mes == "12"){
      mes = "Dec";
    }
  return  mes + " " + dia + " " + hour + ":" + mins + ":" + secs + " " + ip + " " + razon;
}


int busquedaBinaria (DoublyLinkedList<Dato> &lista, int fecha_horaB, bool inicio){
  int inf = 0;
  int sup = lista.getSize() - 1;
  while ((inf <= sup)){
    int mid = (inf + sup) / 2;
    //si buscamos el primer valor del rango
    if (inicio){
      if ((lista.getData(mid).fecha_hora >= fecha_horaB) && (lista.getData(mid-1).fecha_hora < fecha_horaB)){
        return mid;
      }
      //se encuentra del lado derecho
      else if(lista.getData(mid).fecha_hora < fecha_horaB){
        inf = mid + 1;
      }
      //se encuentra del lado izquierdo
      else{
        sup = mid - 1;
      }
    }
    //si buscamos el ultimo valor que entra en el rango
    else {
      if ((lista.getData(mid).fecha_hora <= fecha_horaB) && (lista.getData(mid+1).fecha_hora > fecha_horaB)){
        return mid;
       }
       //se encuentra del lado derecho
      else if(lista.getData(mid).fecha_hora < fecha_horaB){
        inf = mid + 1;
      }
      //se encuentra del lado izquierdo
      else{
        sup = mid - 1;
      }
    }
  } return -1;
}

int main() {
    
    //leer archivo
    cout << "Reading file... ";
    fstream fin;
    //debe de ser DLL de strings
    DoublyLinkedList<string> dataRead;
    
    fin.open("bitacora.txt", ios::in);
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
      string month,date,hour,ip,razon;
      //lee el mes como string y lo cambia a numero
      int pos = (int)dataRead.getData(i).find(" ");
      string mes = dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
      if (mes=="Jan"){
        month = "1";
      }
        else if (mes=="Feb"){
          month = "2";
        }
        else if (mes=="Mar"){
          month = "3";
        }
        else if (mes=="Apr"){
          month = "4";
        }
        else if (mes=="May"){
          month = "5";
        }
        else if (mes=="Jun"){
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
        else if (mes=="Nov"){
          month = "11";
        }
        else if (mes=="Dec"){
          month = "12";
        }
      //lee el dia
      pos = (int)dataRead.getData(i).find(" ");
      string dia = dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
      int day = stoi(dia);
      //rellena los dias menores a 10 con un 0: 5 = 05
      if (day<=9){
        dia= "0" + dia;
      }
      //concatena mes y dia: Sep 7 = 907
      date = month + dia;
      //lee la hora
      pos = (int)dataRead.getData(i).find(":");
      string hora = dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
      //lee los minutos
      pos = (int)dataRead.getData(i).find(":");
      string mins = dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
      //lee los seguntos
      pos = (int)dataRead.getData(i).find(" ");
      string secs = dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
      //concatena el tiempo: 07:23:03 = 072303
      hour = hora + mins + secs;
      string date_hour = date + hour;
      int fecha_hora = std::stoi(date_hour);
      //lee la direccion ip
      pos = (int)dataRead.getData(i).find(" ");
      ip = dataRead.getData(i).substr(0,pos);
      dataRead.erase(i,0,pos + 1);
      //lee la razon de falla
      razon = dataRead.getData(i);
        
      datos.addLast(Dato(fecha_hora, ip, razon));
        
    }
    
    cout << "Done! ";
    
    cout << size << " entries were loaded." << endl;
    
    cout << "Sorting database... ";
    //ordena vector con fechas de más antigua a más reciente
    //sort(datos,0,datos.getSize()-1);
    datos.sort();
    
    cout << "Done! " << endl;
    cout << "Saving sorted database in a file... ";
    //almacena el vector ordenado en un archivo nuevo
    ofstream outdata ("output.txt");
    for (int i=0;i<datos.getSize();i++){
      outdata << datos.getData(i).imprimir() << endl;

    }
    outdata.close();
    cout << "Done! Sorted database was saved in 'output.txt'" << endl << endl;
    string start_month, start_day, start_hr, start_min, start_sec, end_month, end_day, end_hr, end_min, end_sec, reason;
      int aux, valmin, valmax, length;
      string valuemin, valuemax;
      
      bool pass = 1;
      while(pass){
          pass = 0;
          cout << "Search entries from a range. Please enter values as numbers.\n\nSearch range starts from:\n\nMonth: ";
          // --- START MONTH ---
          cin >> start_month;
          
          aux = stoi(start_month);
          
          if (aux < 1 || aux > 12){
              pass = 1;
              reason = reason + "\nStart month";
          }
          if (aux < 10 ){
              start_month = "0" + to_string(aux);
          }
          // --- START DAY ---
          cout << "Day: ";
          cin >> start_day;
          aux = stoi(start_day);
          if (aux < 1 || aux > 31){
              pass = 1;
              reason = reason + "\nStart day";
          }
          if (aux < 10){
              start_day = "0" + to_string(aux);
          }
          // --- START HOUR ---
          cout << "\nEnter time in 24 hour format:\n";
          cout << "Hour: ";
          cin >> start_hr;
          aux = stoi(start_hr);
          if (aux < 0 || aux > 23){
              pass = 1;
              reason = reason + "\nStart Hour";
          }
          if (aux == 0){
              start_hr = "00";
          }
          else if (aux < 10 ){
              start_hr = "0" + to_string(aux);
          }
          
          // --- START MINUTE ---
          cout << "Min: ";
          cin >> start_min;
          aux = stoi(start_min);
          if (aux < 0 || aux > 59){
              pass = 1;
              reason = reason + "\nStart Min";
          }
          if (aux == 0){
              start_min = "00";
          }
          else if (aux < 10){
              start_min = "0" + to_string(aux);
          }
          
          cout << "\nSearch range ends in:\n\nMonth: ";
          cin >> end_month;
          aux = stoi(end_month);
          if (aux < 1 || aux > 12){
              pass = 1;
              reason = reason + "\nEnd month";
          }
          if (aux < 10){
              end_month = "0" + to_string(aux);
          }
          cout << "Day: ";
          cin >> end_day;
          aux = stoi(end_day);
          if (aux < 1 || aux > 31){
              pass = 1;
              reason = reason + "\nEnd day";
          }
          if (aux < 10){
              end_day = "0" + to_string(aux);
          }
          cout << "\nEnter time in 24 hour format:\n";
          cout << "Hour: ";
          cin >> end_hr;
          aux = stoi(end_hr);
          if (aux < 0 || aux > 23){
              pass = 1;
              reason = reason + "\nEnd Hour";
          }
          if (aux == 0){
              end_hr = "00";
          }
          else if (aux < 10){
              end_hr = "0" + to_string(aux);
          }
          cout << "Min: ";
          cin >> end_min;
          aux = stoi(end_min);
          if (aux < 0 || aux > 59){
              pass = 1;
              reason = reason + "\nEnd Min";
          }
          if (aux == 0){
              end_min = "00";
          }
          else if (aux < 10){
              end_min = "0" + end_min;
          }
          if (pass ==1){
              cout << "\nThe following values: \n"<< reason << "\n\nAre incorrect. Please try again.\n\n";
          }
          if (pass == 0){
              valuemin = start_month + start_day + start_hr + start_min + "00";
              valuemax = end_month + end_day + end_hr + end_min + "00";
              
              valmin = stoi(valuemin);
              valmax = stoi(valuemax);
              if (valuemax < valuemin){
                  cout << "End search range cannot be greater than start search range. Please try again.\n";
                  pass = 1;
              }
          }

      }
          
      
      cout << "\nSearching entries from " << start_month << "/" << start_day << " at " << start_hr << ":" << start_min << " to " << end_month << "/" << end_day << " at " << end_hr << ":" << end_min << "...\n\n";
    sleep(3);
      int posI = busquedaBinaria(datos,valmin,true);
      int posF = busquedaBinaria(datos,valmax,false);

      if (posI == -1 || posF == -1){
        cout << "No entries found within the range." << endl;
      }
      //it will return -1 if there's nothing found
      else{
        //print every position from the search range
        for (int i=posI; i<=posF; i++){
          cout << datos.getData(i).imprimir() << endl;
        }
      }

    return 0;
}
