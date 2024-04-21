/** @file Cluster.cc
    @brief Implementación de la clase Cluster.
*/

#include "Cluster.hh"


Cluster::Cluster(){
  cluster = BinTree<string>();
}


void Cluster::posiciones_procesador(double n, const BinTree<string>& a){
  if (not a.empty()){
    posiciones.insert({n, a.value()});
    posiciones_procesador(2*n, a.left());
    posiciones_procesador(2*n+1,a.right());
  }
}


int Cluster::modificar_cluster(const string& identificador){
  map<string,Procesador>::iterator it = lista.find(identificador);
  if (it == lista.end()) return 1;
  if (it->second.consultar_size_memoria() != 0) return 2;
  bool auxiliares = true;
  Cluster aux;
  aux.configurar_cluster();
  if (tiene_auxiliares(cluster, identificador, auxiliares, aux.consultar_cluster())) return 3;
  it = lista.erase(it);
  posiciones.clear();
  posiciones_procesador(1, cluster); //pone bien todas las posiciones de los procesadores del cluster.
  map<string,Procesador>::iterator it1 = aux.lista.begin();
  while (it1 != aux.lista.end()){ //insiere los nuevos procesadores
    lista.insert({it1->first,it1->second});
    ++it1;
  }
  return 0;
}


int Cluster::compactar_memoria_procesador(const string& identificador) {
  map<string,Procesador>::iterator it = lista.find(identificador);
  if (it == lista.end()) return 1;
  it->second.compactar_memoria();
  return 0;
}


void Cluster::compactar_memoria_cluster(){
  map<string,Procesador>::iterator it = lista.begin();
  while (it != lista.end()){
    it->second.compactar_memoria();
    ++it;
  }
}


void Cluster::avanzar_tiempo(int t){
  map<string, Procesador>::iterator it = lista.begin();
  while (it != lista.end()){
    (it -> second).reducir_tiempo(t);
    ++it;
  }
}


int Cluster::baja_proceso(const string& identificador, int pro){
  map<string,Procesador>::iterator it = lista.find(identificador);
  if (it == lista.end()) return 1;
  if (not it->second.contiene_proceso(pro)) return 2;
  it->second.baja_proceso_procesador(pro);
  return 0;
}


int Cluster::alta_proceso(const string& identificador, const Proceso& pr){
  map<string,Procesador>::iterator it = lista.find(identificador);
  if (it == lista.end()) return 1;
  if (it->second.contiene_proceso(pr.consultar_id())) return 2;
  if (not it->second.se_puede_colocar_proceso(pr)) return 3;
  return 0;
}


bool Cluster::anadir_proceso(const Proceso& p){
  map<double,string>::iterator it = posiciones.begin();
  map<string,Procesador>::iterator itL_insertar = lista.begin(); 
  unsigned int hueco = unsigned(-1); //guarda el mayor valor posible
  
  while (it != posiciones.end()){
    int n = 0; //futuro valor del hueco mas ajustado donde cabe el proceso en el procesador que se esta mirando.
    map<string,Procesador>::iterator it_lista = lista.find(it->second);
    if (it_lista->second.hay_espacio(p,n) and not it_lista->second.contiene_proceso(p.consultar_id())){
      if (n <= hueco){ 
        if (n < hueco){//mira si el nuevo hueco es mas ajustado que el mejor de los anteriores
          hueco = n;
          itL_insertar = it_lista;
        }
        else if (it_lista->second.consultar_memoria_libre() > itL_insertar->second.consultar_memoria_libre()){
          hueco = n;
          itL_insertar = it_lista;
        }
      }
    }
    ++it;
  }
  if (hueco == unsigned(-1)) return false;
  itL_insertar->second.se_puede_colocar_proceso(p);
  return true;
}


BinTree<string> Cluster::consultar_cluster() const{
  return cluster;
}


bool Cluster::tiene_auxiliares(BinTree<string>& a,const string& id,bool& auxiliares,const BinTree<string>& b){
  if (not a.empty()){
    if (a.value() == id) {
      if (a.left().empty() and a.right().empty()){
        auxiliares = false;
        a = b;
      }
    }
    else if (auxiliares){
      BinTree<string> right = a.right();
      BinTree<string> left = a.left();
      tiene_auxiliares(left, id, auxiliares, b);
      if (auxiliares) tiene_auxiliares(right, id, auxiliares, b);
      a = BinTree<string>(a.value(), left, right);
    }
  }
  return auxiliares;
}


void Cluster::configurar_cluster(){
  lista.clear();
  posiciones.clear();
  leer_cluster(cluster, 1);
}


void Cluster::leer_cluster(BinTree<string>& a, double n){
  string x;
  cin >> x;
  if (x != "*"){
    int m;
    cin >> m;
    Procesador z(m);
    lista.insert({x,z});
    posiciones.insert({n,x});
    BinTree<string> left;
    BinTree<string> right;
    leer_cluster(left, n*2);
    leer_cluster(right, n*2+1);
    a = BinTree<string>(x, left, right);
  }
}


void Cluster::imprimir_estructura_cluster(const BinTree<string>& a){
  if (a.empty()){
    cout << ' ';
    return;
  }
  cout << '(' << a.value();
  imprimir_estructura_cluster(a.left());
  imprimir_estructura_cluster(a.right());
  cout << ')';
}


void Cluster::iec() const{
  cout << endl;
  imprimir_estructura_cluster(cluster);
  cout << endl;
}


void Cluster::imprimir_procesadores_cluster() const{
  map<string,Procesador>::const_iterator it = lista.begin();
  while (it != lista.end()){
    cout << (it -> first) << endl;
    (it -> second).imprimir_procesador();
    ++it;
  }
}


int Cluster::imprimir_procesador(const string& identificador) const{
  map<string,Procesador>::const_iterator it = lista.find(identificador);
  if (it == lista.end()) return 1;
  it->second.imprimir_procesador();
  return 0;
}