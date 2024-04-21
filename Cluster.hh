/** @file Cluster.hh
    @brief Especificación de la clase Cluster.
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "Procesador.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <list>
#endif


/** @class Cluster
    @brief Representa un arbol de procesadores. 
    
    Puede contener diversos procesadores. Puede usarse para saber como estan estructurado los procesadores
*/
class Cluster
{

private:
  /** @brief Estructura de los procesadores.*/
  BinTree<string> cluster;
  /** @brief Mapa de los procesadores, la key es el identificador de cada procesador.*/
  map<string, Procesador> lista;
  /** @brief  Mapa de las posiciones que ocupan los procesadores en el cluster.(double es la posicion y el string el identificador de los procesadores).*/
  map<double, string> posiciones; 


  //Consultores privados


  /** @brief Consulta el BinTree del cluster.
   * 
   * \pre <em>Cierto.</em>
   * \post Devuelve la estructua del cluster.
   * @return BinTree<string> La estructura del cluster.
   */
  BinTree<string> consultar_cluster() const;


  //Modificadores privados


  /** @brief Mira si el procesador con identificador id tiene procesadores auxiliares. Si no los tiene añade al BinTree a el BinTree b.
   * 
   * \pre <em>Cierto.</em>
   * @param a BinTree del cluster principal.
   * @param id Identificador del procesador sobre el cual se tiene que hacer la accion.
   * @param auxiliares Indica si tiene auxiliares el procesador con el identificador id.
   * @param b BinTree que se tiene que añadir.
   * \post Si tiene auxiliares se devuelve false, si no se añade el BinTree b al BinTree a a partir de la posicion que esta id.
   * @return true si existen procesadores auxiliares.
   * @return false si no existen procesadores auxiliares.
   */
  static bool tiene_auxiliares(BinTree<string>& a, const string& id, bool& auxiliares, const BinTree<string>& b);

  /** @brief Recorre el arbol del cluster e indica la posicion de cada procesador.
   * 
   * \pre <em>Cierto.</em>
   * @param n Indica la posicion del procesador que se esta mirando en ese momento en el BinTree.
   * @param a BinTree del cluster que vamos recorriendo.
   * \post modifica el mapa de posiciones de los procesadores para que todos tengan su posicion correcta.
   */
  void posiciones_procesador(double n, const BinTree<string>& a);


  //Lectura y escritura privada


  /** @brief Devuelve el cluster leido.
   * 
   * \pre <em>Cierto.</em>
   * @param a BinTree donde se va añadiendo los procesadores.
   * @param n Valor de la posicion de los procesadores.
   * \post Devuelve un BinTree<string> que sera el nuevo cluster y el mapa con sus procesadores.
   */
  void leer_cluster(BinTree<string>& a, double n);

  /** @brief Escribe la estructura del cluster.
   * 
      \pre <em>Cierto.</em>
      \param a BinTree que se tiene que imprimir.
      \post Escribe la estructura de pocesadores del cluster.
  */
  static void imprimir_estructura_cluster(const BinTree<string>& a);


public:


  //Constructores


  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un Cluster.
      \pre <em>Cierto.</em>
      \post El resultado es un cluster sin procesadores de ningún tipo.
  */  
  Cluster();


  //Modificadores


  /** @brief Añade un nuevo cluster al cluster existente a cambio de un procesador existente.
   * 
   * \pre <em>Cierto.</em>
   * \param identificador String que indica el procesador que se cambia por un nuevo cluster.
   * \post Devuelve un entero que indica un error si no existe un procesador con ese identificador o si tienen procesos en ejecucion
   *       o si tiene procesadores auxiliares. Si no, se modifica el cluster para sustituya el procesador por un nuevo cluster.
   * \return int Entero que indica si hay un error y el tipo que es.
  */
  int modificar_cluster(const string& identificador);

  /** @brief Se compacta los procesos del procesador con el identificador leido.
   * 
   * \pre <em>Cierto.</em>
   * \param identificador Valor que hace referencia al identificador del procesador.
   * \post Compacta la memoria del procesador con ese identificador. Si no existe el procesador devuelve un entero con un error.
   * \return int Entero que indica si ha habido error o no y el tipo de error.
  */
  int compactar_memoria_procesador(const string& identificador);

  /** @brief Se compacta los procesos de los procesadores del cluster.
   * 
   * \pre <em>Cierto.</em>
   * \post Compacta la memoria de todos los procesadores del cluster.
  */
  void compactar_memoria_cluster();

  /** @brief Se avanza el tiempo de los procesos del cluster.
   * 
   * \pre <em>t es un entero positivo</em>
   * \param t Cantidad que se tiene que reducir el parametro implicito que hace referencia al tiempo que dura los procesos.
   * \post Se ha reducido el tiempo de los procesos del cluster el valor de t y los procesos que han terminado se eliminan.
  */
  void avanzar_tiempo(int t);

  /** @brief Elimina el proceso con identificador pro del procesador con el identificador pasado como parametro.
   * 
   * \pre <em>Cierto.</em>
   * @param identificador Identificador del procesador sobre el cual se tiene que quitar el proceso.
   * @param pro Identificador del proceso que se tiene que eliminar.
   * \post Si existe el proceso, lo quita del procesador, si no devuelve un entero que hace referencia a un error.
   * @return int Entero que indica si ha habido error o no y el tipo de error.
   */
  int baja_proceso(const string& identificador, int pro);

  /** @brief Intenta añadir el proceso pr al procesador con el identificador pasado como parametro.
  * 
  * \pre <em>Cierto.</em>
  * @param identificador Identificador del procesador.
  * @param pr Proceso que se intenta añadir al procesador.
  * \post Devuelve un entero indicando si ha habido un error y si no, se añade el proceso al procesador.
  * @return int Entero que indica si ha habido error o no y el tipo de error.
  */
  int alta_proceso(const string& identificador, const Proceso& pr);

  /** @brief Mira si se puede añadir un proceso en un procesador del cluster y si es asi busca el mejor y lo añade.
   * 
   * \pre <em>Cierto.</em>
   * @param p Proceso que se intenta añadir a un procesador del cluster des de la area de espera.
   * \post Devuelve un booleano indicando si se puede añadir el proceso o no. Si se puede, se añade el proceso en el procesador.
   * @return true si se puede añadir.
   * @return false si no se puede añadir.
   */
  bool anadir_proceso(const Proceso& p);


  //Lectura i escritura
  

  /** @brief Añade toda la informacion de un nuevo cluster.
   * 
   * \pre <em>Cierto.</em>
   * \post Devuelve un nuevo cluster con sus procesadores con las conexiones y memorias de ellos 
           y identificadores no repetidos. Si ya existia un cluster anterior este deja de existir.
  */
  void configurar_cluster();

  /** @brief Escribe la estructura del cluster.
    * 
    * \pre <em>Cierto.</em>
    * \post Escribe la estructura de pocesadores del arbol del cluster.
  */
  void iec() const;

  /** @brief Escribe los procesadores del cluster.
   * 
   * \pre <em>Cierto.</em>
   * \post Escribe todos los procesadores del cluster con id en orden creciente ademas de sus procesos.
  */
  void imprimir_procesadores_cluster() const;

  /**
  * @brief Escribe el procesador con el mismo identificador que se lee.
  * 
  * \pre <em>Cierto.</em>
  * @param identificador Identificador del procesador que se tiene que imprimir.
  * \post Imprime la estructura de memoria del procesador con el identificador pasado como parametro.
  * \return int Entero que indica si ha habido error o no y el tipo de error.
  */
  int imprimir_procesador(const string& identificador) const;

};
#endif