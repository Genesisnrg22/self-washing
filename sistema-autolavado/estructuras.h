#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>

using namespace std;

struct Cliente {
    int id;
    string nombre;
    string telefono;
};

struct Vehiculo {
    string placa;
    string modelo;
    string color;
    int idDueno;
};

struct Lavador {
    int id;
    string nombre;
};

struct Servicio {
    string fecha;
    string placaVehiculo;
    int idLavador;
    float costo;
};

#endif