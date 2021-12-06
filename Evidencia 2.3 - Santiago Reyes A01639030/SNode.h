//Escrito por el Doctor Eduardo Arturo Rodriguez Tello

#ifndef _SNODE_H_
#define _SNODE_H_

#include <iostream>

template <class T>
class SNode
{
public:
    T data;
    SNode<T> *next;
    SNode();
    SNode(T);
};

template <class T>
SNode<T>::SNode()
{
    data = 0;
    next = NULL;
}
template <class T>
SNode<T>::SNode(T val)
{
    data = val;
    next = NULL;
}

#endif // _NODE_H_