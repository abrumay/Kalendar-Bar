#include <stdio.h>
#include <stdlib.h>
#ifndef SUELDO_H_INCLUDED
#define SUELDO_H_INCLUDED
#define MAX 30

typedef struct
{
    float montoFinal;
    float montoBruto;
    int horasTrabajadas; //si
    float aporteJubilatorio;
    float obraSocial;
    float seguroDeVida;
    char puestoDeTrabajo[MAX];
    float aporteSindical;
    int horasExtras;//si
} stSueldo;

///PROTITIPADOS
void listaDeTrabajos();
int detectarHorasExtraMensual(int horas);
float calcularAporteSindical(float monto);
float calcularAporteJubilatorio(float monto);
float calcularObraSocial(float monto);
float calcularSeguroDeVida (float monto);
int detectarHorasExtraMensual(int horas);
stSueldo sueldoDeEmpleado (stSueldo sueldoaux, char puestoDeTrabajo[]);
void mostrarSueldoEmpleado(stSueldo sueldoaux);
void mostrarSueldoCompleto(stSueldo sueldoaux);
float calcularMontoFinal (float aporteSindical, float aporteJubilatorio, float obraSocial, float seguroDeVida, float montoBruto);
stSueldo modificarSueldoEmpleado (char archivo[], char dni[]);
int validacionPuestoDeTrabajo (char puestoDeTrabajo[]);
#endif // SUELDO_H_INCLUDED
