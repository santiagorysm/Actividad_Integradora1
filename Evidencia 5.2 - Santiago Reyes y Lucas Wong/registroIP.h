//Escrito por Santiago Reyes Moran - A01639030 y Lucas Wong Mang - A01639032
//04/12/2021

#ifndef __REGISTROIP_H__
#define __REGISTROIP_H__
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <ostream>
#include <fstream>
#include <cstring>

class RegistroIp
{
public:
    RegistroIp();
    RegistroIp(std::string);
    friend bool operator<(RegistroIp const &, RegistroIp const &);
    friend bool operator<=(RegistroIp const &, RegistroIp const &);
    std::string txtFormat();
    long long getNumericalVal();

private:
    std::string direccion;
    int ip1, ip2, ip3, ip4;
};
#endif

RegistroIp::RegistroIp()
{
    direccion = "0.0.0.0";
    ip1 = ip2 = ip3 = ip4 = 0;
}

//Se crea el registro de la ip (incluyendo separar la IP en sus secciones numericas)
RegistroIp::RegistroIp(std::string ipInput)
{
    direccion = ipInput;
    char charArr[25];
    strcpy(charArr, direccion.c_str());
    char *ipPointer;
    ipPointer = strtok(charArr, ".");
    ip1 = atoi(ipPointer);
    ipPointer = strtok(NULL, ".");
    ip2 = atoi(ipPointer);
    ipPointer = strtok(NULL, ".");
    ip3 = atoi(ipPointer);
    ipPointer = strtok(NULL, ":");
    ip4 = atoi(ipPointer);
}

//Sobre carga del operador < para su uso en el heaipify y en el heap sort
bool operator<(RegistroIp const &c1, RegistroIp const &c2)
{
    if (c1.ip1 < c2.ip1)
    {
        return true;
    }
    else if (c1.ip1 > c2.ip1)
    {
        return false;
    }
    else
    {
        if (c1.ip2 < c2.ip2)
        {
            return true;
        }
        else if (c1.ip2 > c2.ip2)
        {
            return false;
        }
        else
        {
            if (c1.ip3 < c2.ip3)
            {
                return true;
            }
            else if (c1.ip3 > c2.ip3)
            {
                return false;
            }
            else
            {
                if (c1.ip4 < c2.ip4)
                {
                    return true;
                }
                else if (c1.ip4 > c2.ip4)
                {
                    return false;
                }
                else
                {
                    //Esto corre si los IP son identicos
                    return false;
                }
            }
        }
    }
}

//Sobre carga del operador <= para su uso en el heaipify y en el heap sort
bool operator<=(RegistroIp const &c1, RegistroIp const &c2)
{
    if (c1.ip1 < c2.ip1)
    {
        return true;
    }
    else if (c1.ip1 > c2.ip1)
    {
        return false;
    }
    else
    {
        if (c1.ip2 < c2.ip2)
        {
            return true;
        }
        else if (c1.ip2 > c2.ip2)
        {
            return false;
        }
        else
        {
            if (c1.ip3 < c2.ip3)
            {
                return true;
            }
            else if (c1.ip3 > c2.ip3)
            {
                return false;
            }
            else
            {
                if (c1.ip4 < c2.ip4)
                {
                    return true;
                }
                else if (c1.ip4 > c2.ip4)
                {
                    return false;
                }
                else
                {
                    //Esto corre si los IP son identicos
                    return true;
                }
            }
        }
    }
}

//Regresa el string de la direccion IP
std::string RegistroIp::txtFormat()
{
    return direccion;
}

//Regresa el valor numerico de la IP
long long RegistroIp::getNumericalVal()
{
    long long resultado = (ip1 * pow(256, 3)) + (ip2 * pow(256, 2)) + (ip3 * 256) + ip4;
    return resultado;
}