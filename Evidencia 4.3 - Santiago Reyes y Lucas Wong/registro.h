//Clase Registro - Santiago Reyes

//Esta clase de registro representa una sola linea del archivo de texto.
//Un registro tiene un mes, un dia, una hora, una direccion IP y un mensaje de error
//Se utiliza sobrecarga de operadores en esta clase para utilizarlos en el algoritmo de ordenamiento y busqueda

#ifndef REGISTRO_H
#define REGISTRO_H
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstring>

using namespace std;

//Se usa esta estructura para guardar los valores numericos del tiempo
struct hmsTime
{
    int hours;
    int minutes;
    int seconds;
};

//Declaracion de la clase
class Registro
{
public:
    Registro();
    Registro(std::string mon, int dat, std::string tim, std::string ip, std::string err);
    friend bool operator<(Registro const &, Registro const &);
    friend bool operator<=(Registro const &, Registro const &);
    void print();
    std::string txtFormat();
    int getDay();
    std::string getTime();
    std::string getMonth();
    void printIP();
    int getIp1();
    int getIp2();
    int getIp3();
    int getIp4();

private:
    std::string monthName, ipAdress, errorTicket, timeString;
    int date, monthNum;
    int ip1, ip2, ip3, ip4;
    hmsTime time;
};

//Constructor default (En el main no se llama, pero se define de cualquier forma)
Registro::Registro()
{
    monthName = ipAdress = errorTicket = timeString = "";
    date = monthNum = ip1 = ip2 = ip3 = ip4 = 0;
    time.hours = 0;
    time.minutes = 0;
    time.seconds = 0;
}

//De esta manera se declara un registro
Registro::Registro(std::string mon, int dat, std::string tim, std::string ip, std::string err)
{
    //Dividimos el string de tiempo en hora minutos y segundos como numeros enteros
    timeString = tim;
    int h = stoi(tim.substr(0, 2));
    int m = stoi(tim.substr(3, 2));
    int s = stoi(tim.substr(6, 2));

    monthName = mon;

    //Usamos un diccionario (hashmash) para encontrar el valor numerico del mes que se ingresa como parametro
    unordered_map<string, int> meses({{"Ene", 1}, {"Feb", 2}, {"Mar", 3}, {"Abr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dic", 12}});
    monthNum = meses[monthName];

    //Declaramos el struct de la hora e igualamos los otros parametros
    date = dat;
    time.hours = h;
    time.minutes = m;
    time.seconds = s;
    ipAdress = ip;
    errorTicket = err;
    char charArr[25];
    strcpy(charArr, ipAdress.c_str());
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

void Registro::printIP()
{

    std::cout << ip1 << " " << ip2 << " " << ip3 << " " << ip4 << std::endl;
}
//Metodo que regresa el numero de dia
int Registro::getDay()
{
    return date;
}

//Metodo que regresa el nombre del mes
std::string Registro::getMonth()
{
    return monthName;
}

//Metodo que regresa el string de tiempo
std::string Registro::getTime()
{
    return timeString;
}

//Metodo que imprime de manera mas clara un registro (No se utiliza en el main, pero lo pongo por practicidad y para pruebas de desarrollo)
void Registro::print()
{
    std::cout << monthName << "-" << date << " at " << timeString << " from " << ipAdress << std::endl;
    std::cout << errorTicket << std::endl;
}

//Sobre carga del operador < para su uso en el heaipify y en el seap sort
bool operator<(Registro const &c1, Registro const &c2)
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

//Sobre carga del operador <= para su uso en el heaipify y en el seap sort
bool operator<=(Registro const &c1, Registro const &c2)
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

//Este metodo regresa el registro en el mismo formato que se encuentra en el archivo de texto proporcionado para la actividad
std::string Registro::txtFormat()
{
    std::string strDate;
    if (date < 10)
    {
        strDate = "0" + to_string(date);
    }
    else
    {
        strDate = to_string(date);
    }
    return (monthName + " " + strDate + " " + timeString + " " + ipAdress + " " + errorTicket);
}
#endif