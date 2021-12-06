//Escrito por Santiago Reyes Moran - A01639030 y Lucas Wong Mang - A01639032
//04/12/2021

#ifndef __RESUMENIP_H_
#define __RESUMENIP_H_
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <unordered_map>
#include "registroIP.h"

//Esa clase guarda la informacion resumen de la IP
//Esta informacion incluye la direccion IP, la lista de direcciones que la IP acceso y la lista de direcciones IP que accesaron a esta IP
class ResumenIP
{
private:
    RegistroIp direccionIP;
    std::vector<RegistroIp> ipsQueAccesaron;
    std::vector<RegistroIp> ipsAccesadas;
    void heapSort(std::vector<RegistroIp> &data);
    void heapify(std::vector<RegistroIp> &data, int n, int i);

public:
    ResumenIP();
    ResumenIP(std::string, std::vector<std::string>, std::vector<std::string>);
    void printResumen();
    void ordenaIps();
    long long getNumericVal();
    std::string getDireccion();
};

ResumenIP::ResumenIP()
{
    RegistroIp nuevoRegistro("0.0.0.0");
    direccionIP = nuevoRegistro;
}

ResumenIP::ResumenIP(std::string dir, std::vector<std::string> IPQA, std::vector<std::string> IPA)
{
    RegistroIp registroNuevo(dir);
    direccionIP = registroNuevo;
    for (int i = 0; i < IPQA.size(); i++)
    {
        std::cout << "";
        RegistroIp nuevoRegistro(IPQA[i]);
        ipsQueAccesaron.push_back(nuevoRegistro);
    }

    for (int j = 0; j < IPA.size(); j++)
    {
        std::cout << "";
        RegistroIp nuevoRegistro(IPA[j]);
        ipsAccesadas.push_back(nuevoRegistro);
    }
}

//Metodo heapify que se utilzia en el heap sort
//Complejidad temporal O(log(n))
void ResumenIP::heapify(std::vector<RegistroIp> &data, int n, int i)
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

        heapify(data, n, largest);
    }
}

//Metodo heap sort que se utiliza para ordenar las IPs del vector
//Complejidad temporal O(nlog(n))
void ResumenIP::heapSort(std::vector<RegistroIp> &data)
{
    int n = data.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        std::swap(data[0], data[i]);

        heapify(data, i, 0);
    }
}

//Este metodo llama a heapsort para las ipsQueAccesaron e ipsAccesadas
void ResumenIP::ordenaIps()
{
    heapSort(ipsQueAccesaron);
    heapSort(ipsAccesadas);
    //Como el heapsort ordena las Ips de mayor a menor entonces las invierto para que sean de menor a mayor
    std::reverse(ipsQueAccesaron.begin(), ipsQueAccesaron.end());
    std::reverse(ipsAccesadas.begin(), ipsAccesadas.end());
}

void ResumenIP::printResumen()
{
    //Se llama ordenaIps (para que unicamente se ordenen los resumenes que se mandan a llamar y de esta forma sea menor la complejidad temporal)
    ordenaIps();
    std::cout << "------------------ Resumen para la IP " << direccionIP.txtFormat() << " ------------------" << std::endl;
    std::cout << "IPs que fueron accesadas por " << direccionIP.txtFormat() << ":" << std::endl
              << "{ " << std::endl;
    for (int j = 0; j < ipsAccesadas.size(); j++)
    {
        std::cout << ipsAccesadas[j].txtFormat() << std::endl;
    }
    std::cout << "}" << std::endl;
    std::cout << "IPs que accesaron a " << direccionIP.txtFormat() << ":" << std::endl
              << "{ " << std::endl;
    for (int k = 0; k < ipsQueAccesaron.size(); k++)
    {
        std::cout << ipsQueAccesaron[k].txtFormat() << std::endl;
    }
    std::cout << "}" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
}

//Esta funcion regresa el valor numerico de la direccion ip
long long ResumenIP::getNumericVal()
{
    return direccionIP.getNumericalVal();
}

//Esta funcion regresa el string de la direccion IP
std::string ResumenIP::getDireccion()
{
    return direccionIP.txtFormat();
}
#endif