//Escrito por Santiago Reyes Moran - A01639030 y Lucas Wong Mang - A01639032
//04/12/2021

#ifndef BITACORA_H
#define BITACORA_H
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include <climits>
#include "Graph.h"
#include "resumenIP.h"
#include <stdexcept>
#include <filesystem>

//++++++++++++++++++++++++++++++++++++++++Definicion de la clase++++++++++++++++++++++++++++++++++++++++
template <class T>
class Bitacora
{
public:
    Bitacora();
    Bitacora(std::string nombreTxt);

    //Metodos para la bitacora

    void getTop5Registros();        //Escribe e imprime los Ips con mas repeticiones usando .pop() y .top() del max heap
    void escribeGrafo(std::string); //Escribe todo el grafo completo (Los pares de IPs y Grados)
    void imprimeGrafo();            //Utiliza el metodo de .print para los objetos tipo registroGrafo, lo cual imprime todo el grafo
    void getIPSummary(std::string);

private:
    //MaxHeap de todos los registrosGrafo individuales (Pares de IP y grado)
    //Grafo en el que guardaremos las IPs junto con sus listas de adyacencias
    Graph grafoRegistros;
    //Se guarda la cantidad de Ips
    int ips = 0;
    //Se guarda la cantidad de instancias
    int instancias = 0;
    int size = 13381; //Numero primo mas cercano a 13370 (la cantidad de IPs)
    int colisiones = 0;

    //Unordered map para contabilizar las repeticiones de las distintas Ips
    void pushToHash(ResumenIP);
    int getHashIndex(std::string);
    std::vector<ResumenIP> hashTable;
};
#endif

//En el constructor default los Max Heaps se dejan vacios y el size es de 0
template <class T>
Bitacora<T>::Bitacora()
{
    hashTable.resize(size);
}

//Constructor para la clase bitacora utilizando el nombre de un archivo txt
template <class T>
Bitacora<T>::Bitacora(std::string nombreTxt)
{
    hashTable.resize(size); //Numero primo mas cercano a 13370 (la cantidad de IPs)
    //Checamos si el archivo a leer existe, si no existe arrojamos una excepcion (Lo agregue por la retroalimentacion de la actividad anterior)
    std::ifstream infile(nombreTxt);
    if (!infile.good())
    {
        throw std::invalid_argument("El archivo '" + nombreTxt + "' no existe, trate con otro archio");
    }
    else
    {
        std::ifstream lineCatcher(nombreTxt);
        std::string line, atrtibute;
        int counter = 0;
        //Este while se corre para cada linea dentro del archivo de texto
        bool hasFirstLine = false;
        while (std::getline(lineCatcher, line))
        {
            //En la primera fila se lee la cantidad de ips y de instancias
            if (ips == 0 && instancias == 0 && !hasFirstLine)
            {
                char str[500];
                strcpy(str, line.c_str());
                char *ptr; // declare a ptr pointer
                ptr = strtok(str, " ");

                ips = std::stoi(ptr);
                ptr = strtok(NULL, " ");
                instancias = std::stoi(ptr);
                hasFirstLine = true;
                continue;
            }
            //Si la linea es mayor a 16 caracteres significa que es una instancia
            if (line.length() > 16)
            {
                char str[500];
                strcpy(str, line.c_str());
                char *ptr; // declare a ptr pointer
                ptr = strtok(str, " ");

                std::string m = ptr;
                ptr = strtok(NULL, " ");
                int day = std::stoi(ptr);

                ptr = strtok(NULL, " ");
                std::string time = ptr;
                ptr = strtok(NULL, " ");
                std::string ipO = ptr;

                ptr = strtok(NULL, " ");
                std::string ipD = ptr;

                ptr = strtok(NULL, "");
                std::string err = ptr;

                std::string ipOrigen = ipO;
                std::string ipDestino = ipD;

                //Quitamos los ultimos caracteres (para tener la IP sin el puerto)
                while (ipOrigen.find(':') != std::string::npos)
                {
                    ipOrigen.pop_back();
                }

                while (ipDestino.find(':') != std::string::npos)
                {
                    ipDestino.pop_back();
                }
                //Se crea un objeto tipo Registro (que representa la IP destino)
                //Registro objetoIpDestino(m,day,time,ipD,err);

                //Se agrega el objeto tipo registro al grafo en la lista de adyacencia de la ip origen
                grafoRegistros.addToList(ipOrigen, ipDestino);
            }
            //Si la fila es menor a 16 caracteres entonces es una ip
            else
            {
                grafoRegistros.addToGraph(line);
            }
        }
        lineCatcher.close();

        //Recorremos el unordered map cuando ya este terminado para crear la tabla hash

        std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> listaGrafoCompleto = grafoRegistros.getListaAdjacencia();
        for (auto it = listaGrafoCompleto.cbegin(); it != listaGrafoCompleto.cend(); ++it)
        {
            std::vector<std::string> ipsQueAccesaron;
            std::vector<std::string> ipsAccesadas;

            //Se declara el objeto tipo RegistroGrafo
            std::string ipActual = (*it).first;
            std::vector<std::pair<std::string, int>> listaDePares = (*it).second;
            for (int i = 0; i < listaDePares.size(); i++)
            {
                std::pair<std::string, int> par = listaDePares[i];
                if (par.second == 0)
                {
                    ipsAccesadas.push_back(par.first);
                }
                else
                {
                    ipsQueAccesaron.push_back(par.first);
                }
            }

            //Ahora si creamos el objeto tipo resumen
            ResumenIP nuevoResumen(ipActual, ipsQueAccesaron, ipsAccesadas);
            //y lo metemos a la tabla hash;
            pushToHash(nuevoResumen);
        }
        std::cout << std::endl
                  << "Se termio de crear la Tabla Hash, hubo un total de " << colisiones << " colisiones, pero fueron manejadas se forma apropiada" << std::endl
                  << std::endl;
    }
}

//Complejidad: mejor caso O(1), peor caso O(log(n))
template <class T>
void Bitacora<T>::getIPSummary(std::string ipObjetivo)
{
    int hashInd = getHashIndex(ipObjetivo);
    std::cout << "La IP " << ipObjetivo << " fue encontrada en el indice " << hashInd << " de la tabla hash" << std::endl;
    hashTable[hashInd].printResumen();
    std::cout << std::endl;
}

//Complejidad: mejor caso O(1), peor caso O(log(n))
template <class T>
void Bitacora<T>::pushToHash(ResumenIP datoAInsertar)
{
    long long valorNumerico = datoAInsertar.getNumericVal();
    int posicion = valorNumerico % size;
    //En caso de que no haya colision
    if (hashTable[posicion].getDireccion() == "0.0.0.0")
    {
        //Se inserta en la tabla con la posicion calculada inicialmente
        hashTable[posicion] = datoAInsertar;
    }
    //En caso de que si haya colision
    else
    {
        colisiones++;
        int var = 1;
        int newPosicion = posicion + var;
        //Esto se corre hasta que encuentre un espacio libre dentro de la tabla hash
        while (hashTable[newPosicion].getDireccion() != "0.0.0.0")
        {
            colisiones++;
            var++;
            newPosicion = posicion + pow(var, 2);
            if (newPosicion >= size)
            {
                newPosicion = newPosicion % size;
            }
        }
        //Se inserta el objeto en la posicion encontrada
        hashTable[newPosicion] = datoAInsertar;
    }
}

//Complejidad: mejor caso O(1), peor caso O(log(n))
template <class T>
int Bitacora<T>::getHashIndex(std::string lookUpIp)
{
    //Manejo de excepcion en donde lookUpIp no existe
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> listaGrafoCompleto = grafoRegistros.getListaAdjacencia();
    //Si el count de la IP dentro del unordered map da 0, entonces es que no existe dentro del grafo ni de la tabla hash
    if (!listaGrafoCompleto.count(lookUpIp))
    {
        //Aventamos una excepcion
        throw std::invalid_argument("La IP '" + lookUpIp + "' que se trato de buscar no existe, trate con otra IP");
    }

    //Separamos la IP en sus 4 partes distintas
    int ip1, ip2, ip3, ip4;
    char charArr[25];
    strcpy(charArr, lookUpIp.c_str());
    char *ipPointer;
    ipPointer = strtok(charArr, ".");
    ip1 = atoi(ipPointer);
    ipPointer = strtok(NULL, ".");
    ip2 = atoi(ipPointer);
    ipPointer = strtok(NULL, ".");
    ip3 = atoi(ipPointer);
    ipPointer = strtok(NULL, "");
    ip4 = atoi(ipPointer);

    //Convertimos la IP a un valor numerico con esta funcion
    long long resultado = (ip1 * pow(256, 3)) + (ip2 * pow(256, 2)) + (ip3 * 256) + ip4;

    //Buscamos la posicion inicial de busqueda
    int posicion = resultado % size;
    int val = 0;
    //Si la direccion del objeto en la posicion inicial de busqueda es igual a la IP que estamos buscando entonces regresamos esa posicion
    if (hashTable[posicion].getDireccion() == lookUpIp)
    {
        return posicion;
    }
    bool foundIndex = false;

    //Este loop corre infinitamente hasta que encuentre la IP deseada dentro de la tabla hash
    //No correra para siempre porque ya comprobamos que si existe dentro de la tabla hash
    while (!foundIndex)
    {
        val++;
        int newPosicion = posicion + pow(val, 2);
        //Esto corre si la posicion nueva es mayor al size de la tabla hash
        if (newPosicion >= size)
        {
            newPosicion = newPosicion % size;
        }
        //Si encontramos la IP entonces regresamos esa posicion
        if (hashTable[newPosicion].getDireccion() == lookUpIp)
        {
            foundIndex = true;
            return newPosicion;
        }
    }
    return -1;
}
