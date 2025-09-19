#include <ctype.h>
#include "antiguedad.h"
#include <string.h>
#include <time.h>
#define MAX 30

///FUNCION QUE CARGA LA ANTIGUEDAD A TIEMPO REAL DE UN EMPLEADO
stAntiguedad cargarAntiguedad() {

    stAntiguedad antiguedad;

    time_t tiempo = time(NULL);
    struct tm *tiempoLocal = localtime(&tiempo);

    antiguedad.dia = tiempoLocal->tm_mday;
    antiguedad.mes = tiempoLocal->tm_mon + 1;
    antiguedad.anio = tiempoLocal->tm_year + 1900;

    return antiguedad;
}
