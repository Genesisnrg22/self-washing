#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include "estructuras.h"

using namespace std;

const string RESET = "\033[0m";
const string ROJO = "\033[31m";
const string VERDE = "\033[32m";
const string AMARILLO = "\033[33m";
const string AZUL = "\033[34m";
const string CYAN = "\033[36m";

void limpiarPantalla()
{
    cout << "\033[2J\033[1;1H";
}

void esperarEnter()
{
    cout << "\nPresione " << AMARILLO << "[ENTER]" << RESET << " para continuar...";
    cin.get();
}

bool esNumeroValido(string str)
{
    if (str.empty())
        return false;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool esTextoValido(string str)
{
    if (str.empty())
        return false;
    for (size_t i = 0; i < str.length(); i++)
    {

        if (!isalpha(str[i]) && !isspace(str[i]))
            return false;
    }
    return true;
}

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

void agregarCliente(vector<Cliente> &listaClientes)
{
    limpiarPantalla();
    string entradaId;
    int idBuscar;

    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "       REGISTRAR NUEVO CLIENTE          " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;

    do
    {
        cout << "Ingrese la cedula del cliente (Solo numeros): ";
        getline(cin, entradaId);
        if (!esNumeroValido(entradaId))
        {
            cout << ROJO << "¡ERROR: La cedula debe contener unicamente numeros!" << RESET << endl;
        }
    } while (!esNumeroValido(entradaId));

    idBuscar = stoi(entradaId);

    if (existeCliente(listaClientes, idBuscar))
    {
        cout << ROJO << "\n¡ERROR: Ya existe un cliente con la cedula " << idBuscar << "!" << RESET << endl;
        esperarEnter();
        return;
    }

    Cliente nuevoCliente;
    nuevoCliente.id = idBuscar;

    do
    {
        cout << "Ingrese el Nombre Completo (Solo letras): ";
        getline(cin, nuevoCliente.nombre);
        if (!esTextoValido(nuevoCliente.nombre))
        {
            cout << ROJO << "¡ERROR: El nombre no puede contener numeros ni caracteres especiales!" << RESET << endl;
        }
    } while (!esTextoValido(nuevoCliente.nombre));

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

void agregarVehiculo(vector<Vehiculo> &listaVehiculos, const vector<Cliente> &listaClientes)
{

    limpiarPantalla();
    string placaBuscar;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "       REGISTRAR NUEVO VEHICULO         " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Ingrese la Placa: ";
    getline(cin, placaBuscar);

    if (existeVehiculo(listaVehiculos, placaBuscar))
    {
        cout << ROJO << "¡ERROR: La placa " << placaBuscar << " ya existe!" << RESET << endl;
        esperarEnter();
        return;
    }

    string entradaCedulaDueno;
    int cedulaDuenoBuscar;

    do
    {
        cout << "Ingrese la cedula del Dueno (Solo numeros): ";
        getline(cin, entradaCedulaDueno);
        if (!esNumeroValido(entradaCedulaDueno))
        {
            cout << ROJO << "¡ERROR: La cedula debe contener unicamente numeros!" << RESET << endl;
        }
    } while (!esNumeroValido(entradaCedulaDueno));

    cedulaDuenoBuscar = stoi(entradaCedulaDueno);

    if (!existeCliente(listaClientes, cedulaDuenoBuscar))
    {
        cout << ROJO << "¡ERROR: El cliente con cedula " << cedulaDuenoBuscar << " no esta registrado!" << RESET << endl;
        esperarEnter();
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
    cout << VERDE << "\n¡Vehiculo registrado con exito!" << RESET << endl;
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

void agregarLavador(vector<Lavador> &listaLavadores)
{
    limpiarPantalla();
    string entradaId;
    int idBuscar;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "       REGISTRAR NUEVO LAVADOR          " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;

    do
    {
        cout << "Ingrese el ID del Lavador (Solo numeros): ";
        getline(cin, entradaId);
        if (!esNumeroValido(entradaId))
        {
            cout << ROJO << "¡ERROR: El ID debe contener unicamente numeros!" << RESET << endl;
        }
    } while (!esNumeroValido(entradaId));

    idBuscar = stoi(entradaId);

    if (existeLavador(listaLavadores, idBuscar))
    {
        cout << ROJO << "¡ERROR: El lavador con ID " << idBuscar << " ya existe!" << RESET << endl;
        esperarEnter();
        return;
    }

    Lavador nuevoLavador;
nuevoFundador:
    nuevoLavador.id = idBuscar;

    do
    {
        cout << "Ingrese el Nombre (Solo letras): ";
        getline(cin, nuevoLavador.nombre);
        if (!esTextoValido(nuevoLavador.nombre))
        {
            cout << ROJO << "¡ERROR: El nombre no puede contener numeros!" << RESET << endl;
        }
    } while (!esTextoValido(nuevoLavador.nombre));

    listaLavadores.push_back(nuevoLavador);
    cout << VERDE << "¡Lavador registrado con exito!" << RESET << endl;
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

void registrarServicio(vector<Servicio> &listaServicios, const vector<Vehiculo> &listaVehiculos, const vector<Lavador> &listaLavadores)
{
    limpiarPantalla();
    Servicio nuevoServicio;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "       REGISTRAR NUEVO SERVICIO         " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Ingrese la Placa del Vehiculo: ";
    getline(cin, nuevoServicio.placaVehiculo);
    if (!existeVehiculo(listaVehiculos, nuevoServicio.placaVehiculo))
    {
        cout << ROJO << "¡ERROR: El vehiculo no existe!" << RESET << endl;
        esperarEnter();
        return;
    }

    string entradaIdLavador;
    cout << "Ingrese el ID del Lavador: ";
    getline(cin, entradaIdLavador);
    if (!esNumeroValido(entradaIdLavador))
    {
        cout << ROJO << "¡ERROR: El ID debe ser numerico!" << RESET << endl;
        esperarEnter();
        return;
    }
    nuevoServicio.idLavador = stoi(entradaIdLavador);

    if (!existeLavador(listaLavadores, nuevoServicio.idLavador))
    {
        cout << ROJO << "¡ERROR: El lavador no existe!" << RESET << endl;
        esperarEnter();
        return;
    }

    cout << "Ingrese la Fecha (DD/MM/AAAA): ";
    getline(cin, nuevoServicio.fecha);

    string entradaCosto;
    cout << "Ingrese el Costo: ";
    getline(cin, entradaCosto);
    try
    {
        nuevoServicio.costo = stof(entradaCosto);
    }
    catch (...)
    {
        cout << ROJO << "¡ERROR: Costo invalido!" << RESET << endl;
        esperarEnter();
        return;
    }

    listaServicios.push_back(nuevoServicio);
    cout << VERDE << "¡Servicio registrado con exito!" << RESET << endl;
    esperarEnter();
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

void eliminarCliente(vector<Cliente> &listaClientes)
{
    string entradaId;
    cout << "\n--- Eliminar Cliente ---" << endl;
    cout << "Ingrese la cedula del cliente que desea eliminar: ";
    getline(cin, entradaId);

    if (!esNumeroValido(entradaId))
    {
        cout << ROJO << "¡ERROR: Cedula invalida!" << RESET << endl;
        return;
    }
    int idBuscar = stoi(entradaId);

    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].id == idBuscar)
        {
            listaClientes.erase(listaClientes.begin() + i);
            cout << VERDE << "¡Cliente con cedula " << idBuscar << " eliminado exitosamente!" << RESET << endl;
            return;
        }
    }
    cout << ROJO << "¡ERROR: No se encontro ningun cliente con la cedula " << idBuscar << "!" << RESET << endl;
}

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
            cout << VERDE << "¡Vehiculo con placa " << placaBuscar << " eliminado exitosamente!" << RESET << endl;
            return;
        }
    }
    cout << ROJO << "¡ERROR: No se encontro ningun vehiculo con la placa " << placaBuscar << "!" << RESET << endl;
}

void eliminarLavador(vector<Lavador> &listaLavadores)
{
    string entradaId;
    cout << "\n--- Eliminar Lavador ---" << endl;
    cout << "Ingrese el ID del lavador que desea eliminar: ";
    getline(cin, entradaId);

    if (!esNumeroValido(entradaId))
    {
        cout << ROJO << "¡ERROR: ID invalido!" << RESET << endl;
        return;
    }
    int idBuscar = stoi(entradaId);

    for (size_t i = 0; i < listaLavadores.size(); i++)
    {
        if (listaLavadores[i].id == idBuscar)
        {
            listaLavadores.erase(listaLavadores.begin() + i);
            cout << VERDE << "¡Lavador con ID " << idBuscar << " eliminado exitosamente!" << RESET << endl;
            return;
        }
    }
    cout << ROJO << "¡ERROR: No se encontro ningun lavador con el ID " << idBuscar << "!" << RESET << endl;
}

void modificarCliente(vector<Cliente> &listaClientes)
{
    limpiarPantalla();
    string entradaId;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "           MODIFICAR CLIENTE            " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Ingrese la cedula del cliente a modificar: ";
    getline(cin, entradaId);

    if (!esNumeroValido(entradaId))
    {
        cout << ROJO << "¡ERROR: Cedula invalida!" << RESET << endl;
        return;
    }
    int idBuscar = stoi(entradaId);

    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].id == idBuscar)
        {
            cout << AMARILLO << "\nDatos actuales -> Nombre: " << listaClientes[i].nombre
                 << " | Tel: " << listaClientes[i].telefono << RESET << endl;

            string nuevoNombre;
            do
            {
                cout << "\nIngrese el NUEVO Nombre Completo (Solo letras): ";
                getline(cin, nuevoNombre);
                if (!esTextoValido(nuevoNombre))
                {
                    cout << ROJO << "¡ERROR: El nombre no puede tener numeros!" << RESET << endl;
                }
            } while (!esTextoValido(nuevoNombre));

            listaClientes[i].nombre = nuevoNombre;
            cout << "Ingrese el NUEVO Telefono: ";
            getline(cin, listaClientes[i].telefono);

            cout << VERDE << "\n¡Cliente modificado exitosamente!" << RESET << endl;
            return;
        }
    }
    cout << ROJO << "\n¡ERROR: No se encontro ningun cliente con la cedula " << idBuscar << "!" << RESET << endl;
}

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

            string entradaNuevoId;
            int nuevoIdDueno;
            do
            {
                cout << "\nIngrese la CI del NUEVO Dueño (Solo numeros): ";
                getline(cin, entradaNuevoId);
                if (!esNumeroValido(entradaNuevoId))
                {
                    cout << ROJO << "¡ERROR: La cedula debe ser numerica!" << RESET << endl;
                }
            } while (!esNumeroValido(entradaNuevoId));

            nuevoIdDueno = stoi(entradaNuevoId);

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

void modificarLavador(vector<Lavador> &listaLavadores)
{
    limpiarPantalla();
    string entradaId;
    cout << CYAN << "========================================" << RESET << endl;
    cout << CYAN << "           MODIFICAR LAVADOR            " << RESET << endl;
    cout << CYAN << "========================================" << RESET << endl;
    cout << "Ingrese el ID del lavador a modificar: ";
    getline(cin, entradaId);

    if (!esNumeroValido(entradaId))
    {
        cout << ROJO << "¡ERROR: ID invalido!" << RESET << endl;
        return;
    }
    int idBuscar = stoi(entradaId);

    for (size_t i = 0; i < listaLavadores.size(); i++)
    {
        if (listaLavadores[i].id == idBuscar)
        {
            cout << AMARILLO << "\nDatos actuales -> Nombre: " << listaLavadores[i].nombre << RESET << endl;

            string nuevoNombre;
            do
            {
                cout << "\nIngrese el NUEVO Nombre del Lavador (Solo letras): ";
                getline(cin, nuevoNombre);
                if (!esTextoValido(nuevoNombre))
                {
                    cout << ROJO << "¡ERROR: El nombre no puede tener numeros!" << RESET << endl;
                }
            } while (!esTextoValido(nuevoNombre));

            listaLavadores[i].nombre = nuevoNombre;
            cout << VERDE << "\n¡Lavador modificado exitosamente!" << RESET << endl;
            return;
        }
    }
    cout << ROJO << "\n¡ERROR: No se encontro ningun lavador con el ID " << idBuscar << "!" << RESET << endl;
}

string extraerValorJSON(string linea, bool esNumero = false)
{
    size_t posicionDosPuntos = linea.find(':');
    if (posicionDosPuntos == string::npos)
        return "";

    string parteValor = linea.substr(posicionDosPuntos + 1);

    if (!esNumero)
    {
        size_t primeraComilla = parteValor.find('"');
        size_t ultimaComilla = parteValor.rfind('"');
        if (primeraComilla != string::npos && ultimaComilla != string::npos && primeraComilla != ultimaComilla)
        {
            return parteValor.substr(primeraComilla + 1, ultimaComilla - primeraComilla - 1);
        }
    }
    else
    {
        string limpio = "";
        for (size_t i = 0; i < parteValor.length(); i++)
        {
            char c = parteValor[i];
            if (isdigit(c) || c == '.' || c == '-')
            {
                limpio += c;
            }
        }
        return limpio;
    }
    return "";
}

void cargarMasivaClientes(vector<Cliente> &listaClientes)
{
    ifstream archivo("carga_clientes.json");
    if (!archivo.is_open())
    {
        cout << ROJO << "\n[ERROR] No se pudo abrir el archivo 'carga_clientes.json'" << RESET << endl;
        return;
    }

    string linea;
    Cliente c;
    int cont = 0;

    while (getline(archivo, linea))
    {
        if (linea.find("\"id\"") != string::npos)
        {
            string val = extraerValorJSON(linea, true);
            c.id = val.empty() ? 0 : stoi(val);
        }
        else if (linea.find("\"nombre\"") != string::npos)
        {
            c.nombre = extraerValorJSON(linea, false);
        }
        else if (linea.find("\"telefono\"") != string::npos)
        {
            c.telefono = extraerValorJSON(linea, false);
            listaClientes.push_back(c);
            cont++;
        }
    }
    archivo.close();
    cout << VERDE << "\n[OK] ¡Carga masiva finalizada! Se importaron " << cont << " clientes." << RESET << endl;
}

void cargarMasivaVehiculos(vector<Vehiculo> &listaVehiculos)
{
    ifstream archivo("carga_vehiculos.json");
    if (!archivo.is_open())
    {
        cout << ROJO << "\n[ERROR] No se pudo abrir el archivo 'carga_vehiculos.json'" << RESET << endl;
        return;
    }

    string linea;
    Vehiculo v;
    int cont = 0;

    while (getline(archivo, linea))
    {
        if (linea.find("\"placa\"") != string::npos)
        {
            v.placa = extraerValorJSON(linea, false);
        }
        else if (linea.find("\"modelo\"") != string::npos)
        {
            v.modelo = extraerValorJSON(linea, false);
        }
        else if (linea.find("\"color\"") != string::npos)
        {
            v.color = extraerValorJSON(linea, false);
        }
        else if (linea.find("\"idDueno\"") != string::npos)
        {
            string val = extraerValorJSON(linea, true);
            v.idDueno = val.empty() ? 0 : stoi(val);
            listaVehiculos.push_back(v);
            cont++;
        }
    }
    archivo.close();
    cout << VERDE << "\n[OK] ¡Carga masiva finalizada! Se importaron " << cont << " vehiculos." << RESET << endl;
}

void cargarMasivaLavadores(vector<Lavador> &listaLavadores)
{
    ifstream archivo("carga_lavadores.json");
    if (!archivo.is_open())
    {
        cout << ROJO << "\n[ERROR] No se pudo abrir el archivo 'carga_lavadores.json'" << RESET << endl;
        return;
    }

    string linea;
    Lavador l;
    int cont = 0;

    while (getline(archivo, linea))
    {
        if (linea.find("\"id\"") != string::npos)
        {
            string val = extraerValorJSON(linea, true);
            l.id = val.empty() ? 0 : stoi(val);
        }
        else if (linea.find("\"nombre\"") != string::npos)
        {
            l.nombre = extraerValorJSON(linea, false);
            listaLavadores.push_back(l);
            cont++;
        }
    }
    archivo.close();
    cout << VERDE << "\n[OK] ¡Carga masiva finalizada! Se importaron " << cont << " lavadores." << RESET << endl;
}

void cargarMasivaServicios(vector<Servicio> &listaServicios)
{
    ifstream archivo("carga_servicios.json");
    if (!archivo.is_open())
    {
        cout << ROJO << "\n[ERROR] No se pudo abrir el archivo 'carga_servicios.json'" << RESET << endl;
        return;
    }

    string linea;
    Servicio s;
    int cont = 0;

    while (getline(archivo, linea))
    {
        if (linea.find("\"fecha\"") != string::npos)
        {
            s.fecha = extraerValorJSON(linea, false);
        }
        else if (linea.find("\"placaVehiculo\"") != string::npos)
        {
            s.placaVehiculo = extraerValorJSON(linea, false);
        }
        else if (linea.find("\"idLavador\"") != string::npos)
        {
            string val = extraerValorJSON(linea, true);
            s.idLavador = val.empty() ? 0 : stoi(val);
        }
        else if (linea.find("\"costo\"") != string::npos)
        {
            string val = extraerValorJSON(linea, true);
            s.costo = val.empty() ? 0.0f : stof(val);
            listaServicios.push_back(s);
            cont++;
        }
    }
    archivo.close();
    cout << VERDE << "\n[OK] ¡Carga masiva finalizada! Se importaron " << cont << " registros de lavado." << RESET << endl;
}

#endif