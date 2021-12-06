//Escrito por el Doctor Eduardo Arturo Rodriguez Tello

#ifndef _STACK__H__
#define _STACK__H__

#include <climits>
#include "SNode.h"

template <class T>
class Stack
{
private:
    SNode<T> *top;
    int numElements;

public:
    Stack();
    ~Stack();
    int getNumElements();
    void printStack();

    void push(T value);
    T pop();
    T getTop();
    bool isEmpty();
};

template <class T>
Stack<T>::Stack()
{
    //std::cout << "--->Creando un Stack vacio: " << this << std::endl;
    top = NULL;
    numElements = 0;
}

template <class T>
Stack<T>::~Stack()
{
    //std::cout << "--->Liberando memoria del stack: " << this << std::endl;
    SNode<T> *p, *q;
    p = top;
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
    top = NULL;
    numElements = 0;
}

template <class T>
int Stack<T>::getNumElements()
{
    return numElements;
}
template <class T>
void Stack<T>::printStack()
{
    SNode<T> *ptr = top;
    while (ptr != NULL)
    {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

template <class T>
void Stack<T>::push(T value)
{
    SNode<T> *newNode = new SNode<T>(value);
    newNode->next = top;
    top = newNode;
    numElements++;
}

template <class T>
T Stack<T>::pop()
{
    T value = NULL;
    if (top != NULL)
    {
        SNode<T> *p = top;
        value = (top->data);
        top = p->next;
        delete p;
        numElements--;
    }
    return value;
}

template <class T>
T Stack<T>::getTop()
{
    T value = NULL;
    if (top != NULL)
    {
        value = (top->data);
    }
    return value;
}

template <class T>
bool Stack<T>::isEmpty()
{
    bool result = false;
    if (top == NULL)
        result = true;
    return result;
}
#endif // _STACK__H__