#include "usuario.h"
#include <ctype.h>
#include "pila.h"
#include <time.h>

///Funciones

///FUNCION QUE CARGA UN USUARIO, PIDIENDO DNI, NOMBRE, APELLIDO Y CONTRASENIA, RETORNA EL USUARIO CARGADO
stUsuario cargarUnUsuario()
{
    stUsuario usuario;

    int flag=0;
    char nombreaux[MAX];
    char apellidoaux[MAX];
    char contraseniaaux[MAX];
    while (flag==0)
    {
        printf("\n\n\t\t\t\tIngrese su nombre: ");
        fflush(stdin);
        gets(nombreaux);
        flag= ValidacionNombreYApellidoUsuario(nombreaux);

        if(flag==0)
        {
            printf("Nombre incorrecto, (solo letras)\n");
        }
        else
        {
            flag=1;
            strcpy(usuario.persona.nombre, nombreaux);
        }
    }

    flag=0;

    while (flag==0)
    {
        printf("\n\n\t\t\t\tIngrese su apellido: ");
        fflush(stdin);
        gets(apellidoaux);

        flag= ValidacionNombreYApellidoUsuario(apellidoaux);

        if(flag==0)
        {
            printf("Apellido incorrecto, (solo letras)\n");
        }
        else
        {
            flag=1;
            strcpy(usuario.persona.apellido, apellidoaux);
        }
    }
    flag=0;
    while(flag==0)
    {

        printf("\n\n\t\t\t\tIngrese una contrase%ca: ", 164);
        fflush(stdin);
        gets(contraseniaaux);
        flag= ValidacionContraseniaUsuario(contraseniaaux);

        if(flag==0)
        {
            printf("Contrase%ca incorrecta, (4 a 15 digitos )\n", 164);
        }
        else
        {
            flag=1;
            strcpy(usuario.contrasenia, contraseniaaux);
        }
    }
    usuario.sueldo.aporteJubilatorio = 0;
    usuario.sueldo.aporteSindical = 0;
    usuario.sueldo.horasExtras = 0;
    usuario.sueldo.horasTrabajadas = 0;
    usuario.sueldo.montoBruto = 0;
    usuario.sueldo.montoFinal = 0;
    usuario.sueldo.obraSocial = 0;
    strcpy(usuario.sueldo.puestoDeTrabajo, "N/A");
    usuario.sueldo.seguroDeVida = 0;
    usuario.antiguedad = cargarAntiguedad();

    usuario.tipo = 2;
    usuario.baja = 0;

    return usuario;
}

///FUNCION QUE CUENTA LA CANTIDAD DE REGISTROS QUE HAY EN EL ARCHIVO
int contarRegistrosEnArchivo (char archivo[])
{
    FILE* buffer =fopen(archivo, "rb");
    long int cantidad;

    if(buffer)
    {
        fseek(buffer,0, SEEK_END);
        cantidad = ftell(buffer) / sizeof(stUsuario);
        cantidad = cantidad - 1;

        fclose(buffer);
    }
    return cantidad;
}

///FUNCION QUE BUSCA A UN USUARIO POR DNI
int buscarUsuario(char dni[MAX])
{
    stUsuario usuario;
    int flag=0;
    FILE* buffer = fopen (ARCHIVOUSUARIOS, "rb");

    if(buffer)
    {
        while((flag == 0) && (fread(&usuario, sizeof(stUsuario), 1, buffer)> 0) )
        {
            if(strcmp(dni, usuario.persona.dni) == 0 && usuario.baja == 0)
            {
                flag = 1;
            }
        }
        fclose(buffer);
    }
    return flag;
}

///FUNCION QUE BUSCA A UN USUARIO EN EL ARCHIVO POR DNI Y CONTRASENIA PARA INICIAR SESION EN UN MENU
stUsuario buscarUsuarioLogin(char dni[MAX], char pass[MAX])
{
    stUsuario usuario;
    stUsuario encontrado;
    encontrado.tipo=-1;
    int flag=0;
    FILE* buffer = fopen (ARCHIVOUSUARIOS, "rb");

    if(buffer)
    {
        while((flag == 0) && (fread(&usuario, sizeof(stUsuario), 1, buffer)> 0))
        {
            if((strcmpi(dni, usuario.persona.dni) == 0) && (strcmpi(pass, usuario.contrasenia) == 0) && (usuario.baja == 0))
            {
                encontrado=usuario;
                flag = 1;
            }

        }
        fclose(buffer);
    }

    return encontrado;
}

///FUNCION QUE MUESTRA LOS REGISTROS DE UN ARCHIVO, NO MOSTRARA EL SUELDO DE EMPLEADOS DADOS DE BAJA
void mostrarArchivoUsuarios(char archivo[])
{
    FILE* buffer= fopen(ARCHIVOUSUARIOS,"rb");
    stUsuario aux;

    if(buffer)
    {
        while((fread(&aux,sizeof(stUsuario),1, buffer))>0)
        {
            mostrarUsuario(aux);
            if(aux.tipo==2 && aux.baja==0)
            {
                mostrarSueldoEmpleado(aux.sueldo);
            }
        }
        fclose(buffer);
    }
}

///FUNCION  QUE MUESTRA LOS DATOS DE UN USUARIO
void mostrarUsuario(stUsuario aux)
{
    if(aux.tipo == 2)
    {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("\tNombre:                     %s\n", aux.persona.nombre);
        printf("\tApellido:                   %s\n", aux.persona.apellido);
        printf("\tDNI:                        %s\n", aux.persona.dni);
        printf("\tFecha de registro:          %02d/%02d/%04d\n", aux.antiguedad.dia, aux.antiguedad.mes, aux.antiguedad.anio);
    }
}

///FUNCION QUE VALIDA NOMBRE Y APELLIDO PARA LA CARGA DE UN USUARIO
int ValidacionNombreYApellidoUsuario(char palabra[])
{
    for(int i = 0 ; i<strlen(palabra); i++)
    {
        if((isdigit(palabra[i])))
        {
            return 0;
        }
    }

    return 1;
}

///FUNCION QUE VALIDA EL DNI PARA LA CARGA DE UN USUARIO
int ValidacionDniUsuario(char palabra[])
{
    for(int i=0 ; i<(strlen(palabra)); i++)
    {
        if((isalpha(palabra[i])) || strlen(palabra)<7 || strlen(palabra)>8)
        {
            return 0;
        }
    }

    return 1;
}

///FUNCION QUE VALIDA LA CONTRASENIA PARA LA CARGA DE UN USUARIO
int ValidacionContraseniaUsuario(char palabra[])
{
    for(int i = 0 ; i<strlen(palabra); i++)
    {
        if( strlen(palabra) < 4 || strlen(palabra) > 15)
        {
            return 0;
        }
    }

    return 1;

}

///FUNCION QUE DA DE BAJA, ALTA O OTORGA ADMIN A UN USUARIO DESDE EL MENU ADMIN
void modificarEmpleado (char archivo[], char dni[])
{
    int eleccion;
    stUsuario empleado;
    int flag=0;
    FILE * buffer = fopen (archivo, "r+b" );
    if (buffer)
    {
        while (flag==0 && (fread(&empleado,sizeof(stUsuario),1, buffer)) > 0)
        {
            if (strcmp(empleado.persona.dni, dni)==0)
            {
                flag=1;
            }
        }
        int flag2 = 0;
        system("cls");
        while(flag2 == 0)
        {
            system("cls");
            mostrarUsuario(empleado);
            printf("\n\t\t\t\tQue quiere modificar?\n");
            printf("\n\t\t\t\t1. Si quiere darlo de baja\n");
            printf("\n\t\t\t\t2. si quiere darlo de alta\n");
            printf("\n\t\t\t\t3. si quiere asignarlo como admin\n");
            printf("\n\t\t\t\t4. si quiere retirarle los permisos de admin\n");
            printf("\n\t\t\t\t5. salir\n");
            scanf("%d", &eleccion);
            if(eleccion==1)
            {
                if(empleado.baja == 0)
                {
                    printf("\n\t\t\tSe dio de baja a %s %s\n", empleado.persona.nombre, empleado.persona.apellido);
                    empleado.baja = 1;
                    flag2 = 1;
                }
                else
                {
                    printf("\n\t\t\tEl usuario ya se encuentra dado de baja\n");
                    flag2 = 1;
                }
            }
            else if(eleccion==2)
            {
                if(empleado.baja == 1)
                {
                    printf("\n\t\t\tSe dio de alta a %s %s\n", empleado.persona.nombre, empleado.persona.apellido);
                    empleado.baja = 0;
                    flag2 = 1;

                }
                else
                {
                    printf("\n\t\t\tEl usuario ya se encuentra dado de alta\n");
                    flag2 = 1;
                }
            }
            else if (eleccion==3)
            {
                if(empleado.tipo == 1)
                {
                    printf("\n\t\t\tEl usuario ya se encuentra con permisos de admin\n");
                    flag2 = 1;
                }
                else
                {
                    printf("\n\t\t\tSe le otorgo admin a %s %s\n", empleado.persona.nombre, empleado.persona.apellido);
                    empleado.tipo = 1;
                    flag2 = 1;
                }
            }
            else if (eleccion == 4)
            {
                if(empleado.tipo == 2)
                {
                    printf("\n\t\t\tEl usuario ya se encuentra sin permisos de admin\n");
                    flag2 = 1;
                }
                else
                {
                    empleado.tipo = 2;
                    printf("\n\t\t\tSe le removieron los permisos de admin al usuario\n");
                }
            }
            else if (eleccion == 5)
            {
                flag2 = 1;
            }
            else
            {
                printf("\n\t\t\t\t\tla opcion es incorrecta\n");
                system("cls");
            }
        }
        fseek(buffer,sizeof(stUsuario)*(-1), SEEK_CUR);
        fwrite(&empleado,sizeof(stUsuario),1, buffer);
        fclose(buffer);
    }
}

///FUNCION QUE RETORNA UN USUARIO POR DNI BUSCADO
stUsuario retornarUsuarioPorDNI(char DNI[])
{
    stUsuario usuario;
    int flag=0;
    FILE* buffer = fopen (ARCHIVOUSUARIOS, "rb");

    if(buffer)
    {
        while((flag == 0) && (fread(&usuario, sizeof(stUsuario), 1, buffer)> 0) )
        {
            if(strcmp(DNI, usuario.persona.dni) == 0 && usuario.baja == 0)
            {
                flag = 1;
            }
        }
        fclose(buffer);
    }
    return usuario;
}

///FUNCION QUE CARGA LOS CAMPOS DE SUELDO DE UN USUARIO
void cargarSueldoAlUsuario(char archivo[], char archivo2[], stUsuario user)
{
    stSueldo aux;
    stUsuario usuarioaux;
    aux= modificarSueldoEmpleado (archivo, user.persona.dni);
    user.sueldo=aux;
    int flag = 0;

    FILE*buffer=fopen(archivo, "r+b");
    FILE*buffer2=fopen(archivo2, "ab");
    if(buffer && buffer2)
    {
        while(!flag && (fread(&usuarioaux,sizeof(stUsuario), 1, buffer))>0)
        {
            if(strcmp(user.persona.dni, usuarioaux.persona.dni)==0)
            {
                fseek(buffer,(sizeof(stUsuario)*(-1)), 1);
                fwrite(&user, sizeof(stUsuario), 1, buffer);
                flag =1;
            }
        }
        fwrite(&user, sizeof(stUsuario), 1, buffer2);
        if(flag == 0)
        {
            printf("Error al sobreescribir el archivo");
        }
        fclose(buffer);
        fclose(buffer2);
    }
}

///ORDENA EL ARREGLO POR NOMBRE
void insertarEmpleadoPorNombre (stUsuario arregloEmpleado[], int i, stUsuario empleado)
{
    while(i>=0 && stricmp(empleado.persona.nombre, arregloEmpleado[i].persona.nombre) < 0)
    {
        arregloEmpleado[i+1] = arregloEmpleado[i];
        i--;
    }
    arregloEmpleado[i+1] = empleado;
}

///ORDENA EL ARREGLO POR NOMBRE
void ordenamientoPorNombre (stUsuario empleado[], int validos)
{
    int i = 0;
    while (i<validos-1)
    {
        insertarEmpleadoPorNombre(empleado, i, empleado[i+1]);
        i++;
    }
}

///ORDENA EL ARREGLO POR PUESTO DE TRABAJO
void insertarEmpleadoPorPuestoDeTrabajo (stUsuario arregloEmpleado[], int i, stUsuario empleado)
{
    while(i>=0 && stricmp(empleado.sueldo.puestoDeTrabajo, arregloEmpleado[i].sueldo.puestoDeTrabajo) < 0)
    {
        arregloEmpleado[i+1] = arregloEmpleado[i];
        i--;
    }
    arregloEmpleado[i+1] = empleado;
}

///ORDENA EL ARREGLO POR PUESTO DE TRABAJO
void ordenamientoPorPuestoDeTrabajo (stUsuario empleado[], int validos)
{
    int i = 0;
    while (i<validos-1)
    {
        insertarEmpleadoPorPuestoDeTrabajo(empleado, i, empleado[i+1]);
        i++;
    }
}

///ORDENA EL ARREGLO POR DNI
void insertarEmpleadoPorDNI (stUsuario arregloEmpleado[], int i, stUsuario empleado)
{
    while(i>=0 && stricmp(empleado.persona.dni, arregloEmpleado[i].persona.dni) < 0)
    {
        arregloEmpleado[i+1] = arregloEmpleado[i];
        i--;
    }
    arregloEmpleado[i+1] = empleado;
}

///ORDENA EL ARREGLO POR DNI
void ordenamientoPorDNI (stUsuario empleado[], int validos)
{
    int i = 0;
    while (i<validos-1)
    {
        insertarEmpleadoPorDNI(empleado, i, empleado[i+1]);
        i++;
    }
}

///MUESTRA EL ARREGLO DE EMPLEADOS
void mostrarArregloEmpleados(stUsuario arreglo[], int validos)
{
   int i = 0;
   while(i<validos)
   {
       if(arreglo[i].tipo == 2)
    {
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("\tNombre:                     %s\n", arreglo[i].persona.nombre);
        printf("\tApellido:                   %s\n", arreglo[i].persona.apellido);
        printf("\tDNI:                        %s\n", arreglo[i].persona.dni);
        printf("\tFecha de registro:          %02d/%02d/%04d\n", arreglo[i].antiguedad.dia, arreglo[i].antiguedad.mes, arreglo[i].antiguedad.anio);
        printf("\tPuesto de trabajo:          %s\n", arreglo[i].sueldo.puestoDeTrabajo);
    }
    i++;
   }
}

///PASA LAS ESTRUCTURAS DEL ARCHIVO A UN ARREGLO
int pasarDelArchivoAlArreglo(stUsuario arreglo[], char nombrearchivo[])
{
    stUsuario aux;
    int i=0;
    FILE*buffer=fopen(nombrearchivo,"rb");
    if(buffer)
    {
        while(fread(&aux, sizeof(stUsuario), 1, buffer)>0)
        {
            arreglo[i]=aux;
            i++;
        }
        fclose(buffer);
    }
    return i;
}

void modificarDatosEmpleado(char archivo[], char dni[])
{
    int eleccion;
    stUsuario empleado;
    int flag=0;
    FILE * buffer = fopen (archivo, "r+b" );
    if (buffer)
    {
        while (flag==0 && (fread(&empleado,sizeof(stUsuario),1, buffer)) > 0)
        {
            if (strcmp(empleado.persona.dni, dni)==0)
            {
                flag=1;
            }
        }
        int flag2 = 0;
        system("cls");
        while(flag2 == 0)
        {
            system("cls");
            mostrarUsuario(empleado);
            printf("\n\t\t\t\tQue datos desea modificar?\n");
            printf("\n\t\t\t\t1. Si quiere cambiar su nombre\n");
            printf("\n\t\t\t\t2. si quiere cambiar su apellido\n");
            printf("\n\t\t\t\t3. si quiere cambiar su contrase%ca\n", 164);
            printf("\n\t\t\t\t4. si quiere darse de baja en el sistema\n");
            printf("\n\t\t\t\t5. salir\n");
            scanf("%d", &eleccion);
            if(eleccion==1)
            {
                printf("\n\t\t\t\tCambio de nombre\n");
                printf("\n\t\t\t\tIngrese su nuevo nombre :");
                scanf("\n\t\t\t\t%s", empleado.persona.nombre);
                printf("\n\t\t\t\tSe cambio con exito su nombre\n");
                system("pause");
            }
            else if(eleccion==2)
            {
                printf("\n\t\t\t\tCambio de apellido\n");
                printf("\n\t\t\t\tIngrese su nuevo apellido:");
                scanf("\n\t\t\t\t%s", empleado.persona.apellido);
                printf("\n\t\t\t\tSe cambio con exito su apellido\n");
                system("pause");
            }
            else if (eleccion==3)
            {
                printf("\n\t\t\t\tCambio de contrasenia\n");
                printf("\n\t\t\t\tIngrese su nueva contrasenia:");
                scanf("\n\t\t\t\t%s", empleado.contrasenia);
                printf("\n\t\t\t\tSe cambio con exito la contrasenia\n");
                system("pause");
            }
            else if (eleccion == 4)
            {
                printf("\n\t\t\t\tSe dio de baja con exito\n");
                empleado.baja = 1;
                system("pause");
            }
            else if (eleccion == 5)
            {
                flag2 = 1;
            }
            else
            {
                printf("\n\t\t\t\t\tla opcion es incorrecta\n");
                system("cls");
            }
        }
        fseek(buffer,sizeof(stUsuario)*(-1), SEEK_CUR);
        fwrite(&empleado,sizeof(stUsuario),1, buffer);
        fclose(buffer);
    }
}


void mostrarHistorialSueldo (char archivo[], char dni[])
{
    FILE* buffer= fopen(ARCHIVOHISTORIAL,"rb");
    stUsuario aux;

    if(buffer)
    {
        while((fread(&aux,sizeof(stUsuario),1, buffer))>0)
        {
            if((strcmp(aux.persona.dni, dni)) == 0)
            {
                mostrarSueldoEmpleado(aux.sueldo);
            }
        }
        fclose(buffer);
    }
}


///FUNCION QUE CARGA UNA MATRIZ DE ANTIGUEDAD
void cargarMatrizDeFechaDeRegistro(int dimF, int dimC, int MatrizUsuarios[dimF][dimC], char archivo[])
//cargar matriz de usuario. leer todos los usuarios y mostrar de cada uno: dni, dia, mes y año de registro (antiguedad)
{
    FILE*buffer=fopen(archivo, "rb");
    stUsuario user;
    int f=0;
    int c=0;
    int auxiliar;
    if(buffer)
    {

        for(f=0; f<dimF; f++)
        {
            if(fread(&user, sizeof(stUsuario), 1, buffer)>0)
            {
                sscanf(user.persona.dni, "%i", &auxiliar);
                MatrizUsuarios[f][c++]= auxiliar;
                MatrizUsuarios[f][c++]= user.antiguedad.dia;
                MatrizUsuarios[f][c++]= user.antiguedad.mes;
                MatrizUsuarios[f][c++]= user.antiguedad.anio;
            }
            c=0;
        }
        fclose(buffer);

    }
}

///FUNCION QUE MUESTRA MATRIZ DE ANTIGUEDAD
void mostrarMatrizAntiguedad(int dimF, int dimC, int MatrizUsuarios[dimF][dimC])
{
    int f=0;
    int c=0;
    for(f=0; f<dimF; f++)
    {
        for(c=0; c<dimC; c++)
        {
            printf("[  %i  ]", MatrizUsuarios[f][c]);
        }
        printf("\n");
    }
}
int CargarArrregloDeBeneficiosSindicales(char M[][MAX], int dimF)
{
    int f=0;
    while (f<dimF)
    {
        strcpy(M[f++], "1. ASESORAMEINTO SOCIAL");
        strcpy(M[f++],"2. DESCUENTO EN FARMACIAS");
        strcpy(M[f++], "3. HOTELES A DISPOSICION");
        strcpy(M[f++], "4. COLONIA PARA AFILIADOS");
        strcpy(M[f++],"5. COBERTURA MEDICA");
    }
    return f;
}

void MostrarArregloStrings (char M[][MAX], int validos)
{
    for(int i=0; i<validos; i++)
    {
        printf("%s \n", M[i]);
    }
}
