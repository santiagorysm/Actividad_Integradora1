//Escrito por Santiago Reyes Moran - A01639030 y Lucas Wong Mang - A01639032
//23/11/2021

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
#include "MaxHeap.h"
#include "registroGrafo.h"
#include "Graph.h"
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
    void imprimeGrafo(); //Utiliza el metodo de .print para los objetos tipo registroGrafo, lo cual imprime todo el grafo

private:    
    //MaxHeap de todos los registrosGrafo individuales (Pares de IP y grado)
    MaxHeap<RegistroGrafo> listaDeRegistros{MaxHeap<RegistroGrafo>(13370)}; 
    //Grafo en el que guardaremos las IPs junto con sus listas de adyacencias
    Graph grafoRegistros;
    //Se guarda la cantidad de Ips
    int ips = 0;
    //Se guarda la cantidad de instancias
    int instancias = 0;
    //El size de listaDeRegistros
    //Unordered map para contabilizar las repeticiones de las distintas Ips
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
    //Checamos si el archivo a leer existe, si no existe arrojamos una excepcion (Lo agregue por la retroalimentacion de la actividad anterior)
    std::ifstream infile(nombreTxt);
    if(!infile.good()){
            throw std::invalid_argument("El archivo '"+nombreTxt+"' no existe, trate con otro archio" );

    }
      else{
      std::ifstream lineCatcher(nombreTxt);
      std::string line, atrtibute;
      int counter = 0;
      //Este while se corre para cada linea dentro del archivo de texto
      bool hasFirstLine=false;
      while (std::getline(lineCatcher, line))
      {
          //En la primera fila se lee la cantidad de ips y de instancias
          if (ips == 0 && instancias == 0 && !hasFirstLine)
          {
              char str[500];
              strcpy(str, line.c_str());
              char *ptr; // declare a ptr pointer
              ptr = strtok(str, " ");

              ips = stoi(ptr);
              ptr = strtok(NULL, " ");
              instancias = stoi(ptr);
              hasFirstLine=true;
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
              int day = stoi(ptr);

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
              //Quitamos los ultimos 5 caracteres (para tener la IP sin el puerto)
              ipOrigen.pop_back();
              ipOrigen.pop_back();
              ipOrigen.pop_back();
              ipOrigen.pop_back();
              ipOrigen.pop_back();

              //Se crea un objeto tipo Registro (que representa la IP destino)
              Registro objetoIpDestino(m,day,time,ipD,err);
              
              //Se agrega el objeto tipo registro al grafo en la lista de adyacencia de la ip origen
              grafoRegistros.addToList(ipOrigen,objetoIpDestino);


          }
          //Si la fila es menor a 16 caracteres entonces es una ip
          else
          {
              grafoRegistros.addToGraph(line);
          }

      }
      lineCatcher.close();

      
      //Recorremos el unordered map cuando ya este terminado para crear el heap
      std::unordered_map<std::string, std::vector<Registro>> listaGrafoCompleto=grafoRegistros.getListaAdjacencia();
      for (auto it = listaGrafoCompleto.cbegin(); it != listaGrafoCompleto.cend(); ++it)
      {
          //Se declara el objeto tipo RegistroGrafo
          RegistroGrafo nuevoReg((*it).first, (*it).second.size());
          //Y metemos el objeto al heap
          listaDeRegistros.push(nuevoReg);


      }
      }
}

//Esta funcion escribe el grafo completo en un archivo .txt con un nombre que se pasa como parametro
template <class T>
void Bitacora<T>::escribeGrafo(std::string nombreArchivo)
{
    ofstream myfile;
    myfile.open(nombreArchivo);
    //Obtenemos el unordered map del grafo con .getListaAdjacencia
    std::unordered_map<std::string, std::vector<Registro>> listaGrafoCompleto=grafoRegistros.getListaAdjacencia();
    for (auto it = listaGrafoCompleto.cbegin(); it != listaGrafoCompleto.cend(); ++it)
    {
        //Declaramos un objeto y lo escribimos en el archivo en su forma de texto con .txtFormat
        RegistroGrafo nuevoReg((*it).first, (*it).second.size());
        myfile << nuevoReg.txtFormat() << "\n";
    }
    myfile.close();
}

template <class T>
void Bitacora<T>::imprimeGrafo()
{
    //Obtenemos el unordered map del grafo con .getListaAdjacencia
    std::unordered_map<std::string, std::vector<Registro>> listaGrafoCompleto=grafoRegistros.getListaAdjacencia();
    for (auto it = listaGrafoCompleto.cbegin(); it != listaGrafoCompleto.cend(); ++it)
    {
        //Declaramos un objeto y lo imprimimos con .print
        RegistroGrafo nuevoReg((*it).first, (*it).second.size());
        nuevoReg.print();
    }
}

//Esta funcion imprime los 5 registros con mayor grado y los bootmasters. Tambien escribe los top 5 registros en un .txt
template <class T>
void Bitacora<T>::getTop5Registros()
{
    std::cout<<"Las 5 IPs con mayor grado: "<<std::endl;
    //Declaramos un vector en en cual guardar los bootmasters
    std::vector<RegistroGrafo> bootMasters;
    //Ahora si comenzamos a guardar y imprimir los registros con el Max Heap
    ofstream myfile;
    myfile.open("mayores_grados_ips.txt");
    RegistroGrafo dato = listaDeRegistros.top();
    bootMasters.push_back(dato);
    for (int i = 0; i < 5; i++)
    {
        std::cout << dato.txtFormat() << std::endl;
        myfile << dato.txtFormat() << "\n";
        listaDeRegistros.pop();
        dato = listaDeRegistros.top();
        if (!(dato<bootMasters.back())&dato<=bootMasters.back()){
          bootMasters.push_back(dato);
        }
    }
    myfile.close();
    //Imrpimimos los bootmasters
    std::cout<<std::endl;
    std::cout<<"-------------- BOOTMASTERS --------------"<<std::endl;
    for(int j=0;j<bootMasters.size();j++){
      bootMasters[j].print();
    }
        std::cout<<"-----------------------------------------"<<std::endl;
}

