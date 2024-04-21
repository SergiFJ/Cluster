/** @file Procesador.hh
    @brief Especificación de la clase Procesador.
*/

#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
using namespace std;
#endif


/** @class Procesador
    @brief Representa un procesador. 

    Procesadores con su memoria y su estructura de procesos. Puede usarse para saber la cantidad
    de procesos y la memoria que tiene.
*/
class Procesador
{

private:
  /** @brief Memoria total que tiene el procesador.*/
  int memoria_total;                  
  /** @brief Cantidad de memoria restante que le queda.*/
  int memoria_libre;                  
  /** @brief Mapa de los procesos que tiene el cluster, su key es la posicion inicial donde estan situados de la memoria.*/
  map<int,Proceso> memoria;
  /** @brief Mapa que tiene el identificador de cada proceso y su primera posicio de memoria.*/
  map<int,int> identificador_memoria;
  /** @brief Mapa de los huecos vacios y un set de las posiciones iniciales que les prosiguen un hueco de esa cantidad.*/
  map<int,set<int>> espacio;


public:


  //Constructores


  /** @brief Constructora con el parametro implicito de la memoria que tiene leido.
   * 
   * \pre <em>m es un entero positivo</em>
   * @param m Valor que tendra el parametro implicito de la memoria del procesador.
   * \post Devuelve un procesador con memoria m.
   */
  Procesador(int m);


  //Modificadores


  /** @brief Se compacta los procesos del procesador.
   * 
      \pre <em>Cierto.</em>
      \post Devuelve el procesador con sus procesos al principio de memoria sin dejar huecos entre ellos, sin solaparse
            y respetando el orden inicial. Modificando asi, todos los parametros implicitos para que tengan las nuevas posiciones.
  */
  void compactar_memoria();

  /** @brief Elimina un proceso con el identificador pasado como parametro del procesador.
   * 
      \pre <em>Cierto.</em>
      \param identificador Valor del parametro implicito que identifica el proceso que se elimina.
      \post Devuelve el procesador sin el proceso con el identificador leido y devuelve el iterador apuntando al siguiente elemento.
  */
  void baja_proceso_procesador(int identificador);

  /** @brief Reduce el tiempo de todos los procesos del procesador.
   * 
   * \pre <em>t es un entero positivo</em>
   * @param t Tiempo que se reduce los parametros implicitos que indica el tiempo de duracion de los procesos.
   * \post Devuelve el procesador con todos sus procesos con el tiempo reducido en t y si el tiempo pasa a ser 
   *       igual o menor a 0 se han eliminado los procesos.
   */
  void reducir_tiempo(int t);

  /** @brief Mira si se puede poner p en el procesador y si se puede colocar lo coloca.
   * 
   * \pre <em>Cierto.</em>
   * @param p Proceso que se intenta colocar.
   * \post Devuelve un booleano diciendo si se puede o no poner el proceso. Si se puede añade el proceso al procesador.
   * @return true si se puede colocar p en el procesador.
   * @return false si no se puede colocar p en el procesador.
   */
  bool se_puede_colocar_proceso(const Proceso& p);


  //Consultores


  /** @brief Mira si hay un hueco en la memoria del procesador que quepa el proceso p y guarda en n el tamaño del proceso.
   * 
   * \pre <em>Cierto.</em>
   * @param p Proceso que se mira si se puede poner en un hueco de la memoria del procesador.
   * @param n Entero que tendra el valor del hueco mas ajustado si se puede poner el proceso en el procesador.
   * \post Devuelve un booleano indicando si hay espacio o no y pone en n el tamaño del hueco de memoria mas ajustado si cabe el proceso.
   * @return true si se puede poner el proceso en el procesador.
   * @return false si no se puede poner el proceso en el procesador.
   */
  bool hay_espacio(const Proceso& p, int& n) const;

  /**
   * @brief Dice la cantidad de procesos que tiene el porcesador ejecutandose.
   * 
   * \pre <em>Cierto.</em>
   * \post Devuelve un entero de la cantidad de procesos que tiene el procesador.
   * @return int La cantidad de procesos que tiene el parametro implicito de la estructura del procesador.
   */
  int consultar_size_memoria() const;

  /** @brief Lee el entero de la memoria libre del procesador.
   * 
   * \pre <em>Cierto.</em>
   * \post Devuelve un entero de la memoria libre que le queda al procesador.
   * @return int El valor de la memoria libre.
   */
  int consultar_memoria_libre() const;

  /** @brief Mira si el procesador tiene un proceso con el mismo identificador que se pasa como parametro.
   * 
   * \pre <em>Cierto.</em>
   * @param identificador Identificador del proceso que se busca.
   * \post Devuelve un booleano que indica si se ha encontrado el proceso.
   * @return true si existe un proceso con con el mismo identificador que el del canal de entrada.
   * @return false si no existe un proceso con con el mismo identificador que el del canal de entrada.
   */
  bool contiene_proceso(int identificador) const;


  //Escritura y lectura


  /** @brief Escribe la informacion de los procesos que se ejecutan en un procesador.
   * 
   * \pre <em>Cierto.</em>
   * \post Escribe toda la informacion de los procesos que se ejecutan en ese procesador 
           por orden creciente en la posicion de memoria.
  */
  void imprimir_procesador() const;
  

};
#endif