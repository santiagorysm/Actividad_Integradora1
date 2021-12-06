//Santiago Reyes Moran - A01639030 
//Lucas Wong Mang - A01639032
//23/11/2021

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "math.h"
#include "bitacora.h"


int main()
{
    //Lo primero que se hace es declarar un objeto tipo Bitacora, utilizando el nombre del archivo a leer como parametro
    Bitacora<RegistroGrafo> bit("bitacoraGrafos.txt");

    //Dentro de la bitacora tambien se encuentra el Max Heap, del cual podemos extraer los top 5 registros que seran guardados en el archivo "mayores_grados_ips.txt"
    //Se depliegan en pantalla estos 5 registros y tambien se indican cuales son los bootmasters (Los bootmasters serian las IPs con mayor cantidad de ataques/accesos/adyaecncias)
    bit.getTop5Registros();

    //Ahora que ya se leyo la bitacora y se creo el grafo, podemos escribir los registros del grafo (Los pares de IP y grado) en un archivo cuyo nombre pasamos de parametro
    bit.escribeGrafo("grados_ips.txt");


}
