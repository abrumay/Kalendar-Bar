#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sueldo.h"
#include "antiguedad.h"
#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

///Estructuras
#define MAX 30
#define ARCHIVOUSUARIOS "usuarios.dat"
#define ARCHIVOHISTORIAL "usuarios.sueldo"


typedef struct
{
    char nombre[MAX];
    char apellido[MAX];
    char dni[MAX];
} stPersona;

typedef struct
{
    char contrasenia[MAX];
    int tipo;
    int baja;
    stSueldo sueldo;
    stPersona persona;
    stAntiguedad antiguedad;
} stUsuario;

///Prototipados
stUsuario cargarUnUsuario();
int contarRegistrosEnArchivo ();
int buscarUsuario(char dni[]);
stUsuario buscarUsuarioLogin(char dni[], char pass[]);
void cargarUsuarioAdmin();
void mostrarArchivoUsuarios(char archivo[]);
void mostrarUsuario(stUsuario aux);
int ValidacionNombreYApellidoUsuario(char palabra[]);
int ValidacionDniUsuario(char palabra[]);
int ValidacionContraseniaUsuario(char palabra[]);
int pasarDelArchivoAlArreglo(stUsuario arreglo[], char nombrearchivo[]);
void ingresarAntiguedadAMatriz(int dimF, int dimC, int matrizDnis[dimF][dimC], stUsuario user, int validos);
void buscarEmpleado(char archivo[], char dni[]);
stUsuario retornarUsuarioPorDNI(char DNI[]);
void cargarSueldoAlUsuario(char archivo[], char archivo2[], stUsuario user);
void modificarEmpleado (char archivo[], char dni[]);
void insertarEmpleadoPorNombre (stUsuario arregloEmpleado[], int i, stUsuario empleado);
void ordenamientoPorNombre (stUsuario empleado[], int validos);
void mostrarArregloEmpleados(stUsuario arreglo[], int validos);
void insertarEmpleadoPorPuestoDeTrabajo (stUsuario arregloEmpleado[], int i, stUsuario empleado);
void ordenamientoPorPuestoDeTrabajo (stUsuario empleado[], int validos);
void insertarEmpleadoPorDNI (stUsuario arregloEmpleado[], int i, stUsuario empleado);
void ordenamientoPorDNI (stUsuario empleado[], int validos);
void modificarDatosEmpleado(char archivo[], char dni[]);
void mostrarHistorialSueldo (char archivo[], char dni[]);
void cargarMatrizDeFechaDeRegistro(int dimF, int dimC, int MatrizUsuarios[dimF][dimC], char archivo[]);
void mostrarMatrizAntiguedad(int dimF, int dimC, int MatrizUsuarios[dimF][dimC]);
int CargarArrregloDeBeneficiosSindicales(char M[][MAX], int dimF);
void MostrarArregloStrings (char M[][MAX], int validos);

#endif // USUARIO_H_INCLUDED
