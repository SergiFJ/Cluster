/** @file Lista_procesos.cc
    @brief Implementación de la clase Lista_procesos.
*/

#include "Lista_procesos.hh"

 
Lista_procesos::Lista_procesos() = default;


int Lista_procesos::alta_prioridad(const string& nombre){
  if (existe_prioridad(nombre)) return 1;
  Prioridad x{};
  prioridades.insert({nombre,x});
  return 0;
}


int Lista_procesos::baja_prioridad(const string& nombre){
  if (not existe_prioridad(nombre)) return 1;
  if (tiene_procesos(nombre)) return 2;
  prioridades.erase(nombre);
  return 0;
}


int Lista_procesos::alta_proceso_espera(const string& nombre,const Proceso& p){
  if (not existe_prioridad(nombre)) return 1;
  if (tiene_proceso_p(nombre, p)) return 2;
  map<string,Prioridad>::iterator it = prioridades.find(nombre);
  it->second.lista.push_back(p);
  return 0;
}


void Lista_procesos::enviar_procesos_cluster(Cluster& c, int n){  
  map<string,Prioridad>::iterator it = prioridades.begin();

  while (n != 0 and it != prioridades.end()){
    list<Proceso>::iterator it_lista = it->second.lista.begin();
    int s = it->second.lista.size();
    int i = 0;
    while (i < s and n != 0){
      if (c.anadir_proceso(*(it_lista))){
        --n;
        ++(it->second.procesos_cluster);
      }
      
      else {
        ++(it->second.rechazos);
        it->second.lista.push_back(*(it_lista));
      }
      ++i;
      it_lista = it->second.lista.erase(it_lista);
    }
    ++it;
  }
}


bool Lista_procesos::existe_prioridad(const string& id) const{
  if (prioridades.find(id) == prioridades.end()) return false;
  return true;
}


bool Lista_procesos::tiene_procesos(const string& id) const{
  map<string,Prioridad>::const_iterator it = prioridades.find(id);
  if (it->second.lista.empty()) return false;
  return true; 
}


bool Lista_procesos::tiene_proceso_p(const string& id,const Proceso& p) const{
  map<string,Prioridad>::const_iterator it1 = prioridades.find(id);
  list<Proceso>::const_iterator it2 = (it1->second).lista.begin();  
  while (it2 != it1->second.lista.end()){
    if ((*it2).consultar_id() == p.consultar_id()) return true;
    ++it2;
  }
  return false;
}


void Lista_procesos::leer_lista(){
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i){
    Prioridad x{};
    string s;
    cin >> s;
    prioridades.insert({s,x});
  }
}


int Lista_procesos::imprimir_prioridad(const string& id) const{
  if (not existe_prioridad(id)) return 1;
  map<string,Prioridad>::const_iterator it1 = prioridades.find(id);
  list<Proceso>::const_iterator it2 = it1->second.lista.begin();
  while (it2 != it1->second.lista.end()){
    (*it2).escritura();
    ++it2;
  }
  cout << it1->second.procesos_cluster << ' ' << it1->second.rechazos << endl;
  return 0;
}


void Lista_procesos::imprimir_area_espera() const{
  map<string,Prioridad>::const_iterator it1 = prioridades.begin();
  while (it1 != prioridades.end()){
    cout << it1-> first << endl;
    list<Proceso>::const_iterator it2 = it1->second.lista.begin();
    while (it2 != it1->second.lista.end()){
      (*it2).escritura();
      ++it2;
    }
  cout << it1->second.procesos_cluster << ' ' << it1->second.rechazos << endl;
  ++it1;
  }
}