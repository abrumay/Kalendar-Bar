#include <ctype.h>
#include "pila.h"
#include "sueldo.h"
#include <string.h>
#include <time.h>
#define MAX 30

const char cocinero [MAX]= "cocinero";
const char barman [MAX] = "barman";
const char cajero [MAX] = "cajero";
const char encargado [MAX] = "encargado";
const char camarero [MAX]= "camarero";
const char bachero [MAX]="bachero";
const int dimF = 30;
const int dimC = 3;

///FUNCION QUE MODIFICA DATOS DEL SUELDO(PUESTO DE TRABAJOS Y HORAS TRABAJADAS)
stSueldo modificarSueldoEmpleado (char archivo[], char dni[])
{

    int flag = 0;
    float sueldoBruto = 0;
    float obrasocialaux = 0;
    float aporteJubilacion = 0;
    float aporteSindicalista = 0;
    float seguroDeVidas = 0;
    float sueldoFinal = 0;
    char puestoDeTrabajo[MAX];
    stSueldo sueldoEmpleado;

    system("cls");
    printf("\n\t\t\tMODIFICAR SUELDO DE EMPLEADO\n");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    listaDeTrabajos();
    while (flag == 0)
    {
        printf("\n\t\t\tIngrese el puesto de trabajo: ");
        fflush(stdin);
        gets(puestoDeTrabajo);
        flag = validacionPuestoDeTrabajo(puestoDeTrabajo);
        if (flag == 0)
        {
            printf("\n\t\t\tIngreso un puesto de trabajo incorrecto, lea bien\n");
        }
    }
    sueldoEmpleado = sueldoDeEmpleado(sueldoEmpleado, puestoDeTrabajo);

    strcpy(sueldoEmpleado.puestoDeTrabajo, puestoDeTrabajo);

    sueldoBruto = sueldoEmpleado.montoBruto;

    aporteSindicalista = calcularAporteSindical(sueldoBruto);
    sueldoEmpleado.aporteSindical = aporteSindicalista;

    aporteJubilacion = calcularAporteJubilatorio(sueldoBruto);
    sueldoEmpleado.aporteJubilatorio = aporteJubilacion;

    obrasocialaux = calcularObraSocial(sueldoBruto);
    sueldoEmpleado.obraSocial = obrasocialaux;

    seguroDeVidas = calcularSeguroDeVida(sueldoBruto);
    sueldoEmpleado.seguroDeVida = seguroDeVidas;

    sueldoFinal = calcularMontoFinal(aporteSindicalista, aporteJubilacion, obrasocialaux, seguroDeVidas, sueldoBruto);
    sueldoEmpleado.montoFinal = sueldoFinal;

    printf("\n\t\t\tSe cargo con el exito el sueldo\n");

    return sueldoEmpleado;
}

///FUNCION QUE CALCULA UN MONTO QUE SE RESTA AL SUELDO BRUTO
float calcularAporteSindical(float monto)
{
    float aporteSindicalAux;
    aporteSindicalAux = (float) monto*0.025; /// aporte sindical de tipo gastronomico : 2.5%

    return aporteSindicalAux;
}

///FUNCION QUE CALCULA UN MONTO QUE SE RESTA AL SUELDO BRUTO
float calcularAporteJubilatorio(float monto)
{
    float aporteJubilatorioAux;
    aporteJubilatorioAux = (float) monto*0.11; /// aporte jubilatorio argentina : 11%

    return aporteJubilatorioAux;
}

///FUNCION QUE CALCULA UN MONTO QUE SE RESTA AL SUELDO BRUTO
float calcularObraSocial(float monto)
{
    float obraSocialAux;
    obraSocialAux = (float) monto*0.03; /// aporte minimo obra social argentina : 3%

    return obraSocialAux;
}

///FUNCION QUE CALCULA UN MONTO QUE SE RESTA AL SUELDO BRUTO
float calcularSeguroDeVida (float monto)
{
    float seguroVida = 0;
    seguroVida = monto * 0.03;
    return seguroVida;
}

///FUNCION QUE CALCULA HORAS EXTRA DE UN EMPLEADO
int detectarHorasExtraMensual(int horas)
{
    int horasExtra = 0;
    if(horas > 8)
    {
        horasExtra = horas - 8;
    }
    return horasExtra;
}

///LISTAS DE TRABAJO QUE SE MUESTRAN DURANTE LA CARGA DEL PUESTO DE TRABAJO
void listaDeTrabajos()
{
    ///LOS TRABAJOS SON DECLARADOS COMO ARREGLOS CONSTANTES Y NO ESTRUCTURAS ASI PODEMOS AGREGAR MAS FACIL LOS DATOS
    ///ESTA LISTA COMPLETA APARECE ANTES DE QUE EL ADMIN MODIFIQUE UN SUELDO ASI SEPA QUE PONER AUTOMATICAMENTE
    ///AGREGAR HORAS MINIMAS A CADA TRABAJO, SU PAGO POR HORA
    /// SE PUEDE AGREGAR HORAS MININAS REQUERIDAS PARA CADA TRABAJO Y EDITAR EL NUM RANDOM EN LA FUNCION DE ABAJO

    printf("\n\t\t\tCOCINERO, 500, TIPO DE PAGO (MENSUAL)\n");
    printf("\n\t\t\tBARMAN 700, TIPO DE PAGO (MENSUAL)\n");
    printf("\n\t\t\tCAJERO 400, TIPO DE PAGO (DIARIO)\n");
    printf("\n\t\t\tENCARGADO 800, TIPO DE PAGO (MENSUAL)\n");
    printf("\n\t\t\tCAMARERO  300, TIPO DE PAGO (DIARIO)\n");
    printf("\n\t\t\tBACHERO  300, TIPO DE PAGO (DIARIO)\n");
}

///FUNCION QUE CALCULA EL MONTO BRUTO DE UN EMPLEADO Y ASIGNA EL PUESTO DE TRABAJO
stSueldo sueldoDeEmpleado (stSueldo sueldoaux, char puestoDeTrabajo[])
{
    /// CALCULA CON NUM RANDOM ENTRE 8 Y 12 LAS HORAS TRABAJADAS PARA CALCULAR MONTO
    ///FALTA LOS APORTES, OBRA SOCIAL ETC QUE SE RESTAN DEL MONTO TOTAL
    int horas=0;
    int horasExtra=0;
    int monto = 0;
    if((strcmp(puestoDeTrabajo, cocinero) == 0))
    {
        srand(time(NULL));
        horas=rand() % 5 + 8;
        sueldoaux.horasTrabajadas = horas;
        horas = horas * 28;
        horasExtra = detectarHorasExtraMensual(horas);
        sueldoaux.horasExtras = horasExtra;
        monto = horas  * 500;
        sueldoaux.montoBruto = monto;
        strcpy(sueldoaux.puestoDeTrabajo, cocinero);
    }
    else if((strcmp(puestoDeTrabajo, barman) == 0))
    {
        srand(time(NULL));
        horas=rand() % 5 + 8;
        sueldoaux.horasTrabajadas = horas;
        horas = horas * 28;
        horasExtra = detectarHorasExtraMensual(horas);
        sueldoaux.horasExtras = horasExtra;
        monto = horas* 700;
        sueldoaux.montoBruto = monto;
        strcpy(sueldoaux.puestoDeTrabajo, barman);
    }
    else if((strcmp(puestoDeTrabajo, cajero) == 0))
    {
        printf("\n\t\t\tIngrese las horas trabajadas por este empleado: ");
        scanf("%i", &horas);
        sueldoaux.horasTrabajadas = horas;
        horasExtra = detectarHorasExtraMensual(horas);
        sueldoaux.horasExtras = horasExtra;
        monto = horas* 400;
        sueldoaux.montoBruto = monto;
        strcpy(sueldoaux.puestoDeTrabajo, cajero);
    }
    else if((strcmp(puestoDeTrabajo, encargado) == 0))
    {
        srand(time(NULL));
        horas=rand() % 5 + 8;
        sueldoaux.horasTrabajadas = horas;
        horas = horas * 28;
        horasExtra = detectarHorasExtraMensual(horas);
        sueldoaux.horasExtras = horasExtra;
        monto = horas *800;
        sueldoaux.montoBruto = monto;
        strcpy(sueldoaux.puestoDeTrabajo, encargado);
    }
    else if((strcmp(puestoDeTrabajo, camarero) == 0))
    {
        printf("\n\t\t\tIngrese las horas trabajadas por este empleado: ");
        scanf("%i", &horas);
        sueldoaux.horasTrabajadas = horas;
        horasExtra = detectarHorasExtraMensual(horas);
        sueldoaux.horasExtras = horasExtra;
        monto = horas *300;
        sueldoaux.montoBruto = monto;
        strcpy(sueldoaux.puestoDeTrabajo, camarero);
    }
    else if((strcmp(puestoDeTrabajo, bachero) == 0))
    {
        printf("\n\t\t\tIngrese las horas trabajadas por este empleado: ");
        scanf("%i", &horas);
        sueldoaux.horasTrabajadas = horas;
        horasExtra = detectarHorasExtraMensual(horas);
        sueldoaux.horasExtras = horasExtra;
        monto = horas *300;
        sueldoaux.montoBruto = monto;
        strcpy(sueldoaux.puestoDeTrabajo, bachero);
    }
    return sueldoaux;
}

///FUNCION QUE CALCULA EL SUELDO NETO DE UN EMPLEADO
float calcularMontoFinal (float aporteSindical, float aporteJubilatorio, float obraSocial, float seguroDeVida, float montoBruto)
{
    float montoFinal = montoBruto - (aporteSindical + aporteJubilatorio + obraSocial + seguroDeVida);
    return montoFinal;
}

///FUNCION QUE MUESTRA SUELDO Y HORAS TRABAJADAS DE UN EMPLEADO
void mostrarSueldoEmpleado(stSueldo sueldoaux)
{
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("\tSueldo Bruto:               $%g\n", sueldoaux.montoBruto);
        printf("\tSueldo Final:               $%g\n", sueldoaux.montoFinal);
        printf("\tHoras trabajadas:            %i\n", sueldoaux.horasTrabajadas);

}

///FUNCION QUE MUESTRA EL SUELDO COMPLETO DE UN USUARIO
void mostrarSueldoCompleto(stSueldo sueldoaux)
{
    mostrarSueldoEmpleado(sueldoaux);
    {
        printf("\tHoras Extra:                %i\n", sueldoaux.horasExtras);
        printf("\tAporte Jubilatorio:        -$%g\n", sueldoaux.aporteJubilatorio);
        printf("\tAporte Sindical:           -$%g\n", sueldoaux.aporteSindical);
        printf("\tObra Social:               -$%g\n", sueldoaux.obraSocial);
        printf("\tSeguro de Vida:            -$%g\n", sueldoaux.seguroDeVida);
        printf("\tPuesto de trabajo:         %s\n", sueldoaux.puestoDeTrabajo);
    }
}

///FUNCION QUE VALIDA EL PUESTO DE TRABAJO DE UN EMPLEADO
int validacionPuestoDeTrabajo (char puestoDeTrabajo[])
{
    int flag = 0;

    if((strcmp(puestoDeTrabajo, cocinero) == 0))
    {
       flag = 1;
    }
    else if((strcmp(puestoDeTrabajo, barman) == 0))
    {
        flag = 1;
    }
    else if((strcmp(puestoDeTrabajo, cajero) == 0))
    {
        flag = 1;
    }
    else if((strcmp(puestoDeTrabajo, encargado) == 0))
    {
          flag = 1;
    }
    else if((strcmp(puestoDeTrabajo, camarero) == 0))
    {
           flag = 1;
    }
    else if((strcmp(puestoDeTrabajo, bachero) == 0))
    {
           flag = 1;
    }
    return flag;
}
