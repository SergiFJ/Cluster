/** @file Procesador.cc
    @brief Implementación de la clase Procesador.
*/

#include "Procesador.hh"


Procesador::Procesador(int m){
  memoria_total = m;
  memoria_libre = m;
  espacio[m].insert(0);

}


void Procesador::compactar_memoria() {
  if (memoria.size() != 0 and memoria_libre != memoria_total){ //Hay procesos y no ocupan toda la memoria
    map<int, Proceso>::iterator it = memoria.begin();
    espacio.clear();
    identificador_memoria.clear();
    int posicion = 0; //variable que indica la posicion de memoria donde se tiene que poner el proceso
    while (it != memoria.end()) {
      identificador_memoria.insert({it->second.consultar_id(), posicion});
      if (it->first != posicion){ //mira que no este el proceso en la posicion correcta
        memoria.insert({posicion,it->second});
        it = memoria.erase(it);
      }
      else ++it;
      posicion += prev(it)->second.consultar_memoria();
      }
    if (posicion != memoria_total) espacio[memoria_total - posicion].insert(posicion);
  }
}


void Procesador::baja_proceso_procesador(int identificador) {
  map<int,int>::iterator it1 = identificador_memoria.find(identificador);
  map<int,Proceso>::iterator it2 = memoria.find(it1->second);

  if (memoria.size() == 1){ //si solo hay un proceso en el procesador
    memoria_libre = memoria_total;
    memoria.clear();
    it2 = memoria.end();
    identificador_memoria.clear();
    espacio.clear();
    espacio[memoria_total].insert(0);
  }
  else { //si hay mas de un proceso
    map<int,Proceso>::iterator it_previo = memoria.begin();
    map<int,Proceso>::iterator it_posterior = next(it2);
    map<int,set<int>>::iterator it_espacio = espacio.begin();
    int previo, posterior;
    if (it2 != memoria.begin()){ //si el proceso que apunta it2 no es el primero
      it_previo = prev(it2);
      previo = it_previo->first + it_previo->second.consultar_memoria();
    }
    else {
      previo = 0;
    }

    if (it_posterior == memoria.end()){ //si el proceso que apunta it2 es el ultimo
      posterior = memoria_total;
    }
    else {
      posterior = it_posterior->first;
    }
    
    int first = it2->first;
    if (previo != first){ //si hay un espacio delante
      it_espacio = espacio.find(first - previo);
      it_espacio->second.erase(previo);
      if (it_espacio->second.empty()) espacio.erase(it_espacio);
    }
    int l = first + it2->second.consultar_memoria();
    if (posterior != l){ //si hay un espacio detras
      it_espacio = espacio.find(posterior - l);
      it_espacio->second.erase(l);
      if (it_espacio->second.empty()) espacio.erase(it_espacio);
    }
    espacio[posterior-previo].insert(previo);
    memoria_libre += it2->second.consultar_memoria();
    it2 = memoria.erase(it2);
    identificador_memoria.erase(it1);
  }
}


void Procesador::reducir_tiempo(int t){
  map<int,Proceso>::iterator it = memoria.begin();
  while (it != memoria.end()){
    (it -> second).avanzar_tiempo_proceso(t);
    ++it;
    if ((prev(it) -> second).consultar_tiempo() <= 0){
      baja_proceso_procesador(prev(it)->second.consultar_id());
    }
  }
}


bool Procesador::hay_espacio(const Proceso& p, int& n) const{
  map<int,set<int>>::const_iterator it = espacio.lower_bound(p.consultar_memoria());
  if (it == espacio.end()) return false;
  n = it->first; //guarda en n el hueco mas ajustado donde cabe el proceso p
  return true;
}


bool Procesador::se_puede_colocar_proceso(const Proceso& p){
  map<int, set<int>>::iterator it2 = espacio.begin();
  int m = p.consultar_memoria(); //memoria que ocupa el proceso

  if (m > memoria_libre) return false; //no cabe proceso
  if (memoria_total == memoria_libre) {//mira espacio al inicio
    memoria.insert({0,p});
    identificador_memoria.insert({p.consultar_id(), 0});
    espacio.clear();
    if (memoria_total - m != 0) espacio[memoria_total - m].insert(m); //si el proceso no ocupa todo el espacio guarda el hueco que queda
    memoria_libre -= m;
    return true;
  }

  map<int, set<int>>::iterator it = espacio.lower_bound(m); //busca el hueco mas ajustado para el proceso
  if (it != espacio.end()){ //mira si existe el hueco
    memoria_libre -= m;
    memoria.insert({*(it->second.begin()), p});
    identificador_memoria.insert({ p.consultar_id(), *(it->second.begin())});
    map<int,Proceso>::iterator it1 = memoria.find(*(it->second.begin()));
    int posicion = m + it1->first; //espacio donde ira el hueco
    if (next(it1) == memoria.end() and (memoria_libre != 0)) {
      espacio[memoria_total - posicion].insert(posicion);
    }
    else {
      if (memoria_libre != 0) espacio[next(it1)->first - posicion].insert(posicion);
    }
    it->second.erase(it->second.begin());
    if (it->second.empty()) espacio.erase(it); //si no quedan huecos de ese tamaño, borra el tamaño del mapa
    
    return true;
  }
  return false;
}


int Procesador::consultar_size_memoria() const{
  return memoria.size();
}


int Procesador::consultar_memoria_libre() const{
  return memoria_libre;
}


bool Procesador::contiene_proceso(int identificador) const{
  if (identificador_memoria.find(identificador) == identificador_memoria.end()) return false;
  return true;
}


void Procesador::imprimir_procesador() const{
  map<int,Proceso>::const_iterator it = memoria.begin();
  while (it != memoria.end()){
    cout << it->first << ' ';
    it->second.escritura();
    ++it;
  }
}