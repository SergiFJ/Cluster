/** @file program.cc
    @brief Main de la práctica.
*/

/** @mainpage Práctica PRO2
 * Simulación del funcionamiento de una arquitectura multiprocesador, donde cada procesador 
 * trabaja exclusivamente con su propia memoria y puede ejecutar más de un proceso simultáneamente.
 * A la vez, tenemos una area de espera con sus prioridades y sus procesos pendientes que esperan
 * ser enviados al cluster.
*/

#include "Lista_procesos.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

int main(){
    Cluster clust;
    clust.configurar_cluster(); //añade la informacion del cluster
    Lista_procesos lista;
    lista.leer_lista(); //lee las prioridades iniciales
    string com;
    cin >> com;
    while (com != "fin"){
        //procesa comando

        if (com == "configurar_cluster" or com == "cc"){
            clust.configurar_cluster();
            cout << '#' << com << endl;
        }

        else if (com == "modificar_cluster" or com == "mc"){
            string p;
            cin >> p; 
            int error = clust.modificar_cluster(p);
            if (error == 0) cout << '#' << com << ' '  << p << endl;
            else if (error == 1) cout << '#' << com << ' '  << p << endl << "error: no existe procesador" << endl;
            else if (error == 2) cout << '#' << com << ' '  << p << endl << "error: procesador con procesos" << endl;
            else if (error == 3) cout << '#' << com << ' '  << p << endl << "error: procesador con auxiliares" << endl;
        }

        else if (com == "alta_prioridad" or com == "ap"){
            string nombre;
            cin >> nombre;
            int error = lista.alta_prioridad(nombre);
            if (error == 0) cout << '#' << com << ' ' << nombre << endl;
            else if (error == 1) cout << '#' << com << ' ' << nombre << endl << "error: ya existe prioridad" << endl;
        }

        else if (com == "baja_prioridad" or com == "bp"){
            string nombre;
            cin >> nombre;
            int error = lista.baja_prioridad(nombre);
            if (error == 0) cout << '#' << com << ' ' << nombre << endl;
            else if (error == 1) cout << '#' << com << ' ' << nombre << endl << "error: no existe prioridad" << endl;
            else if (error == 2) cout << '#' << com << ' ' << nombre << endl << "error: prioridad con procesos" << endl;
        }

         else if (com == "alta_proceso_espera" or com == "ape"){
            string nombre;
            cin >> nombre;
            Proceso p;
            p.leer();
            int error = lista.alta_proceso_espera(nombre, p);
            if (error == 0) cout << '#' << com << ' ' << nombre << ' ' << p.consultar_id() << endl;
            else if (error == 1) cout << '#' << com << ' ' << nombre << ' ' << p.consultar_id() << endl << "error: no existe prioridad" << endl;
            else if (error == 2) cout << '#' << com << ' ' << nombre << ' ' << p.consultar_id() << endl << "error: ya existe proceso" << endl;
        }

        else if (com == "alta_proceso_procesador" or com == "app"){
            string identificador;
            cin >> identificador;
            Proceso pr;
            pr.leer();
            int error = clust.alta_proceso(identificador, pr);
            if (error == 0) cout << '#' << com <<  ' ' << identificador << ' ' << pr.consultar_id() << endl;
            else if (error == 1) cout << '#' << com <<  ' ' << identificador << ' ' << pr.consultar_id() << endl << "error: no existe procesador" << endl;
            else if (error == 2) cout << '#' << com <<  ' ' << identificador << ' ' << pr.consultar_id() << endl << "error: ya existe proceso" << endl;
            else if (error == 3) cout << '#' << com <<  ' ' << identificador << ' ' << pr.consultar_id() << endl << "error: no cabe proceso" << endl;
        }

        else if (com == "baja_proceso_procesador" or com == "bpp"){
            string identificador;
            int pro;
            cin >> identificador >> pro;
            int error = clust.baja_proceso(identificador, pro);
            if (error == 0) cout << '#' << com << ' ' << identificador << ' ' << pro << endl;
            else if (error == 1) cout << '#' << com << ' ' << identificador << ' ' << pro << endl << "error: no existe procesador" << endl;
            else if (error == 2) cout << '#' << com << ' ' << identificador << ' ' << pro << endl << "error: no existe proceso" << endl;
        }

        else if (com == "enviar_procesos_cluster" or com == "epc"){
            int n;
            cin >> n;
            cout << '#' << com << ' ' << n << endl;
            lista.enviar_procesos_cluster(clust, n);
        }

        else if (com == "avanzar_tiempo" or com == "at"){
            int t;
            cin >> t;
            cout << '#' << com << ' ' << t << endl;
            clust.avanzar_tiempo(t);
        }

        else if (com == "imprimir_prioridad" or com == "ipri"){
            string p;
            cin >> p;
            cout << '#' << com << ' ' << p << endl;
            int error = lista.imprimir_prioridad(p);
            if (error == 1) cout << "error: no existe prioridad" << endl;
        }

        else if (com == "imprimir_area_espera" or com == "iae"){
            cout << '#' << com << endl;
            lista.imprimir_area_espera();
        }

        else if (com == "imprimir_procesador" or com == "ipro"){
            string identificador;
            cin >> identificador;
            cout << '#' << com << ' ' << identificador << endl;
            int error = clust.imprimir_procesador(identificador);
            if (error == 1) cout << "error: no existe procesador" << endl;
        }

        else if (com == "imprimir_procesadores_cluster" or com == "ipc"){
            cout << '#' << com << endl;
            clust.imprimir_procesadores_cluster();
        }

        else if (com == "imprimir_estructura_cluster" or com == "iec"){
            cout << '#' << com;
            clust.iec();
        }

        else if (com == "compactar_memoria_procesador" or com == "cmp") {
            string identificador;
            cin >> identificador;
            int error = clust.compactar_memoria_procesador(identificador);
            if (error == 0) cout << '#' << com << ' ' << identificador << endl;
            if (error == 1) cout << '#' << com << ' ' << identificador << endl << "error: no existe procesador" << endl;
        }

        else if (com == "compactar_memoria_cluster" or com == "cmc"){
            cout << '#' << com << endl;
            clust.compactar_memoria_cluster();
        }
        cin >> com;
    }
}
