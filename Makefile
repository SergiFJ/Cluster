OPCIONS = -std=c++11
OPCIONS1 = -std=c++11 -D_GLIBCXX_DEBUG
OPCIONS2 = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Proceso.o Procesador.o Cluster.o Lista_procesos.o
	g++ -o program.exe program.o Proceso.o Procesador.o Cluster.o Lista_procesos.o

Proceso.o:  Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS2)

Procesador.o:  Procesador.cc Procesador.hh Proceso.hh
	g++ -c Procesador.cc $(OPCIONS2)

Cluster.o:  Cluster.cc Cluster.hh Procesador.hh Proceso.hh
	g++ -c Cluster.cc $(OPCIONS2)

Lista_procesos.o: Lista_procesos.cc Lista_procesos.hh Cluster.hh Procesador.hh Proceso.hh
	g++ -c Lista_procesos.cc $(OPCIONS2)

program.o: program.cc Lista_procesos.hh Cluster.hh Procesador.hh Proceso.hh
	g++ -c program.cc $(OPCIONS2)

clean:
	rm *.o
	rm *.exe

practica.tar:
	tar -cvf practica.tar *.cc *.hh Makefile html.zip
