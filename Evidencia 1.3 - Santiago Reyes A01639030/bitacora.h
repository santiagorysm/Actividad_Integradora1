#ifndef BITACORA_H
#define BITACORA_H
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include "registro.h"

//++++++++++++++++++++++++++++++++++++++++Algoritmos de Ordenamiento y de Busqueda++++++++++++++++++++++++++++++++++++++++
//Esta es la funcion merge que se manda a llamar dentro del merge sort
void merge(std::vector<Registro> &vec, int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto *leftArray = new Registro[subArrayOne],
         *rightArray = new Registro[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
    {
        leftArray[i] = vec[left + i];
    }
    for (auto j = 0; j < subArrayTwo; j++)
    {
        rightArray[j] = vec[mid + 1 + j];
    }

    auto indexOfSubArrayOne = 0,
         indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            vec[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            vec[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }

    while (indexOfSubArrayOne < subArrayOne)
    {
        vec[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }

    while (indexOfSubArrayTwo < subArrayTwo)
    {
        vec[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

//Esta es la funcion merge sort que se manda a llamar dentro del codigo del main para el ordenamiento de los registros en el archivo de texto
void ordenaMerge(std::vector<Registro> &vec, int const begin, int const end)
{
    if (begin >= end)
    {
        return;
    }

    auto mid = begin + (end - begin) / 2;
    ordenaMerge(vec, begin, mid);
    ordenaMerge(vec, mid + 1, end);
    merge(vec, begin, mid, end);
}

//Este es el metodo de busqueda binaria que se utiliza para buscar un registro particular
//Este metodo regresa el indice exacto del registro en caso de que se encuentre.
//En caso de que no se encuentre, regresa el indice mas cercano que fue encontrado.
int busquedaBinaria(std::vector<Registro> vec, Registro findMe)
{
    int vecSize = vec.size();
    int comparisons = 0;
    int left = 0;
    int right = vecSize - 1;
    int medio;
    if (vec[0].getDay() == findMe.getDay() && vec[0].getMonth() == findMe.getMonth() && vec[0].getTime() == findMe.getTime())
    {
        return 0;
    }
    if (vec[vecSize - 1].getDay() == findMe.getDay() && vec[vecSize - 1].getMonth() == findMe.getMonth() && vec[vecSize - 1].getTime() == findMe.getTime())
    {
        return vecSize - 1;
    }
    while (vecSize > 1)
    {
        comparisons += 1;
        medio = (left + right) / 2;
        if (vec[medio].getDay() == findMe.getDay() && vec[medio].getMonth() == findMe.getMonth() && vec[medio].getTime() == findMe.getTime())
        {
            return medio;
        }
        else if (vec[medio] < findMe)
        {
            left = medio;
        }
        else
        {
            right = medio;
        }
        vecSize = right - left;
    }
    std::cout << "Los datos ingresados no fueron encontrados en la base de datos, en lugar del indice especifico, se regreso el indice mas cercano" << std::endl;
    return medio;
}

//++++++++++++++++++++++++++++++++++++++++Definicion de la clase++++++++++++++++++++++++++++++++++++++++

class Bitacora
{
public:
    Bitacora();
    Bitacora(std::string nombreTxt);
    void imprimeRango(int, int);
    void ordenaBitacora();
    void escribeBitacora();
    int buscaRegistro(Registro);

private:
    vector<Registro> listaDeRegistros;
    int size;
};
#endif

//En el constructor default el vector se deja vacio y el size es de 0
Bitacora::Bitacora()
{
    size = 0;
}

//Constructor para la clase bitacora utilizando el nombre de un archivo txt
Bitacora::Bitacora(std::string nombreTxt)
{
    std::ifstream lineCatcher(nombreTxt);
    std::string line, atrtibute;
    int counter = 0;

    //Este while se corre para cada linea dentro del archivo de texto
    while (std::getline(lineCatcher, line))
    {

        std::string mes, dia, hora, direccion, error;
        //Los siguientes datos tienen la misma logitud en todos los casos, por lo que se puede usar un substr de parametros constante
        mes = line.substr(0, 3);
        dia = line.substr(4, 2);
        hora = line.substr(7, 8);
        //Se usa .find para encontrar la posicion en la que termina la direccion IP
        size_t found = line.find(' ', 16);
        direccion = line.substr(16, found - 16);
        error = line.substr(found + 1);

        //Se crea un objeto de tipo Registro para la linea con toda la informacion y se agrega al vector de registros
        Registro nuevoRegistro(mes, stoi(dia), hora, direccion, error);
        listaDeRegistros.push_back(nuevoRegistro);
        counter++;
    }

    size = listaDeRegistros.size();
}

//En este metodo se utiliza el ordena merge para ordenar todos los registros de la bitacora
void Bitacora::ordenaBitacora()
{
    ordenaMerge(listaDeRegistros, 0, size - 1);
}

//Este metodo escribe la bitacora a un archivo txt
void Bitacora::escribeBitacora()
{
    //Al tener el vector de objetos ordenados, escribimos el archivo bitacora_ordenada.txt con los registros en orden
    ofstream myfile;
    myfile.open("bitacora_ordenada.txt");
    for (int i = 0; i < listaDeRegistros.size(); i++)
    {
        myfile << listaDeRegistros[i].txtFormat() << "\n";
    }
    myfile.close();
}

//Metodo para buscar el indice de un objeto Registro en la bitacora
int Bitacora::buscaRegistro(Registro aBuscar)
{
    return busquedaBinaria(listaDeRegistros, aBuscar);
}

void Bitacora::imprimeRango(int inicio, int fin)
{
    std::cout << std::endl
              << "------------------------------------------- Numero de registros: " << fin + 1 - inicio << " -------------------------------------------" << std::endl
              << std::endl;
    for (int i = inicio; i <= fin; i++)
    {
        std::cout << listaDeRegistros[i].txtFormat() << std::endl;
    }
}