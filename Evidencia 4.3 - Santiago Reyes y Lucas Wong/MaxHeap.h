//Clase extraida del Trabajo 3.2 de programacion
//Escrito por Lucas Wong Mang y Santiago Reyes Moran

#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class MaxHeap
{
private:
    // contiene los elementos del heap
    std::vector<T> data;
    // capacidad maxima del heap
    int maxSize;
    // tamaño actual del heap
    int size;

    int parent(int i);
    int left(int i);
    int right(int i);

public:
    MaxHeap(int capacity);
    ~MaxHeap();
    bool isEmpty();
    int getSize();
    int getCapacity();
    void printMaxHeap();
    void writeMaxHeap(std::string);
    void writeTop(std::string, int);

    void push(T key);
    void pop();
    void heapify(int, int);
    void heapifyPop(int);
    T top();
    void heapSort();

    int Partition(std::vector<T> &v, int start, int end);
    void Quicksort(std::vector<T> &v, int start, int end);
};

template <class T>
MaxHeap<T>::MaxHeap(int capacity)
{
    //std::cout << "--->Creando un MaxHeap: " << this << std::endl;
    size = 0;
    maxSize = capacity;
    data.resize(maxSize);
}

template <class T>
MaxHeap<T>::~MaxHeap()
{
    //std::cout << "--->Liberando memoria del MaxHeap: " << this << std::endl;
    data.clear();
}

template <class T>
bool MaxHeap<T>::isEmpty()
{
    return (size <= 0);
}

template <class T>
int MaxHeap<T>::getSize()
{
    return size;
}

template <class T>
int MaxHeap<T>::getCapacity()
{
    return maxSize;
}

template <class T>
void MaxHeap<T>::printMaxHeap()
{
    for (int i = 0; i < size; i++)
        std::cout << data[i].txtFormat() << std::endl;
}

template <class T>
void MaxHeap<T>::writeMaxHeap(std::string nombreArchivo)
{
    ofstream myfile;
    myfile.open(nombreArchivo);
    for (int i = 0; i < size; i++)
        myfile << data[i].txtFormat() << "\n";
    myfile.close();
}

template <class T>
void MaxHeap<T>::writeTop(std::string nombreArchivo, int top)
{
    ofstream myfile;
    myfile.open(nombreArchivo);
    for (int i = 0; i < top; i++)
        myfile << data[i].txtFormat() << "\n";
    myfile.close();
}

template <class T>
int MaxHeap<T>::parent(int i)
{
    return (i - 1) / 2;
}

template <class T>
int MaxHeap<T>::left(int i)
{
    return (2 * i + 1);
}

template <class T>
int MaxHeap<T>::right(int i)
{
    return (2 * i + 2);
}

template <class T>
void MaxHeap<T>::push(T key)
{
    if (size == maxSize)
    {
        std::cout << "Overflow: no se puede insertar la llave " << std::endl;
        return;
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)] < data[i])
    {
        std::swap(data[i], data[parent(i)]);
        i = parent(i);
    }
}

template <class T>
T MaxHeap<T>::top()
{

    return data[0];
}

//Heapify que se utiliza para el pop de un elemento
template <class T>
void MaxHeap<T>::heapifyPop(int i)
{
    //Sacamos left y right
    int l = left(i);
    int r = right(i);

    //Inicializamos largest como el valor ingresado
    int largest = i;

    //Encontramos el valor mayor entre right y left
    if (l < getSize() && data[i] < data[l])
    {
        largest = l;
    }

    if (r < getSize() && data[largest] < data[r])
    {
        largest = r;
    }

    //Hace el swap con el hijo que tenga el valor mayor
    if (largest != i)
    {
        //Se hace el swap
        std::swap(data[i], data[largest]);
        //Se vuelve a llamar heapify (es recursivo) hasta que largest=i
        heapifyPop(largest);
    }
}

//Metodo de pop
template <class T>
void MaxHeap<T>::pop()
{
    try
    {
        //Si no hay elementos en el heap, lanza una excepcion
        if (isEmpty())
        {
            throw std::out_of_range("No hay suficientes elementos para hacer un pop");
        }

        //Movemos el ultimo elemento del heap hacia el root y borramos el ultimo elemento
        data[0] = data.back();
        data.pop_back();
        //data.erase(data.begin());

        //Inicializamos el metodo de heapify desde el root
        heapifyPop(0);
        size--;
    }
    //Se hace catch de la excepcion(en caso de quererle hacer pop a un heap vacio)
    catch (const std::out_of_range &oor)
    {
        std::cout << std::endl
                  << oor.what();
    }
}

//Metodo heapify que se utiliza para el heap sort
template <class T>
void MaxHeap<T>::heapify(int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && data[l] < data[largest])
        largest = l;

    if (r < n && data[r] < data[largest])
        largest = r;

    if (largest != i)
    {
        std::swap(data[i], data[largest]);

        heapify(n, largest);
    }
}

//Metodo heap sort
template <class T>
void MaxHeap<T>::heapSort()
{
    int n = size;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);

    for (int i = n - 1; i > 0; i--)
    {
        std::swap(data[0], data[i]);

        heapify(i, 0);
    }
}

#endif // __MAXHEAP_H_