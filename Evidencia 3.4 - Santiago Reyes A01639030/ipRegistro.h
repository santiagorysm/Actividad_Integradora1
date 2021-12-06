//Clase Registro - Santiago Reyes

//Esta clase de registro representa una sola linea del archivo de texto.
//Un registro tiene un mes, un dia, una hora, una direccion IP y un mensaje de error
//Se utiliza sobrecarga de operadores en esta clase para utilizarlos en el algoritmo de ordenamiento y busqueda

#ifndef IPREGISTRO_H
#define IPREGISTRO_H
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

//Declaracion de la clase
class IpRegistro
{
public:
    IpRegistro();
    IpRegistro(std::string ip, int cant);
    friend bool operator<(IpRegistro const &, IpRegistro const &);
    friend bool operator<=(IpRegistro const &, IpRegistro const &);
    void print();
    std::string txtFormat();

private:
    std::string ipAdress; //El Ip en si
    int cantidad;         //La cantidad de veces que aparece en el archivo
};

//Constructor default (En el main no se llama, pero se define de cualquier forma)
IpRegistro::IpRegistro()
{

    cantidad = 0;
    ipAdress = "";
}

//De esta manera se declara un registro de ip
IpRegistro::IpRegistro(std::string ip, int cant)
{
    ipAdress = ip;
    cantidad = cant;
}

//Metodo que imprime de manera mas clara un registro (No se utiliza en el main, pero lo pongo por practicidad y para pruebas de desarrollo)
void IpRegistro::print()
{
    std::cout << ipAdress << " : " << cantidad << std::endl;
}

//Sobre carga del operador < para su uso en el heaipify y en el seap sort
bool operator<(IpRegistro const &c1, IpRegistro const &c2)
{
    return (c1.cantidad < c2.cantidad);
}

//Sobre carga del operador <= para su uso en el heaipify y en el seap sort
bool operator<=(IpRegistro const &c1, IpRegistro const &c2)
{
    return (c1.cantidad <= c2.cantidad);
}

//Este metodo regresa el registro en el mismo formato que se encuentra en el archivo de texto proporcionado para la actividad
std::string IpRegistro::txtFormat()
{
    return (ipAdress + " : " + to_string(cantidad));
}
#endif