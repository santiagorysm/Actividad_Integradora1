//Clase registroGrafo - Santiago Reyes y Lucas Wong

//Esta clase de registro representa una instancia del grafo, utilizando su IP de Origen y el grado de su lista de adyacencia
//Un registroGrafo tiene una IP y un Grado
//Se utiliza sobrecarga de operadores en esta clase para utilizarlos en el Max Heap

#ifndef REGISTROGRAFO_H
#define REGISTROGRAFO_H
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstring>

using namespace std;


//Declaracion de la clase
class RegistroGrafo
{
public:
    RegistroGrafo();
    RegistroGrafo(std::string ip, int inst);
    friend bool operator<(RegistroGrafo const &, RegistroGrafo const &);
    friend bool operator<=(RegistroGrafo const &, RegistroGrafo const &);
    void print();
    std::string txtFormat();
    void printIP();

private:
    std::string direccionIp;
    int instancias;
    
};

//Constructor default (En el main no se llama, pero se define de cualquier forma)
RegistroGrafo::RegistroGrafo()
{
    direccionIp="";
    instancias=0;
}

//De esta manera se declara un registro
RegistroGrafo::RegistroGrafo(std::string ip, int inst)
{
    direccionIp=ip;
    instancias=inst;
}

void RegistroGrafo::printIP()
{

    std::cout << direccionIp<<std::endl;
}

void RegistroGrafo::print()
{
    std::cout<<"{IP: "<<direccionIp<<" ,Grado: "<<instancias<<" }"<<std::endl;
}

//Sobre carga del operador < para su uso en el heaipify y en el seap sort
bool operator<(RegistroGrafo const &c1, RegistroGrafo const &c2)
{
    if (c1.instancias < c2.instancias)
    {
        return true;
    }
    return false;

}

//Sobre carga del operador <= para su uso en el heaipify y en el seap sort
bool operator<=(RegistroGrafo const &c1, RegistroGrafo const &c2)
{
    if (c1.instancias <= c2.instancias)
    {
        return true;
    }
    return false;
}

//Este metodo regresa el en formato para escribirlo en los archivos .txt
std::string RegistroGrafo::txtFormat()
{
    return ("{ IP: "+direccionIp+" ,Grado: "+to_string(instancias)+" }");
}
#endif