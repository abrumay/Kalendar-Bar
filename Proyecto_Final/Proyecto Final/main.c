#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "usuario.h"
#include <string.h>
#include <conio.h>
#include <ctype.h>

const char nombreEmpresa[]="Kalendar Bar";


///PERFIL ADMINISTRADOR = DNI 45290871 CONTRASENIA fausto


void menu();
void registrarse();
stUsuario iniciarSesion();
void menuAdmin(stUsuario admin);
void menuUsuario(stUsuario user);
Pila cargarDadosDeBaja (char archivo[]);
int EncontrarMenor(Pila *baja);
Pila OrdenamientoPorSeleccion(Pila desordenada);

int main()
{

    menu();
    return 0;
}

///FUNCION MENU PRINCIPAL QUE LLAMA AL MENU ADMIN , MENU USUARIO, INICIAR SESION Y REGISTRARSE
void menu()
{
    char op;
    stUsuario user;

    do
    {
        system("cls");
        printf("\t\t\t\t=================================\n");
        printf("\t\t\t\tBienvenidos a %s\n", nombreEmpresa);
        printf("\t\t\t\t=================================\n");
        printf("\n\t\t\t\t[1]. Iniciar sesion\n");
        printf("\t\t\t\t[2]. Registrarse\n");
        printf("\t\t\t\t[ESC]. Salir\n");


        op=getch();

        system("cls");

        switch(op)
        {

        case 49:
            system("cls");
            printf("\t\t\t\t=================================\n");
            printf("\t\t\t\tBienvenido a %s\n", nombreEmpresa);
            printf("\t\t\t\t=================================\n");
            printf("\n\n\t\t\t\tInicio de sesion\n");

            user=iniciarSesion();

            if(user.tipo == 1 && user.baja == 0)
            {
                menuAdmin(user);
            }
            else if(user.tipo == 2 && user.baja == 0)
            {
                menuUsuario(user);
            }
            else
            {
                printf("\n\n\t\t\t\tNo se encotro el usuario o se dio de baja.\n");

            }
            system("pause");
            system("cls");
            break;

        case 50:
            system("cls");
            printf("\t\t\t\t=================================\n");
            printf("\t\t\t\tBienvenido a %s\n", nombreEmpresa);
            printf("\t\t\t\t=================================\n");
            printf("\n\n\t\t\t\tRegistro\n");
            registrarse();
            system("pause");
            break;
        case 27:
            break;

        default:
            break;


        }

    }
    while(op != 27);
}

///FUNCION QUE PERMITE CARGAR UNA ESTRUCTURA TIPO USUARIO AL ARCHIVO CON VALIDACIONES
void registrarse()
{
    FILE* buffer = fopen(ARCHIVOUSUARIOS, "ab");
    char dniadmin[MAX]="45290871";

    if(buffer)
    {

        int exit = 0;
        int control=0;
        char dni[MAX];
        while(exit == 0)
        {
            printf("\n\n\t\t\t\tIngrese DNI:");
            gets(dni);
            control = ValidacionDniUsuario(dni);

            if(control==0)
            {
                printf("\n\t\t\t\tIngreso un dni incorrecto (solo numeros)\n");
                exit=0;
            }
            else
            {
                //control = 1;
                exit = 1;
            }

        }
        int encontrado = buscarUsuario(dni);
        if(encontrado == 0)
        {
            stUsuario usuario = cargarUnUsuario();
            strcpy(usuario.persona.dni,dni);
            printf("\n\t\t\t\tHas sido registrado con exito\n");
            if((strcmp(usuario.persona.dni, dniadmin) == 0))
            {
                usuario.tipo = 1;
            }
            fwrite(&usuario, sizeof(stUsuario), 1, buffer);
        }
        else
        {
            printf("\n\t\t\t\tEl DNI ya se encuentra registrado en el sistema\n");
        }
        fclose(buffer);
    }
}

///FUNCION QUE PERMITE INGRESAR DNI Y CONTRASENIA PARA INICIAR SESION EN ALGUN MENU (USUARIO O ADMIN)
stUsuario iniciarSesion ()
{
    char dni[MAX];
    char pass[MAX];
    stUsuario usuario;
    printf("\n\n\t\t\t\tIngrese su DNI: ");
    fflush(stdin);
    gets(dni);
    printf("\n\t\t\t\tIngrese su contrase%ca: ", 164);
    fflush(stdin);
    gets(pass);

    usuario = buscarUsuarioLogin(dni, pass);

    return usuario;
}

///FUNCION DE ADMIN SOLO PARA USUARIOS TIPO 1 (ADMIN), PERMITE LA MODIFICACION DE LAS ESTRUCTURAS USUARIOS
void menuAdmin(stUsuario admin)
{
    char op;
    char dni[MAX];
    int matrizUsuarios[MAX][MAX];
    Pila baja;
    inicpila(&baja);
    int cantidad = 0;
    int eleccion = 0;
    stUsuario arregloEmpleado[MAX];
    do
    {
        system("cls");
        printf("\t\t\t=============================================\n");
        printf("\t\t\tBienvenido %s a %s\n", admin.persona.nombre, nombreEmpresa);
        printf("\t\t\t=============================================\n");
        printf("\n\t\t\t[1]. Mostrar todos los empleados registrados\n");
        printf("\t\t\t[2]. Modificar propiedades de un empleado\n");
        printf("\t\t\t[3]. Modificar sueldo de un empleado\n");
        printf("\t\t\t[4]. Mostrar dni de empleados dados de baja\n");
        printf("\t\t\t[5]. Mostrar matriz de fecha de registro de empleados\n");
        printf("\t\t\t[ESC]. Cerrar sesion\n");

        op=getch();

        system("cls");

        switch(op)
        {

        case 49:
            printf("\n\t\t\t\t\tComo desea ver a los empleados?\n\n");
            printf("\n\t\t\t[1]. Mostrar todos los empleados por orden de registro\n");
            printf("\t\t\t[2]. Mostrar todos los empleados por orden alfabetico\n");
            printf("\t\t\t[3]. Mostrar todos los empleados por puesto de trabajo\n");
            printf("\t\t\t[4]. Mostrar todos los empleados por orden de DNI\n");
            printf("\t\t\t[5]. Salir\n");
            scanf("\t\t\t%i", &eleccion);
            if(eleccion == 1)
            {
                system("cls");
                printf("\n\t\t\t\t\tLISTA DE EMPLEADOS\n\n");
                mostrarArchivoUsuarios(ARCHIVOUSUARIOS);
            }
            else if (eleccion == 2)
            {
                system("cls");
                printf("\n\t\t\t\t\tLISTA DE EMPLEADOS\n\n");
                cantidad = contarRegistrosEnArchivo(ARCHIVOUSUARIOS);
                printf("Cantidad de estructuras en el archivo: ");
                printf("%i\n", cantidad);
                cantidad = pasarDelArchivoAlArreglo(arregloEmpleado, ARCHIVOUSUARIOS);
                ordenamientoPorNombre(arregloEmpleado, cantidad);
                mostrarArregloEmpleados(arregloEmpleado, cantidad);
            }
            else if(eleccion == 3)
            {
                system("cls");
                printf("\n\t\t\t\t\tLISTA DE EMPLEADOS\n\n");
                cantidad = contarRegistrosEnArchivo(ARCHIVOUSUARIOS);
                printf("Cantidad de estructuras en el archivo: ");
                printf("%i\n", cantidad);
                cantidad = pasarDelArchivoAlArreglo(arregloEmpleado, ARCHIVOUSUARIOS);
                ordenamientoPorPuestoDeTrabajo(arregloEmpleado, cantidad);
                mostrarArregloEmpleados(arregloEmpleado, cantidad);
            }
            else if (eleccion == 4)
            {
                 system("cls");
                 printf("\n\t\t\t\t\tLISTA DE EMPLEADOS\n\n");
                 cantidad = contarRegistrosEnArchivo(ARCHIVOUSUARIOS);
                 printf("Cantidad de estructuras en el archivo: ");
                 printf("%i\n", cantidad);
                 cantidad = pasarDelArchivoAlArreglo(arregloEmpleado, ARCHIVOUSUARIOS);
                 ordenamientoPorDNI(arregloEmpleado, cantidad);
                 mostrarArregloEmpleados(arregloEmpleado, cantidad);

            }

            ///Funcion mostrar usuarios.
            system("pause");
            system("cls");
            break;

        case 50:
            printf("\n\t\t\t\t\tModificar propiedades de un empleado\n");
            mostrarArchivoUsuarios(ARCHIVOUSUARIOS);
            printf("\n\t\t\tQue empleado desea modificar (ingrese el DNI) :");
            fflush(stdin);
            gets(dni);
            modificarEmpleado(ARCHIVOUSUARIOS, dni);
            system("pause");
            break;
        case 51:
            printf("\n\t\t\t\t\tModificar sueldo de un empleado\n");
            mostrarArchivoUsuarios(ARCHIVOUSUARIOS);
            printf("Ingrese el DNI del empleado al que desea modificar su sueldo: ");
            stUsuario aux;
            gets(dni);
            if(buscarUsuario(dni))
            {
                aux = retornarUsuarioPorDNI(dni);
                cargarSueldoAlUsuario(ARCHIVOUSUARIOS, ARCHIVOHISTORIAL, aux);
            }
            else
            {
                printf("\n\t\t\t\t\tNo existe el usuario\n");
            }
            system("pause");
            break;
        case 52:
            printf("\n\t\t\t\t\tEmpleados dados de baja\n");
            baja = cargarDadosDeBaja(ARCHIVOUSUARIOS);
            mostrar(&baja);
            system("pause");
            break;
        case 53:
             printf("\n\t\t\t\t\tFecha de registro de empleados\n");
             cantidad = contarRegistrosEnArchivo(ARCHIVOUSUARIOS);
             cargarMatrizDeFechaDeRegistro(cantidad, 4, matrizUsuarios, ARCHIVOUSUARIOS);
             printf("[     DNI    ][ DIA  ][ MES ][   A%cO  ]\n", 165);
             mostrarMatrizAntiguedad(cantidad, 4, matrizUsuarios);
             system("pause");
             break;
        case 27:
            break;

        default:
            break;


        }

    }
    while(op != 27);
}

///FUNCION DE USUARIO O EMPLEADO QUE PERMITE VER TODOS LOS DATOS DEL SUELDO CORRESPONDIENTE AL USUARIO
void menuUsuario(stUsuario user)
{
    char op;
    int validos=0;
    char beneficios[5][MAX];
    Pila antiguedad;
    inicpila(&antiguedad);
    do
    {
        system("cls");
        printf("\t\t\t~~~~~~~~~~~~~~~ MENU PRINCIPAL ~~~~~~~~~~~~~~~\n");
        printf("\t\t\tBienvenido %s a %s               \n", user.persona.nombre, nombreEmpresa);
        printf("\t\t\t                                 \n");
        printf("\t\t\t\nNombre de usuario: %s          \n", user.persona.nombre);
        printf("\t\t\t\nApellido de usuario: %s        \n", user.persona.apellido);
        printf("\t\t\t\nDNI de usuario: %s             \n", user.persona.dni);
        printf("\t\t\t            OPCIONES             \n");
        printf("\t\t\t\n [1].Ver su sueldo             \n");
        printf("\t\t\t\n [2].Ver su historial de sueldo\n");
        printf("\t\t\t\n [3].Modificar datos           \n");
        printf("\t\t\t\n [4].Mostrar beneficios sindicales          \n");
        printf("\t\t\t\n [ESC].Cerrar sesion\n");
        op=getch();

        system("cls");

        switch(op)
        {

        case 49:
            printf("\n\t\t\t\t\tDatos del sueldo\n\n");
            ///SUELDO, HORAS TRABAJADAS, APORTE DE JUBILACION, OBRA SOCIAL, TIPO DE RECIBO DE SUELDO, APORTE SINDICAL, HORAS EXTRA
            mostrarSueldoCompleto(user.sueldo);
            system("pause");
            system("cls");
            break;
        case 50:
            printf("\n\t\t\t\t\tHistorial de sueldo\n");
            mostrarHistorialSueldo(ARCHIVOHISTORIAL, user.persona.dni);
            system("pause");
            system("cls");
            break;
        case 51:
            modificarDatosEmpleado(ARCHIVOUSUARIOS, user.persona.dni);
            system("pause");
            system("cls");
            break;
        case 52:
            validos= CargarArrregloDeBeneficiosSindicales(beneficios, 5);
            MostrarArregloStrings (beneficios, validos);
            system("pause");
            system("cls");
            break;
        case 27:
            break;

        default:
            break;


        }

    }
    while(op != 27);

}

///FUNCION QUE RECIBE EMPLEADOS DADOS DE BAJA Y GUARDA SU DNI EN UNA PILA DE FORMA ORDENADA POR SELECCION
Pila cargarDadosDeBaja (char archivo[])
{
    Pila baja;
    Pila aux;
    inicpila(&baja);
    inicpila(&aux);
    stUsuario user;
    int x;
    FILE* buffer = fopen(archivo, "rb");
    if(buffer)
    {
        while((fread(&user, sizeof(stUsuario), 1, buffer)) > 0)
        {
            if(user.baja == 1)
            {
                sscanf(user.persona.dni, "%i", &x);
                apilar(&aux, x);
                baja = OrdenamientoPorSeleccion(aux);
            }
        }
        fclose(buffer);
    }
    return baja;
}

///FUNCION QUE ENCUENTRA EL DNI MENOR DE UNA PILA DESORDENADA
int EncontrarMenor(Pila *baja)
{
    Pila aux;
    inicpila(&aux);
    int menor=0;

    if (!pilavacia(baja))
    {
        menor = desapilar(baja);
    }

    while (!pilavacia (baja))
    {
        if (tope(baja) > menor)
        {
            apilar(&aux, desapilar(baja));
        }
        else
        {
            apilar(&aux, menor);
            menor = desapilar(baja);
        }
    }

    while (!pilavacia (&aux))
    {
        apilar(baja, desapilar(&aux));
    }
    return menor;
}

///FUNCION QUE ORDENA UNA PILA POR DNI
Pila OrdenamientoPorSeleccion(Pila desordenada)
{
    Pila dada;
    inicpila(&dada);
    int menor;

    while(!pilavacia(&desordenada))
    {
        menor = EncontrarMenor(&desordenada);
        apilar(&dada, menor);

    }
    return dada;
}

