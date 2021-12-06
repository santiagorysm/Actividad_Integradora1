//Santiago Reyes Moran - A01639030
//Lucas Wong Mang - A01639032
//04/12/2021

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
    Bitacora<ResumenIP> bit("bitacoraGrafos.txt");
    //Al tener la bitacora creada, podemos utilizar la funcion getIPSummary para obtener la informacion pertininte a una IP
    //Primero la mandamos a llamar con la IP 1.14.27.28
    bit.getIPSummary("1.14.27.28");
    //Y vuelvo a ejemplificar la funcion utilizando la IP 232.235.247.163
    bit.getIPSummary("232.235.247.163");
}
