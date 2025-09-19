#include <stdio.h>
#include <stdlib.h>
#define MAX 30
#ifndef ANTIGUEDAD_H_INCLUDED
#define ANTIGUEDAD_H_INCLUDED

typedef struct
{
    int dia;
    int mes;
    int anio;
}stAntiguedad;

///PROTOTIPADOS

stAntiguedad cargarAntiguedad();
#endif // ANTIGUEDAD_H_INCLUDED
