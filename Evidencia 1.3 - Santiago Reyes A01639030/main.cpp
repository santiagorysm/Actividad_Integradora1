//Este es el main en el que se llevara a cabo la lectura y escritura del archivo de texto con los registros.
//Se crearan objetos para cada registro que se encuentra en el archivo y luego se podra consultar las fechas y horas de inicio y fin para la busqueda

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "math.h"
#include "bitacora.h"

//Aqui comienza el main
int main()
{
    //Se declara el nombre el documento de la bitacora y con el se crea un objeto de tipo bitacora
    std::string nombreDelDocumento = "bitacora.txt";
    Bitacora bit(nombreDelDocumento);

    //Usamos .ordenaBitacora() para utilizar el metodo de ordena merge en la bitacora
    bit.ordenaBitacora();

    //Escribimos la bitacora a un archivo txt
    bit.escribeBitacora();

    //Declaracion de las variables que se deberan ingresar por parte del usuario
    std::string imes, fmes, itiempo, ftiempo;
    int idia, fdia;

    //Primero se solicita el mes de inicio
    std::cout << std::endl
              << "Cual es el mes de inicio para la busqueda (Jun, Jul, Aug, Sep, Oct)? " << std::endl;
    std::cin >> imes;

    //Se solicita el dia de inicio
    std::cout << "Cual es el dia de inicio para la busqueda? " << std::endl;
    std::cin >> idia;

    //Se solicita la hora de inicio con el formato 00:00:00
    std::cout << "Cual es la hora de inicio para la busqueda? (En formato 00:00:00)" << std::endl;
    std::cin >> itiempo;

    //Con la informacion dada se crea un nuevo objeto tipo Registro con el que se hara la busqueda binaria (se utiliza una direccion IP y un error estandar)
    Registro regInicio(imes, idia, itiempo, "0.0.0.0", "No Error");

    //Se da el indice encontrado por la busqueda binaria (el indice de inicio para la impresion de registros) que existe en la clase bitacora
    int indiceInicio = bit.buscaRegistro(regInicio);
    std::cout << "Indice de inicio: " << indiceInicio << std::endl;

    //Se solicita el mes final
    std::cout
        << "Cual es el mes de fin para la busqueda (Jun, Jul, Aug, Sep, Oct)? " << std::endl;
    std::cin >> fmes;

    //Se solicita el dia final
    std::cout << "Cual es el dia de fin para la busqueda? " << std::endl;
    std::cin >> fdia;

    //Finalmente, se solicita la hora final en formato 00:00:00
    std::cout << "Cual es la hora de fin para la busqueda? (En formato 00:00:00)" << std::endl;
    std::cin >> ftiempo;

    //Se crea un objeto con los datos de fin y se realiza la busqueda binaria con ese objeto
    Registro regFinal(fmes, fdia, ftiempo, "0.0.0.0", "No Error");

    //Regresamos el indice encontrado por la busqueda binaria de .buscaRegistro()
    int indiceFin = bit.buscaRegistro(regFinal);
    std::cout << "Indice de fin: " << indiceFin << std::endl;

    //Usamos los indices encontrados con las busquedas binarias
    bit.imprimeRango(indiceInicio, indiceFin);
}