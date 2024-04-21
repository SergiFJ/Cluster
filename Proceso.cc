/** @file Proceso.cc
    @brief Implementación de la clase Proceso.
*/

#include "Proceso.hh"

  
Proceso::Proceso(){
  id = 0;
  memoria = 0;
  tiempo = 0;
}


void Proceso::avanzar_tiempo_proceso(int t){
  tiempo -= t;
}


int Proceso::consultar_tiempo() const{
  return tiempo;
}


int Proceso::consultar_id() const{
  return id;
}


int Proceso::consultar_memoria() const{
  return memoria;
}


void Proceso::leer(){
  cin >> id >> memoria >> tiempo;
}


void Proceso::escritura() const{
  cout << id << ' ' << memoria << ' ' << tiempo << endl;
}