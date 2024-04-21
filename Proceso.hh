/** @file Proceso.hh
    @brief Especificación de la clase Proceso.
*/

#ifndef _PROCESO_HH_
#define _PROCESO_HH_


#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @class Proceso
    @brief Representa un proceso. 

    Procesos con su identificador. Puede usarse para saber la memoria que ocupan y el tiempo para ejecutarse.
*/
class Proceso
{

private:
  /** @brief Identificador del proceso.*/
  int id;      
  /** @brief Memoria que ocupa.*/ 
  int memoria;  
  /** @brief Tiempo que tarda a ejecturase.*/
  int tiempo;   


public:


  //Constructores


  /** @brief Constructora por defecto. 

      Se ejecuta automaticamente al declarar un proceso.
      \pre <em>Cierto.</em>
      \post El resultado es un proceso sin informacion.
  */  
  Proceso();


  //Modificadores


  /** @brief Se avanza el tiempo del proceso un numero t.
   * 
      \pre <em>t es un entero positivo</em>
      @param t Tiempo que se tiene que avanzar el proceso.
      \post Se ha reducido el valor del parametro implicito que indica el tiempo del proceso el valor de t.  
  */
  void avanzar_tiempo_proceso(int t);


  //Consultores


  /** @brief Devuelve la duracion del proceso.
   * 
      \pre <em>Cierto.</em>
      \post Devuelve el parametro implicito que indica el tiempo del proceso.
      \return int Tiempo que dura el proceso.
  */
  int consultar_tiempo() const;


  /** @brief Devuelve el identificador del proceso.
   * 
      \pre <em>Cierto.</em>
      \post Devuelve el parametro implicito del identificador del proceso.
      \return int Identificador del proceso.
  */
  int consultar_id() const;


  /** @brief Dice la memoria que ocupa el proceso.
   * 
      \pre <em>Cierto.</em>
      \post Devuelve el parametro implicito que indica la memoria del proceso.
      \return int Memoria que ocupa el proceso.
  */
  int consultar_memoria() const;


  //Lectura y escritura();


  /** @brief Lee los datos de un proceso.
   * 
   * \pre Hay preparado en el canal estandard de entrada tres enteros no negativos.
   * \post Los parametros implicitos pasan a tener los valores leidos del canal estandard de entrada.
   */
  void leer();

  /** @brief Escribe los datos del proceso.
   * 
   * \pre <em>Cierto.<em>
   * \post Escribe los datos del proceso.
   */
  void escritura() const;


};
#endif