//Escrito por Santiago Reyes Moran A01639030 con base al codigo propocionado por el Doctor Eduardo Arturo Rodriguez Tello
//13/10/2021

#ifndef _DOUBLELINKEDLIST_H_
#define _DOUBLELINKEDLIST_H_
#include <climits>
#include "Node.h"
#include <vector>
#include <algorithm>

template <class T>
class DoubleLinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;
    int numElements;

public:
    DoubleLinkedList();
    ~DoubleLinkedList();
    int getNumElements();
    void printList();
    void printListRegistro();

    void addFirst(T value);
    void addLast(T value);
    bool deleteData(T value);
    bool deleteAt(int position);
    T dataFromPosition(int position);
    void changeData(int position, T value);
    void clear();
    void duplicate();
    void removeDuplicates();
    void sortedList();
    Node<T> *getNodeHead();
    Node<T> *getNodeTail();

    //Stack<T> getReversedSublist(int ini, int fini);
    //void swap(Node<T> &A, Node<T> &B);
    T &operator[](int);
    Node<T> getHead();

    void updateAt(int position, T value);
};

template <class T>
DoubleLinkedList<T>::DoubleLinkedList()
{
    //std::cout << "--->Creando una lista vacia " << this << std::endl;
    head = NULL;
    tail = NULL;
    numElements = 0;
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    //std::cout << "--->Liberando memoria de la lista " << this << std::endl;
    Node<T> *p, *q;
    p = head;
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
    head = NULL;
    tail = NULL;
    numElements = 0;
}

//
template <class T>
int DoubleLinkedList<T>::getNumElements()
{
    return numElements;
}

template <class T>
void DoubleLinkedList<T>::printList()
{
    Node<T> *ptr = head;
    while (ptr != NULL)
    {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

template <class T>
void DoubleLinkedList<T>::printListRegistro()
{
    Node<T> *ptr = head;
    while (ptr != NULL)
    {
        std::cout << ptr->data.txtFormat() << std::endl;
        ptr = ptr->next;
    }
}

template <class T>
Node<T> DoubleLinkedList<T>::getHead()
{
    return head;
}

template <class T>
void DoubleLinkedList<T>::addFirst(T value)
{
    Node<T> *newNode = new Node<T>(value);
    // Si la lista esta vacia
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    numElements++;
}

template <class T>
void DoubleLinkedList<T>::addLast(T value)
{
    // La lista esta vacia
    if (head == NULL)
    {
        addFirst(value);
    }
    else
    {
        Node<T> *newNode = new Node<T>(value);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        numElements++;
    }
}

template <class T>
//O(n)
bool DoubleLinkedList<T>::deleteData(T value)
{
    Node<T> *p, *q;
    p = head;
    q = NULL;
    // Si la lista esta vacia
    if (p == NULL)
    {
        return false;
    }
    else
    {
        // buscar value en la lista
        while (p != NULL && p->data != value)
        {
            q = p;
            p = p->next;
        }
        // Si no existe value en la lista
        if (p == NULL)
            return false;
        // Si debe borrarse el primer elemento
        if (p->prev == NULL)
        {
            head = p->next;
            if (head != NULL)
                head->prev = NULL;
        }
        else if (p->next == NULL)
        {
            // Si debe borrarse el último elemento
            q->next = NULL;
            tail = q;
        }
        else
        {
            // Cualquier otro elemento entre la lista
            q->next = p->next;
            p->next->prev = q;
        }
        delete p;
        numElements--;
        return true;
    }
}

template <class T>
bool DoubleLinkedList<T>::deleteAt(int position)
{
    if (position < 0 || position >= numElements)
    {
        std::cout << "Indice fuera de rango" << std::endl;
        return false;
    }
    else if (position == 0)
    { // Si debe borrarse el primer elemento
        Node<T> *p = head;
        // Si la lista contiene solo un nodo
        if (head != NULL && head->next == NULL)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = p->next;
            head->prev = NULL;
        }
        delete p;
        numElements--;
        return true;
    }
    else
    {
        Node<T> *p = head, *q = NULL;
        int index = 0;
        while (index != position)
        {
            q = p;
            p = p->next;
            index++;
        }
        // Si debe borrarse el último elemento
        if (p->next == NULL)
        {
            q->next = NULL;
            tail = q;
        }
        else
        { // Cualquier otro elemento entre la lista
            q->next = p->next;
            p->next->prev = q;
        }
        delete p;
        numElements--;
        return true;
    }
}

//La funcion recorre toda la lista y borra cada nodo en ella
//Complejidad O(n)
template <class T>
void DoubleLinkedList<T>::clear()
{
    for (int i = 0; i < numElements; i++)
    {
        Node<T> *p = head;
        T value = head->data;
        head = p->next;
        delete p;
        numElements--;
    }
}
//Al tener un for su complejidad algoritmica es de O(log(n))
//Se duplican los miembros originales de la lista
template <class T>
void DoubleLinkedList<T>::duplicate()
{
    int s = numElements;
    Node<T> *p = head;
    for (int i = 0; i < s; i++)
    {
        Node<T> *newNode = new Node<T>(p->data);
        newNode->next = p->next;
        p->next = newNode;
        newNode->prev = p;
        p = newNode->next;
        numElements++;
    }
}

template <class T>
void DoubleLinkedList<T>::changeData(int position, T value)
{
    if (position < 0 || position >= numElements)
    {
        std::cout << "Indice fuera de rango" << std::endl;
    }
    else
    {
        if (position == 0)
            head->data;
        Node<T> *p = head;
        int index = 0;
        while (p != NULL)
        {
            if (index == position)
                p->data = value;
            index++;
            p = p->next;
        }
    }
}

//Funcion removeDuplicates quita todos los numeros duplicados de la lista
//Complejidad O(n) con peor caso O(n^2) si todos los elementos son duplicados
template <class T>
void DoubleLinkedList<T>::removeDuplicates()
{
    std::vector<T> presentVals;
    Node<T> *p = head;
    Node<T> *q = NULL;
    while (p != NULL)
    {
        if (std::count(presentVals.begin(), presentVals.end(), p->data))
        {
            deleteData(p->data);
            numElements--;
        }
        else
        {
            presentVals.push_back(p->data);
        }
        q = p;
        p = p->next;
    }
    std::cout << std::endl;
}

//Funcion para obtener un nodo apuntador al tail de la DLL
template <class T>
T DoubleLinkedList<T>::dataFromPosition(int pos)
{
    if (pos < 0 || pos >= numElements)
    {
        std::cout << "Indice invalido, se encuentra fuera del rango " << pos << std::endl;
        Registro nuevo;
        return nuevo;
    }
    else
    {
        if (pos == 0)
            return head->data;
        Node<T> *p = head;
        int ind = 0;
        while (p != NULL)
        {
            if (ind == pos)
                return p->data;
            ind++;
            p = p->next;
        }
        Registro nuevo;
        return nuevo;
    }
}

//Sobre carga del operador [], que en realidad no se utiliza, pero fue bueno tener para realizar pruebas y comprobar resultados
template <class T>
T &DoubleLinkedList<T>::operator[](int index)
{
    int llSize = getNumElements();

    if (index < 0)
    {
        index = llSize + index;
    }

    if (index >= llSize)
    {
        std::cout << "DLL index out of bound, exiting";
        exit(0);
    }
    Node<T> *ptr = head;
    for (int i = 0; i < index; i++)
    {
        ptr = ptr->next;
    }
    return ptr->data;
}

//Funcion para obtener un nodo apuntador al head de la DLL
template <class T>
Node<T> *DoubleLinkedList<T>::getNodeHead()
{
    Node<T> *ptr = head;
    return ptr;
}

//Funcion para obtener un nodo apuntador al tail de la DLL
template <class T>
Node<T> *DoubleLinkedList<T>::getNodeTail()
{
    Node<T> *ptr = tail;
    return ptr;
}

#endif // _DOUBLELINKEDLIST_H_