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
#include "doubleLinkedList.h"
#include "stack.h"

//++++++++++++++++++++++++++++++++++++++++Definicion de la clase++++++++++++++++++++++++++++++++++++++++
template <class T>
class Bitacora
{

public:
    Bitacora();
    Bitacora(std::string nombreTxt);
    void imprimeRango(int, int);
    void ordenaBitacora();
    void sortBitacora();
    void escribeBitacora();
    int buscaRegistro(Registro, Registro);
    void swap(Node<T> *a, Node<T> *b);
    Registro operator[](int);
    Node<T> *binarySearch(Node<T> *head, T value);
    Node<T> *middle(Node<T> *start, Node<T> *last);
    Node<T> *partition(Node<T> *l, Node<T> *h);
    void quickSortRecursive(Node<T> *l, Node<T> *h);
    void quickSortIterative(Node<T> *l, Node<T> *h);

private:
    DoubleLinkedList<Registro> listaDeRegistros;
    int size;
};
#endif

//En el constructor default el vector se deja vacio y el size es de 0
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
        listaDeRegistros.addLast(nuevoRegistro);
        counter++;
    }

    size = listaDeRegistros.getNumElements();
}

//En este metodo se utiliza el ordena merge para ordenar todos los registros de la bitacora
template <class T>
void Bitacora<T>::ordenaBitacora()
{
    //ordenaMerge(listaDeRegistros, 0, size - 1);
    Node<Registro> *ini = listaDeRegistros.getNodeHead();
    Node<Registro> *fini = listaDeRegistros.getNodeTail();

    //std::cout << "Ultimo registro: " << fini->data.txtFormat() << std::endl;
    //quickSortIterative(ini, fini);
    quickSortIterative(ini, fini);
}

//Este metodo escribe la bitacora a un archivo txt
template <class T>
void Bitacora<T>::escribeBitacora()
{
    //Al tener el vector de objetos ordenados, escribimos el archivo bitacora_ordenada.txt con los registros en orden
    ofstream myfile;
    myfile.open("bitacora_ordenada.txt");
    Node<Registro> *ini = listaDeRegistros.getNodeHead();
    while (ini != NULL)
    {
        myfile << ini->data.txtFormat() << "\n";
        ini = ini->next;
    }
    myfile.close();
}

//Metodo para buscar el indice de un objeto Registro en la bitacora
template <class T>
int Bitacora<T>::buscaRegistro(Registro aBuscar, Registro bBuscar)
{
    if (bBuscar < aBuscar)
    {
        throw std::runtime_error("Error: El segundo registro ingreso debe de encontrarse despues que el primero");
    }

    std::cout << "Los siguientes registros fueron escritos en el archivo resultad_busqueda.txt" << std::endl;
    ofstream myfile;
    myfile.open("resultado_busqueda.txt");

    Node<Registro> *ini = listaDeRegistros.getNodeHead();
    Node<Registro> *primero = binarySearch(ini, aBuscar);
    Node<Registro> *ultimo = binarySearch(ini, bBuscar);
    std::cout << primero->data.txtFormat() << std::endl;
    int numResultados = 0;
    while (primero->data.txtFormat() != ultimo->data.txtFormat())
    {
        numResultados++;
        std::cout << primero->data.txtFormat() << std::endl;
        myfile << primero->data.txtFormat() << "\n";
        primero = primero->next;
    }
    numResultados++;

    std::cout << primero->data.txtFormat() << std::endl;
    myfile << primero->data.txtFormat() << "\n";
    myfile.close();
    std::cout << "---------------------- Numero total de registros encontrados: " << std::to_string(numResultados) << " ----------------------" << std::endl;

    return 0;
}

template <class T>
void Bitacora<T>::imprimeRango(int inicio, int fin)
{
    std::cout << std::endl
              << "------------------------------------------- Numero de registros: " << fin + 1 - inicio << " -------------------------------------------" << std::endl
              << std::endl;
    for (int i = inicio; i <= fin; i++)
    {
        std::cout << listaDeRegistros.dataFromPosition(i).txtFormat() << std::endl;
    }
}

template <class T>
Registro Bitacora<T>::operator[](int index)
{
    return listaDeRegistros[index];
}

//++++++++++++++++++++++++++++++++++++++++Algoritmos de Ordenamiento y de Busqueda++++++++++++++++++++++++++++++++++++++++
using namespace std;

//Funcion que encuentra el nodo de en medio entre dos nodos apuntadores T
template <class T>
Node<T> *Bitacora<T>::middle(Node<T> *start, Node<T> *last)
{
    if (start == NULL)
        return NULL;

    Node<T> *slow = start;
    Node<T> *fast = start->next;

    while (fast != last)
    {
        fast = fast->next;
        if (fast != last)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

// Funcion de busqueda binaria para la lista doblemente ligada
template <class T>
Node<T> *Bitacora<T>::binarySearch(Node<T> *head, T value)
{
    Node<T> *start = head;
    Node<T> *last = NULL;
    Node<T> *mid = NULL;
    do
    {
        // Declaramos nodo apuntador T mid
        Node<T> *mid = middle(start, last);

        // Si el valor encontrado es nulo
        if (mid == NULL)
            return NULL;

        // Si el valor es el de en medio
        if (mid->data.getMonth() == value.getMonth() && mid->data.getDay() == value.getDay() && mid->data.getTime() == value.getTime()) //(mid->data.txtFormat() == value.txtFormat())
            return mid;

        // If value is more than mid
        else if (mid->data < value)
            start = mid->next;

        // If the value is less than mid.
        else
            last = mid;

    } while (last == NULL ||
             last->data.txtFormat() != start->data.txtFormat());

    // value not present
    return mid;
}

// Funcion que intercambia los valores de los dos nodos apuntadores T que se les pasa
template <class T>
void Bitacora<T>::swap(Node<T> *a, Node<T> *b)
{
    Registro temp = a->data;
    //std::cout << "Prev A: " << a->data.txtFormat();
    a->data = b->data;
    b->data = temp;
    //std::cout << "Post A: " << a->data.txtFormat() << std::endl;
}

//Funcion partition que regresa un nodo apuntador T; se utiliza en el quick sort iterativo y en el recursivo
template <class T>
Node<T> *Bitacora<T>::partition(Node<T> *l, Node<T> *h)
{
    // set pivot as h element
    Registro x = h->data;

    // similar to i = l-1 for array implementation
    Node<T> *i = l->prev;

    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (Node<T> *j = l; j != h; j = j->next)
    {

        if ((j->data) <= x)
        {
            // Similar to i++ for array
            i = (i == NULL) ? l : i->next;

            swap(i, j);
        }
    }
    i = (i == NULL) ? l : i->next; // Similar to i++
    swap(i, h);
    return i;
}

//Funcion recursiva para el quick sort
template <class T>
void Bitacora<T>::quickSortRecursive(Node<T> *l, Node<T> *h)
{
    if (h != NULL && l != h && l != h->next)
    {
        Node<T> *p = partition(l, h);
        quickSortRecursive(l, p->prev);
        quickSortRecursive(p->next, h);
    }
}

//Funcion iterativa para el quick sort utilizando stacks
template <class T>
void Bitacora<T>::quickSortIterative(Node<T> *l, Node<T> *h)
{

    Stack<Node<T> *> myStack;

    myStack.push(l);
    myStack.push(h);

    while (!myStack.isEmpty())
    {

        h = myStack.pop();
        l = myStack.pop();

        Node<T> *p = partition(l, h);

        if (l->data < p->data)
        {

            myStack.push(l);
            myStack.push(p->prev);
        }

        if (p->data < h->data)
        {
            myStack.push(p->next);
            myStack.push(h);
        }
    }

    myStack.printStack();
}