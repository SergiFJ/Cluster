/** @file Lista_procesos.hh
    @brief Especificación de la clase Lista_procesos.
*/

#ifndef _LISTA_PROCESOS_HH_
#define _LISTA_PROCESOS_HH_

#include "Cluster.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <list>
#endif


/** @class Lista_procesos
    @brief Representa una lista de procesos en espera. 

    Puede contener procesos en espera con diferente memoria y prioridad. Puede usarse para saber los 
    siguientes procesos que entraran en el cluster.
*/
class Lista_procesos
{

private:
  /** @brief Informacion que tiene cada prioridad de la area de espera.*/
  struct Prioridad{
    /** @brief Lista de los procesos pendientes que tiene la prioridad.*/
    list<Proceso> lista;    
    /** @brief Numero de procesos que ha enviado al cluster.*/
    int procesos_cluster;   
    /** @brief Numero de rechazos de envios de procesos al cluster.*/
    int rechazos;           
  };
  /** @brief Mapa del identificador de la prioridad y los datos de esta.*/
  map<string,Prioridad> prioridades;  

  //Consultores privados


  /** @brief Mira si la prioridad con identificador id tiene un proceso en espera.
   * 
   * \pre <em>Cierto.</em>
   * @param id Identificador de la prioridad donde tiene que buscar.
   * \post Devuelve un booleano indicando si la prioridad buscada tiene procesos.
   * @return true si la prioridad tiene un proceso en espera.
   * @return false si la prioridad no tiene un proceso en espera.
   */
  bool tiene_procesos(const string& id) const;

  /** @brief Mira si la prioridad con identificador id tiene un proceso p.
   * 
   * \pre <em>Cierto.</em>
   * @param id Identificador de la prioridad donde tiene que buscar.
   * @param p Proceso p que tiene que mirar si existe en la prioridad.
   * \post Devuelve un booleano indicando si la prioridad buscada tiene el proceso p.
   * @return true si la prioridad tiene el proceso p en espera.
   * @return false si la prioridad no tiene el proceso p en espera.
   */
  bool tiene_proceso_p(const string& id,const Proceso& p) const;

  /** @brief Mira si existe la prioridad en la lista de procesos.
   * 
   * \pre <em>Cierto.</em>
   * @param id Identificador de la prioridad que se busca si existe.
   * \post Devuelve un booleano indicando si la prioridad buscada existe o no.
   * @return true si existe la prioridad en el vector.
   * @return false si no existe la prioridad en el vector.
   */
  bool existe_prioridad(const string& id) const;

  
public:

  //Constructores

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una lista de procesos.
      \pre <em>Cierto.</em>
      \post El resultado es una lista sin procesos de ningún tipo.
  */  
  Lista_procesos();


  //Modificadores


  /** @brief Añade una prioridad a la area de espera.
   * \pre <em>Cierto.</em>
   * \param nombre Identificador de la nueva prioridad.
   * \post Si no existe una prioridad con el mismo identificador, devuelve la area de espera con una nueva prioridad.
           Si no, devuelve un entero indicando el tipo de error.
   * \return int Entero que indica si ha habido error o no y el tipo de error.    
  */
  int alta_prioridad(const string& nombre);

  /** @brief Elimina una prioridad de la area de espera.
   * \pre <em>Cierto.</em>
   * \param nombre Identificador de la nueva prioridad.
   * \post Si no existe la prioridad o tiene un proceso pendiente devuelve un entero que indica el tipo de error.
           Si no, devuelve la area de espera sin la prioridad con el identificador leido.
     \return int Entero que indica si ha habido error o no y el tipo de error.  
  */
  int baja_prioridad(const string& nombre);

  /** @brief Añade un proceso p a la prioridad con identificador nombre.
   * 
   * \pre <em>Cierto.</em>
   * \param nombre Identificador de la prioridad sobre la que se intenta hacer la accion.
   * \param p Proceso que se intenta añadir a una prioridad.
   * \post Si no existe la prioridad o esa ya tiene un proceso con el mismo identificador pendiente devuelve un entero
   *       que indica el tipo de error. Si no, añade el proceso p a la prioridad.
   * \return int Entero que indica si ha habido error o no y el tipo de error.
  */
  int  alta_proceso_espera(const string& nombre,const Proceso& p);

  /** @brief Se intenta añadir n procesos al cluster.
   * 
   * \pre <em>n es un entero positivo</em>
   * \param c Es el cluster al cual se envian los procesos.
   * \param n Numero de procesos que se quieren enviar al cluster.
   * \post Se devuelve el cluster con n procesos mas si se ha podido. Si no, se devuelve con los procesos
           que podia ejecutar con maxima prioridad.
  */
  void enviar_procesos_cluster(Cluster& c, int n);


  //Escritura y lectura


  /**
   * @brief Lee una lista de prioridades.
   * 
   * \pre <em>Cierto.</em>
   * \post Devuelve la area de espera leida con diferentes prioridades.
   */
  void leer_lista();

  /** @brief Escribe la informacion de la prioridad.
   * 
   * \pre <em>Cierto.</em>
   * \param id Identificador de la prioridad que se tiene que imprimir.
   * \post Si no existe la prioridad con identificador id devuelve error. Si no, escribe los procesos pendientes,
           numero de procesos de la prioridad colocados en el cluster y numero rechazos.
  */
  int imprimir_prioridad(const string& id) const;

  /** @brief Escribe todas las prioridades de la area de espera.
   * 
   * \pre <em>Cierto.</em>
   * \post Escribe todos los procesos pendientes de todas las prioridades por orden creciente de prioridad.
           Ademas de el numero de envios aceptados hacia el cluster y los rechazados.
     \return int Entero que indica si ha habido error o no y el tipo de error.
  */
  void imprimir_area_espera() const;

};
#endif
