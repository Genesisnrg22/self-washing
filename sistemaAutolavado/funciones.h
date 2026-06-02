#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <vector>
#include <fstream>
#include "estructuras.h"

using namespace std;

// --- CONSTANTES DE COLOR ANSI ---
const string RESET = "\033[0m";
const string ROJO = "\033[31m";
const string VERDE = "\033[32m";
const string AMARILLO = "\033[33m";
const string AZUL = "\033[34m";
const string CYAN = "\033[36m";

// --- FUNCIÓN PARA LIMPIAR PANTALLA ---
void limpiarPantalla()
{
    // Código ANSI para limpiar la pantalla y reiniciar el cursor
    cout << "\033[2J\033[1;1H";
}

// --- FUNCIÓN PARA PAUSAR ---
void esperarEnter()
{
    cout << "\nPresione " << AMARILLO << "[ENTER]" << RESET << " para continuar...";
    cin.get(); // Espera a que el usuario presione Enter
}

// --- VALIDACIONES ---
bool existeCliente(const vector<Cliente> &listaClientes, int idBuscar)
{
    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].id == idBuscar)
            return true;
    }
    return false;
}

bool existeVehiculo(const vector<Vehiculo> &listaVehiculos, string placaBuscar)
{
    for (size_t i = 0; i < listaVehiculos.size(); i++)
    {
        if (listaVehiculos[i].placa == placaBuscar)
            return true;
    }
    return false;
}

bool existeLavador(const vector<Lavador> &listaLavadores, int idBuscar)
{
    for (size_t i = 0; i < listaLavadores.size(); i++)
    {
        if (listaLavadores[i].id == idBuscar)
            return true;
    }
    return false;
}

// --- CLIENTES ---
void agregarCliente(vector<Cliente> &listaClientes)
{
    limpiarPantalla();
    int idBuscar;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "       REGISTRAR NUEVO CLIENTE          " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Ingrese la cedula del cliente: ";
    cin >> idBuscar;
    cin.ignore();

    if (existeCliente(listaClientes, idBuscar))
    {
        cout << ROJO << "\n¡ERROR: Ya existe un cliente con la cedula " << idBuscar << "!" << RESET << endl;
        esperarEnter();
        return;
    }
    Cliente nuevoCliente;
    nuevoCliente.id = idBuscar;
    cout << "Ingrese el Nombre Completo: ";
    getline(cin, nuevoCliente.nombre);
    cout << "Ingrese el Telefono: ";
    getline(cin, nuevoCliente.telefono);
    listaClientes.push_back(nuevoCliente);

    cout << VERDE << "\n¡Cliente registrado con exito!" << RESET << endl;
    esperarEnter();
}

void listarClientes(const vector<Cliente> &listaClientes)
{
    if (listaClientes.empty())
    {
        cout << "\nNo hay clientes registrados." << endl;
        return;
    }
    cout << "\n--- Lista de Clientes ---" << endl;
    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        cout << "CI: " << listaClientes[i].id << " | Nombre: " << listaClientes[i].nombre << " | Tel: " << listaClientes[i].telefono << endl;
    }
}

void guardarClientesEnArchivo(const vector<Cliente> &listaClientes)
{
    ofstream archivo("clientes.txt");
    if (archivo.is_open())
    {
        for (size_t i = 0; i < listaClientes.size(); i++)
        {
            archivo << listaClientes[i].id << "|" << listaClientes[i].nombre << "|" << listaClientes[i].telefono << "\n";
        }
        archivo.close();
    }
}

void cargarClientesDesdeArchivo(vector<Cliente> &listaClientes)
{
    ifstream archivo("clientes.txt");
    if (!archivo.is_open())
        return;
    Cliente c;
    string idStr;
    while (getline(archivo, idStr, '|'))
    {
        c.id = stoi(idStr);
        getline(archivo, c.nombre, '|');
        getline(archivo, c.telefono, '\n');
        listaClientes.push_back(c);
    }
    archivo.close();
}

// --- VEHÍCULOS ---
void agregarVehiculo(vector<Vehiculo> &listaVehiculos, const vector<Cliente> &listaClientes)
{
    string placaBuscar;
    cout << "\n--- Registrar Nuevo Vehiculo ---" << endl;
    cout << "Ingrese la Placa: ";
    getline(cin, placaBuscar);

    if (existeVehiculo(listaVehiculos, placaBuscar))
    {
        cout << "¡ERROR: La placa " << placaBuscar << " ya existe!" << endl;
        return;
    }
    int cedulaDuenoBuscar;
    cout << "Ingrese la cedula del Dueno: ";
    cin >> cedulaDuenoBuscar;
    cin.ignore();
    if (!existeCliente(listaClientes, cedulaDuenoBuscar))
    {
        cout << "¡ERROR: El cliente no existe!" << endl;
        return;
    }
    Vehiculo nuevoCarro;
    nuevoCarro.placa = placaBuscar;
    nuevoCarro.idDueno = cedulaDuenoBuscar;
    cout << "Ingrese el Modelo: ";
    getline(cin, nuevoCarro.modelo);
    cout << "Ingrese el Color: ";
    getline(cin, nuevoCarro.color);
    listaVehiculos.push_back(nuevoCarro);
    cout << "¡Vehiculo registrado!" << endl;
}

void listarVehiculos(const vector<Vehiculo> &listaVehiculos)
{
    if (listaVehiculos.empty())
    {
        cout << "\nNo hay vehiculos registrados." << endl;
        return;
    }
    cout << "\n--- Lista de Vehiculos ---" << endl;
    for (size_t i = 0; i < listaVehiculos.size(); i++)
    {
        cout << "Placa: " << listaVehiculos[i].placa << " | Modelo: " << listaVehiculos[i].modelo << " | Color: " << listaVehiculos[i].color << " | CI Dueno: " << listaVehiculos[i].idDueno << endl;
    }
}

void guardarVehiculosEnArchivo(const vector<Vehiculo> &listaVehiculos)
{
    ofstream archivo("vehiculos.txt");
    if (archivo.is_open())
    {
        for (size_t i = 0; i < listaVehiculos.size(); i++)
        {
            archivo << listaVehiculos[i].placa << "|" << listaVehiculos[i].modelo << "|" << listaVehiculos[i].color << "|" << listaVehiculos[i].idDueno << "\n";
        }
        archivo.close();
    }
}

void cargarVehiculosDesdeArchivo(vector<Vehiculo> &listaVehiculos)
{
    ifstream archivo("vehiculos.txt");
    if (!archivo.is_open())
        return;
    Vehiculo v;
    string idDuenoStr;
    while (getline(archivo, v.placa, '|'))
    {
        getline(archivo, v.modelo, '|');
        getline(archivo, v.color, '|');
        getline(archivo, idDuenoStr, '\n');
        v.idDueno = stoi(idDuenoStr);
        listaVehiculos.push_back(v);
    }
    archivo.close();
}

// --- LAVADORES ---
void agregarLavador(vector<Lavador> &listaLavadores)
{
    int idBuscar;
    cout << "\n--- Registrar Nuevo Lavador ---" << endl;
    cout << "Ingrese el ID del Lavador: ";
    cin >> idBuscar;
    cin.ignore();
    if (existeLavador(listaLavadores, idBuscar))
    {
        cout << "¡ERROR: El lavador ya existe!" << endl;
        return;
    }
    Lavador nuevoLavador;
    nuevoLavador.id = idBuscar;
    cout << "Ingrese el Nombre: ";
    getline(cin, nuevoLavador.nombre);
    listaLavadores.push_back(nuevoLavador);
    cout << "¡Lavador registrado!" << endl;
}

void listarLavadores(const vector<Lavador> &listaLavadores)
{
    if (listaLavadores.empty())
    {
        cout << "\nNo hay lavadores registrados." << endl;
        return;
    }
    cout << "\n--- Lista de Lavadores ---" << endl;
    for (size_t i = 0; i < listaLavadores.size(); i++)
    {
        cout << "ID: " << listaLavadores[i].id << " | Nombre: " << listaLavadores[i].nombre << endl;
    }
}

void guardarLavadoresEnArchivo(const vector<Lavador> &listaLavadores)
{
    ofstream archivo("lavadores.txt");
    if (archivo.is_open())
    {
        for (size_t i = 0; i < listaLavadores.size(); i++)
        {
            archivo << listaLavadores[i].id << "|" << listaLavadores[i].nombre << "\n";
        }
        archivo.close();
    }
}

void cargarLavadoresDesdeArchivo(vector<Lavador> &listaLavadores)
{
    ifstream archivo("lavadores.txt");
    if (!archivo.is_open())
        return;
    Lavador l;
    string idStr;
    while (getline(archivo, idStr, '|'))
    {
        l.id = stoi(idStr);
        getline(archivo, l.nombre, '\n');
        listaLavadores.push_back(l);
    }
    archivo.close();
}

// --- SERVICIOS ---
void registrarServicio(vector<Servicio> &listaServicios, const vector<Vehiculo> &listaVehiculos, const vector<Lavador> &listaLavadores)
{
    Servicio nuevoServicio;
    cout << "\n--- Registrar Nuevo Servicio ---" << endl;
    cout << "Ingrese la Placa del Vehiculo: ";
    getline(cin, nuevoServicio.placaVehiculo);
    if (!existeVehiculo(listaVehiculos, nuevoServicio.placaVehiculo))
    {
        cout << "¡ERROR: El vehiculo no existe!" << endl;
        return;
    }
    cout << "Ingrese el ID del Lavador: ";
    cin >> nuevoServicio.idLavador;
    cin.ignore();
    if (!existeLavador(listaLavadores, nuevoServicio.idLavador))
    {
        cout << "¡ERROR: El lavador no existe!" << endl;
        return;
    }
    cout << "Ingrese la Fecha (DD/MM/AAAA): ";
    getline(cin, nuevoServicio.fecha);
    cout << "Ingrese el Costo: ";
    cin >> nuevoServicio.costo;
    cin.ignore();

    listaServicios.push_back(nuevoServicio);
    cout << "¡Servicio registrado con exito!" << endl;
}

void listarServicios(const vector<Servicio> &listaServicios)
{
    if (listaServicios.empty())
    {
        cout << "\nNo hay lavados en el historial." << endl;
        return;
    }
    cout << "\n--- Historial de Servicios ---" << endl;
    for (size_t i = 0; i < listaServicios.size(); i++)
    {
        cout << "Fecha: " << listaServicios[i].fecha << " | Carro: " << listaServicios[i].placaVehiculo << " | Lavador: " << listaServicios[i].idLavador << " | Costo: $" << listaServicios[i].costo << endl;
    }
}

void guardarServiciosEnArchivo(const vector<Servicio> &listaServicios)
{
    ofstream archivo("servicios.txt");
    if (archivo.is_open())
    {
        for (size_t i = 0; i < listaServicios.size(); i++)
        {
            archivo << listaServicios[i].fecha << "|" << listaServicios[i].placaVehiculo << "|" << listaServicios[i].idLavador << "|" << listaServicios[i].costo << "\n";
        }
        archivo.close();
    }
}

void cargarServiciosDesdeArchivo(vector<Servicio> &listaServicios)
{
    ifstream archivo("servicios.txt");
    if (!archivo.is_open())
        return;
    Servicio s;
    string idLavadorStr, costoStr;
    while (getline(archivo, s.fecha, '|'))
    {
        getline(archivo, s.placaVehiculo, '|');
        getline(archivo, idLavadorStr, '|');
        getline(archivo, costoStr, '\n');
        s.idLavador = stoi(idLavadorStr);
        s.costo = stof(costoStr);
        listaServicios.push_back(s);
    }
    archivo.close();
}

// --- FUNCIONES DE ELIMINACIÓN (CRUD - DELETE) ---

// 1. Eliminar Cliente por ID
void eliminarCliente(vector<Cliente> &listaClientes)
{
    int idBuscar;
    cout << "\n--- Eliminar Cliente ---" << endl;
    cout << "Ingrese la cedula del cliente que desea eliminar: ";
    cin >> idBuscar;
    cin.ignore();


    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].id == idBuscar)
        {
           
            listaClientes.erase(listaClientes.begin() + i);
            cout << "¡Cliente con cedula " << idBuscar << " eliminado exitosamente de la memoria!" << endl;
            return; 
        }
    }
    cout << "¡ERROR: No se encontro ningun cliente con la cedula " << idBuscar << "!" << endl;
}

// 2. Eliminar Vehículo por Placa
void eliminarVehiculo(vector<Vehiculo> &listaVehiculos)
{
    string placaBuscar;
    cout << "\n--- Eliminar Vehiculo ---" << endl;
    cout << "Ingrese la Placa del vehiculo que desea eliminar: ";
    getline(cin, placaBuscar);

    for (size_t i = 0; i < listaVehiculos.size(); i++)
    {
        if (listaVehiculos[i].placa == placaBuscar)
        {
            listaVehiculos.erase(listaVehiculos.begin() + i);
            cout << "¡Vehiculo con placa " << placaBuscar << " eliminado exitosamente!" << endl;
            return;
        }
    }
    cout << "¡ERROR: No se encontro ningun vehiculo con la placa " << placaBuscar << "!" << endl;
}

// 3. Eliminar Lavador por ID
void eliminarLavador(vector<Lavador> &listaLavadores)
{
    int idBuscar;
    cout << "\n--- Eliminar Lavador ---" << endl;
    cout << "Ingrese el ID del lavador que desea eliminar: ";
    cin >> idBuscar;
    cin.ignore();

    for (size_t i = 0; i < listaLavadores.size(); i++)
    {
        if (listaLavadores[i].id == idBuscar)
        {
            listaLavadores.erase(listaLavadores.begin() + i);
            cout << "¡Lavador con ID " << idBuscar << " eliminado exitosamente!" << endl;
            return;
        }
    }
    cout << "¡ERROR: No se encontro ningun lavador con el ID " << idBuscar << "!" << endl;
}

// --- FUNCIONES DE MODIFICACIÓN (CRUD - UPDATE) ---

// 1. Modificar Cliente por ID
void modificarCliente(vector<Cliente> &listaClientes)
{
    limpiarPantalla();
    int idBuscar;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "           MODIFICAR CLIENTE            " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Ingrese el ID del cliente a modificar: ";
    cin >> idBuscar;
    cin.ignore();

    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].id == idBuscar)
        {
            cout << AMARILLO << "\nDatos actuales -> Nombre: " << listaClientes[i].nombre
                 << " | Tel: " << listaClientes[i].telefono << RESET << endl;

            cout << "\nIngrese el NUEVO Nombre Completo: ";
            getline(cin, listaClientes[i].nombre);
            cout << "Ingrese el NUEVO Telefono: ";
            getline(cin, listaClientes[i].telefono);

            cout << VERDE << "\n¡Cliente modificado exitosamente en memoria!" << RESET << endl;
            return;
        }
    }
    cout << ROJO << "\n¡ERROR: No se encontro ningun cliente con la cedula " << idBuscar << "!" << RESET << endl;
}

// 2. Modificar Vehículo por Placa
void modificarVehiculo(vector<Vehiculo> &listaVehiculos, const vector<Cliente> &listaClientes)
{
    limpiarPantalla();
    string placaBuscar;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "          MODIFICAR VEHICULO            " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Ingrese la Placa del vehiculo a modificar: ";
    getline(cin, placaBuscar);

    for (size_t i = 0; i < listaVehiculos.size(); i++)
    {
        if (listaVehiculos[i].placa == placaBuscar)
        {
            cout << AMARILLO << "\nDatos actuales -> Modelo: " << listaVehiculos[i].modelo
                 << " | Color: " << listaVehiculos[i].color << " | CI Dueño: " << listaVehiculos[i].idDueno << RESET << endl;

            int nuevoIdDueno;
            cout << "\nIngrese la CI del NUEVO Dueño: ";
            cin >> nuevoIdDueno;
            cin.ignore();

          
            if (!existeCliente(listaClientes, nuevoIdDueno))
            {
                cout << ROJO << "¡ERROR: La cedula del cliente " << nuevoIdDueno << " no existe. Modificacion cancelada!" << RESET << endl;
                return;
            }

            listaVehiculos[i].idDueno = nuevoIdDueno;
            cout << "Ingrese el NUEVO Modelo: ";
            getline(cin, listaVehiculos[i].modelo);
            cout << "Ingrese el NUEVO Color: ";
            getline(cin, listaVehiculos[i].color);

            cout << VERDE << "\n¡Vehiculo modificado exitosamente!" << RESET << endl;
            return;
        }
    }
    cout << ROJO << "\n¡ERROR: No se encontro ningun vehiculo con la placa " << placaBuscar << "!" << RESET << endl;
}

// 3. Modificar Lavador por ID
void modificarLavador(vector<Lavador> &listaLavadores)
{
    limpiarPantalla();
    int idBuscar;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "           MODIFICAR LAVADOR            " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Ingrese el ID del lavador a modificar: ";
    cin >> idBuscar;
    cin.ignore();

    for (size_t i = 0; i < listaLavadores.size(); i++)
    {
        if (listaLavadores[i].id == idBuscar)
        {
            cout << AMARILLO << "\nDatos actuales -> Nombre: " << listaLavadores[i].nombre << RESET << endl;

            cout << "\nIngrese el NUEVO Nombre del Lavador: ";
            getline(cin, listaLavadores[i].nombre);

            cout << VERDE << "\n¡Lavador modificado exitosamente!" << RESET << endl;
            return;
        }
    }
    cout << ROJO << "\n¡ERROR: No se encontro ningun lavador con el ID " << idBuscar << "!" << RESET << endl;
}

#endif