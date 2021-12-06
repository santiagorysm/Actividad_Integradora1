//Escrito por Santiago Reyes Moran A01639030
//13/10/2021

#ifndef BITACORA_H
#define BITACORA_H
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <climits>
#include "registro.h"
#include "ipRegistro.h"
#include "MaxHeap.h"

//++++++++++++++++++++++++++++++++++++++++Definicion de la clase++++++++++++++++++++++++++++++++++++++++
template <class T>
class Bitacora
{

public:
    Bitacora();
    Bitacora(std::string nombreTxt);

    //Metodos para la bitacora
    //Varios de estos no son necesarios para la actividad pero los inclui por conveniencia y para que este mas completo el programa

    void imprimeBitacora();   //Imprime la bitacora
    void ordenaBitacora();    //Ordena la bitacora por Ips utilizando heap sort
    void writeBitacora();     //Escribe la bitacora en su estado actual como un archivo .txt
    void imprimeIpRegistry(); //Imprime los registros de Ips (la Ip y la cantidad de veces que aparece dentro del archivo)
    void ordenaIpRegistry();  //Ordena los registros de Ips en orden de cuantas veces aparecen dentro del archivo (usando heap sort)
    void writeIpRegistry();   //Escribe los registros de Ips en su estado actual dentro de un archivo .txt
    void getTop5Ips();        //Escribe los Ips con mas repeticiones usando .pop() y .top()

    void imprimeIpUnorderedMap(); //Imprime el unordered map que se utilzia para generar el heap de registros Ips

    //void escribeBitacora();

private:
    MaxHeap<Registro> listaDeRegistros{MaxHeap<Registro>(16807)}; //MaxHeap de todos los registros individuales
    MaxHeap<IpRegistro> listaDeIps{MaxHeap<IpRegistro>(735)};     //MaxHeap de los registros Ips (Las direcciones IP y sus repeticiones)

    int size;                                   //El size de listaDeRegistros
    unordered_map<std::string, int> ipRegistry; //Unordered map para contabilizar las repeticiones de las distintas Ips
};
#endif

//En el constructor default los Max Heaps se dejan vacios y el size es de 0
template <class T>
Bitacora<T>::Bitacora()
{
    size = 0;
}

//Constructor para la clase bitacora utilizando el nombre de un archivo txt
template <class T>
Bitacora<T>::Bitacora(std::string nombreTxt)
{
    std::ifstream lineCatcher(nombreTxt);
    std::string line, atrtibute;
    int counter = 0;
    std::cout << "Line catcher initiated" << std::endl;
    //Este while se corre para cada linea dentro del archivo de texto
    while (std::getline(lineCatcher, line))
    {
        char str[500];
        strcpy(str, line.c_str());
        char *ptr; // declare a ptr pointer
        ptr = strtok(str, " ");

        std::string m = ptr;
        ptr = strtok(NULL, " ");
        int day = stoi(ptr);

        ptr = strtok(NULL, " ");
        std::string time = ptr;

        ptr = strtok(NULL, " ");
        std::string adrStr = ptr;

        ptr = strtok(NULL, "");
        std::string err = ptr;

        //Creamos un nuevo registro y lo metemos dentro del MaxHeap de registros
        Registro nuevoRegistro(m, day, time, adrStr, err);
        listaDeRegistros.push(nuevoRegistro);

        std::string ipP = adrStr;
        //Quitamos los ultimos 5 caracteres (para tener la IP sin el puerto)
        ipP.pop_back();
        ipP.pop_back();
        ipP.pop_back();
        ipP.pop_back();
        ipP.pop_back();

        //Hacemos el update del unordered map
        if (ipRegistry.count(ipP))
        {
            ipRegistry[ipP]++;
        }
        else
        {
            ipRegistry.insert({{ipP, 1}});
        }
        counter++;
    }

    //Recorremos el unordered map cuando ya este terminado para crear el heap
    for (auto it = ipRegistry.cbegin(); it != ipRegistry.cend(); ++it)
    {
        IpRegistro nuevoIpReg((*it).first, (*it).second);
        listaDeIps.push(nuevoIpReg);
    }

    size = listaDeRegistros.getSize();
}

template <class T>
void Bitacora<T>::imprimeIpUnorderedMap()
{
    for (auto it = ipRegistry.cbegin(); it != ipRegistry.cend(); ++it)
    {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }
}

template <class T>
void Bitacora<T>::ordenaBitacora()
{
    listaDeRegistros.heapSort();
}

template <class T>
void Bitacora<T>::imprimeBitacora()
{
    listaDeRegistros.printMaxHeap();
}

template <class T>
void Bitacora<T>::writeBitacora()
{
    listaDeRegistros.writeMaxHeap("bitacora_ordenada.txt");
}

template <class T>
void Bitacora<T>::ordenaIpRegistry()
{
    listaDeIps.heapSort();
}

template <class T>
void Bitacora<T>::imprimeIpRegistry()
{
    listaDeIps.printMaxHeap();
}

template <class T>
void Bitacora<T>::writeIpRegistry()
{
    listaDeIps.writeMaxHeap("ips_cantidades_ordenadas.txt");
}

template <class T>
void Bitacora<T>::getTop5Ips()
{
    //Escribimos los 5 registros con mas repeticiones en un txt
    ofstream myfile;
    myfile.open("ips_con_mayor_acceso.txt");
    IpRegistro dato = listaDeIps.top();
    for (int i = 0; i < 5; i++)
    {
        std::cout << dato.txtFormat() << std::endl;
        myfile << dato.txtFormat() << "\n";
        listaDeIps.pop();
        dato = listaDeIps.top();
    }
    myfile.close();
}
