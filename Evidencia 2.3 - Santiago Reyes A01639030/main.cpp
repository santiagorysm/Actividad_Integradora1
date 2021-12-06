//Este es el main en el que se llevara a cabo la lectura y escritura del archivo de texto con los registros.
//Se crearan objetos para cada registro que se encuentra en el archivo y luego se podra consultar las fechas y horas de inicio y fin para la busqueda
//Escrito por Santiago Reyes Moran A01639030
//13/10/2021

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "math.h"
#include "bitacora.h"
#include "doubleLinkedList.h"

//Aqui comienza el main
int main()
{

    //Primeramente se crea la bitacora utilizando en nombre del archivo "bitacora.txt", el cual se nos proporciono para esta actividad
    std::string nombreDelDocumento = "bitacora.txt";
    Bitacora<Registro> bit(nombreDelDocumento);

    //Utilizamos el metodo .ordenaBitacora para aplicar el quick sort iterativo usando stacks en nuestra bitacora
    bit.ordenaBitacora();

    //Ahora que tenemos la bitacora ordenada, la escibiremos a un archivo txt llamado "bitacora_ordenada.txt"
    bit.escribeBitacora();

    //Al tener la bitacora ordenada, podemos hacer la busqueda de registros con el input del usuario:
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

    //Finalmente hacemos la busqueda de los registros, imprimimos el resultado de la busqueda y lo escribimos a un archivo llamado "resultado_busqueda.txt"
    bit.buscaRegistro(regInicio, regFinal);
}