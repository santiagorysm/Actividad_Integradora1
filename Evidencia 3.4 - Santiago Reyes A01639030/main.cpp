#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "math.h"
#include "registro.h"
#include "bitacora.h"

int main()
{

    //Esto lo tengo que meter en la bitacora nueva
    //Lo primero que se hace es declarar un objeto tipo Bitacora, utilizando el nombre del archivo a leer como parametro

    Bitacora<Registro> bit("bitacoraHeap.txt");

    //Primero ordenamos la bitacora (se ordena segun las Ip's)
    bit.ordenaBitacora();

    //Se puede mandar a imprimir la bitacora utilizando el metodo imprimeBitacora();

    //Escribimos la bitacora en un archivo txt llamado "bitacora_ordenada.txt"
    bit.writeBitacora();

    //Se puede ordenar el heap por la cantidad de veces que se presenta una IP utilizando ordenaIpRegistry();
    //Y tambien se puede imprimir la misma usando el metodo imprimeIpRegistry();

    //Se manda a llamar writeTop5Ips() que utiliza .top y .pop
    //para obtener y extraer las 5 Ips con mayores accesos, escribirlas en "ips_con_mayor_acceso.txt" e imprimirlas
    std::cout << std::endl
              << "Las 5 IP's con mayor numero de accesos:" << std::endl
              << std::endl;
    bit.getTop5Ips();
    std::cout << std::endl;
}
