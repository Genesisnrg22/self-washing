#include <iostream>
#include <vector>
#include "estructuras.h"
#include "funciones.h"

using namespace std;

int main()
{
    vector<Cliente> misClientes;
    vector<Vehiculo> misVehiculos;
    vector<Lavador> misLavadores;
    vector<Servicio> misServicios;

    cargarClientesDesdeArchivo(misClientes);
    cargarVehiculosDesdeArchivo(misVehiculos);
    cargarLavadoresDesdeArchivo(misLavadores);
    cargarServiciosDesdeArchivo(misServicios);

    int opcion;
    char confirmarSalir;

    do
    {
        limpiarPantalla();
        cout << CYAN << "=========================================================================" << RESET << endl;
        cout << CYAN << "                    SISTEMA DE GESTION DE AUTOLAVADO                     " << RESET << endl;
        cout << CYAN << "=========================================================================" << RESET << endl;

        cout << AZUL << " [1]" << RESET << " Agregar Cliente  |" << AZUL << " [5]" << RESET << " Agregar Vehiculo |" << AZUL << " [9]" << RESET << " Agregar Lavador" << endl;
        cout << AZUL << " [2]" << RESET << " Listar Clientes   |" << AZUL << " [6]" << RESET << " Listar Vehiculos  |" << AZUL << " [10]" << RESET << " Listar Lavadores" << endl;
        cout << AZUL << " [3]" << RESET << " Modificar Cliente |" << AZUL << " [7]" << RESET << " Modificar Vehiculo|" << AZUL << " [11]" << RESET << " Modificar Lavador" << endl;
        cout << AZUL << " [4]" << RESET << " Eliminar Cliente  |" << AZUL << " [8]" << RESET << " Eliminar Vehiculo |" << AZUL << " [12]" << RESET << " Eliminar Lavador" << endl;

        cout << CYAN << "-------------------------------------------------------------------------" << RESET << endl;
        cout << AMARILLO << " [13]" << RESET << " Registrar Servicio de Lavado" << endl;
        cout << AMARILLO << " [14]" << RESET << " Listar Historial de Lavados" << endl;
        cout << ROJO << " [15]" << RESET << " Salir del Sistema" << endl;
        cout << CYAN << "=========================================================================" << RESET << endl;
        cout << AMARILLO << " Recuerde usar la opcion [15] para guardar sus cambios en los archivos." << RESET << endl;
        cout << CYAN << "=========================================================================" << RESET << endl;
        cout << "Seleccione una opcion numérica: ";

        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            agregarCliente(misClientes);
            break;
        case 2:
            limpiarPantalla();
            listarClientes(misClientes);
            esperarEnter();
            break;
        case 3:
            modificarCliente(misClientes);
            esperarEnter();
            break;
        case 4:
            eliminarCliente(misClientes);
            esperarEnter();
            break;

        case 5:
            agregarVehiculo(misVehiculos, misClientes);
            esperarEnter();
            break;
        case 6:
            limpiarPantalla();
            listarVehiculos(misVehiculos);
            esperarEnter();
            break;
        case 7:
            modificarVehiculo(misVehiculos, misClientes);
            esperarEnter();
            break;
        case 8:
            eliminarVehiculo(misVehiculos);
            esperarEnter();
            break;

        case 9:
            agregarLavador(misLavadores);
            esperarEnter();
            break;
        case 10:
            limpiarPantalla();
            listarLavadores(misLavadores);
            esperarEnter();
            break;
        case 11:
            modificarLavador(misLavadores);
            esperarEnter();
            break;
        case 12:
            eliminarLavador(misLavadores);
            esperarEnter();
            break;

        case 13:
            registrarServicio(misServicios, misVehiculos, misLavadores);
            esperarEnter();
            break;
        case 14:
            limpiarPantalla();
            listarServicios(misServicios);
            esperarEnter();
            break;

        case 15:
            limpiarPantalla();
            cout << AMARILLO << "=========================================================" << RESET << endl;
            cout << AMARILLO << "                CONFIRMACION DE SALIDA                   " << RESET << endl;
            cout << AMARILLO << "=========================================================" << RESET << endl;
            cout << "¿Esta seguro que desea guardar los datos y salir? (S/N): ";
            cin >> confirmarSalir;
            cin.ignore();

            if (confirmarSalir == 'S' || confirmarSalir == 's')
            {
                guardarClientesEnArchivo(misClientes);
                guardarVehiculosEnArchivo(misVehiculos);
                guardarLavadoresEnArchivo(misLavadores);
                guardarServiciosEnArchivo(misServicios);

                cout << VERDE << "\n[OK] ¡Todos los cambios se guardaron con exito!" << RESET << endl;
                cout << "¡Gracias por usar el sistema!" << endl;
            }
            else
            {
                cout << CYAN << "\nOperacion cancelada. Volviendo al menu..." << endl;
                opcion = 0;
                esperarEnter();
            }
            break;

        default:
            cout << ROJO << "Opcion invalida. Intente de nuevo." << RESET << endl;
            esperarEnter();
        }
    } while (opcion != 15);

    return 0;
}