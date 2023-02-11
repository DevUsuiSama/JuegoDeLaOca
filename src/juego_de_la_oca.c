/*
 * Copyright (c) 2018 UsuiSama
 */
#include "../include/stdafx.h"

int main()
{
    int contador = 0,
        contador_de_alumnos = 0,
        contador_de_turnos = 0,
        informar_cantidad,
        ronda = 1,
        dado,
        mensaje = IDYES,
        cantidad_minima_de_alumnos = 1,
        cantidad_maxima_de_alumnos = 4,
        prenda_a_jugador = 0,
        casilla_anterior,
        oca[] = {5, 9, 14, 18, 23, 27, 32, 36, 41, 45, 50, 54, 59},
        puente[] = {6, 12},
        posadas = 19,
        pozo = 31,
        laberinto = 42,
        carcel = 56,
        dados[] = {26, 43},
        calavera = 58,
        prenda;

    char opcion = 'w';

    const int TURNO_PERDIDO = 150;

    BOOL turno = FALSE;
    Alumno alumno;
    Juego *lista = NULL,
          *nueva_lista = NULL,
          **aux_lista = NULL;
    Jugador *nuevo_jugador = NULL,
            *entrada = NULL,
            *salida = NULL,
            *aux_salida = NULL;
    Arbol *raiz = NULL;
    FILE *archivo;

    SetConsoleTitle(TITULO_DE_LA_APP);
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    );

    do
    {
        printf("------------------------------------------------------------\n");
        printf("///////////////////// MENU PRINCIPAL ///////////////////////\n");
        printf("------------------------------------------------------------\n\n");

        printf("Opciones Disponibles:\n");
        printf("\t> A: Cargar datos de los [Jugadores]\n");
        printf("\t> B: Iniciar [Juego de la Oca]\n");
        printf("\t> C: Eliminar datos de los [Jugadores]\n");
        printf("\t> E: Salir del [Juego de la Oca]\n\n");

        printf("------------------------------------------------------------\n");
        printf("Ingrese una de las opciones disponibles: ");

        fflush(stdin);
        scanf("%c", &opcion);

        switch (opcion_correcta(OPCION_1, opcion))
        {
        case 1:
            opcion = 'w';

            do
            {
                contador_de_alumnos++;

                limpiar_terminal();

                printf("------------------------------------------------------------\n");
                printf("////////////////////// CARGAR DATOS ////////////////////////\n");
                printf("------------------------------------------------------------\n\n");

                printf("> Ingresar Nombre: ");
                scanf("%s", alumno.nombre);

                printf("> Ingresar Apellido: ");
                scanf("%s", alumno.apellido);

                alumno.cantidad = contador_de_alumnos;

                cargar_datos_del_alumno(&archivo, alumno);

                printf("\n------------------------------------------------------------\n");
                printf("Para continuar presione - W: ");

                fflush(stdin);
                scanf("%c", &opcion);

                limpiar_terminal();
            } while (opcion_correcta(0, opcion));

            contador_de_alumnos = 0;
            opcion = 'w';
            break;
        case 2:
            contador_de_alumnos = 0;

            if ((archivo = fopen("db\\datos_de_los_alumnos.dat", "rb")) != NULL)
            {
                limpiar_terminal();

                crear_lista(&lista, &nueva_lista, 63);

                while (mensaje == IDYES)
                {
                    fread(&alumno, sizeof(Alumno), 1, archivo);
                    while (!feof(archivo))
                    {
                        if (
                            cantidad_minima_de_alumnos <= alumno.cantidad &&
                            alumno.cantidad <= cantidad_maxima_de_alumnos
                        )
                        {
                            printf("------------------------------------------------------------\n");
                            printf("/////////////////////////// JUEGO //////////////////////////\n");
                            printf("------------------------------------------------------------\n\n");

                            nuevo_jugador = (Jugador *)malloc(sizeof(Jugador));
                            if (!esta_vacio((void *)nuevo_jugador))
                            {
                                strcpy(nuevo_jugador->nombre, alumno.nombre);
                                strcpy(nuevo_jugador->apellido, alumno.apellido);

                                printf("> Alumno %s %s\n", nuevo_jugador->nombre, nuevo_jugador->apellido);

                                informar_cantidad = alumno.cantidad;

                                nuevo_jugador->numero_del_jugador = contador_de_alumnos + 1;
                                nuevo_jugador->prendas = FALSE;
                                nuevo_jugador->siguiente = NULL;

                                encolar_nodo(&entrada, &salida, &nuevo_jugador);
                            }
                            else
                                MessageBox(
                                    NULL,
                                    _T("No hay espacio suficiente en memoria"),
                                    TITULO_DE_LA_APP,
                                    MB_OK | MB_ICONERROR
                                );

                            printf("\n------------------------------------------------------------\n");
                            printf("Para continuar presione - cualquier tecla: ");

                            fflush(stdin);
                            getchar();

                            contador_de_alumnos++;
                            limpiar_terminal();
                        }
                        fread(&alumno, sizeof(Alumno), 1, archivo);
                    }

                    if (informar_cantidad == cantidad_maxima_de_alumnos)
                    {
                        cantidad_minima_de_alumnos = cantidad_maxima_de_alumnos + 1;
                        cantidad_maxima_de_alumnos += 4;
                    }
                    else
                    {
                        cantidad_maxima_de_alumnos = cantidad_maxima_de_alumnos - 2;

                        if (informar_cantidad == cantidad_maxima_de_alumnos)
                        {
                            MessageBox(
                                NULL,
                                _T("Solo quedan dos alumnos"),
                                TITULO_DE_LA_APP,
                                MB_OK | MB_ICONINFORMATION
                            );
                            cantidad_maxima_de_alumnos = 150;
                            cantidad_minima_de_alumnos = 140;
                        }
                        else
                        {
                            cantidad_maxima_de_alumnos = cantidad_maxima_de_alumnos - 1;

                            if (informar_cantidad == cantidad_maxima_de_alumnos)
                            {
                                MessageBox(
                                    NULL,
                                    _T("Solo quedan un alumno y jugara con la maestra"),
                                    TITULO_DE_LA_APP,
                                    MB_OK | MB_ICONINFORMATION
                                );

                                limpiar_terminal();

                                printf("------------------------------------------------------------\n");
                                printf("/////////////////////////// MENU ///////////////////////////\n");
                                printf("------------------------------------------------------------\n\n");

                                nuevo_jugador = (Jugador *)malloc(sizeof(Jugador));
                                if (!esta_vacio((void *)nuevo_jugador))
                                {
                                    strcpy(nuevo_jugador->nombre, "Alberta");
                                    strcpy(nuevo_jugador->apellido, "Perdida");

                                    printf("> Maestra %s %s\n", nuevo_jugador->nombre, nuevo_jugador->apellido);

                                    nuevo_jugador->numero_del_jugador = 2;
                                    nuevo_jugador->siguiente = NULL;

                                    encolar_nodo(&entrada, &salida, &nuevo_jugador);
                                }
                                else
                                    MessageBox(
                                        NULL,
                                        _T("No hay espacio suficiente en memoria"),
                                        TITULO_DE_LA_APP,
                                        MB_OK | MB_ICONERROR
                                    );

                                printf("\n------------------------------------------------------------\n");
                                printf("Para continuar presione - cualquier tecla: ");
                                fflush(stdin);
                                getchar();

                                limpiar_terminal();

                                cantidad_maxima_de_alumnos = 150;
                                cantidad_minima_de_alumnos = 140;
                            }
                        }
                    }

                    aux_lista = (Juego **)malloc(sizeof(Juego *) * contador_de_alumnos);

                    if (!esta_vacio((void *)aux_lista))
                        copiar_la_lista(lista, &aux_lista[0], contador_de_alumnos);
                    else
                        MessageBox(
                            NULL,
                            _T("No hay espacio suficiente en memoria"),
                            TITULO_DE_LA_APP,
                            MB_OK | MB_ICONERROR
                        );

                    aux_salida = salida;

                    opcion = 'w';

                    while (opcion_correcta(0, opcion) && !esta_vacio((void *)salida))
                    {
                        printf("Ronda: %d\n", ronda);
                        printf("------------------------------------------------------------\n");
                        printf("///////////////////// JUEGO DE LA OCA //////////////////////\n");
                        printf("------------------------------------------------------------\n\n");

                        if (
                            aux_salida->prendas == TURNO_PERDIDO ||
                            aux_salida->prendas == TRUE ||
                            aux_salida->numero_del_jugador == prenda_a_jugador
                        )
                        {
                            printf("-----------------------------\n");
                            printf("////////// AVISO ////////////\n");
                            printf("-----------------------------\n");
                            printf(
                                "> Mensaje: El jugador [%s] Nro [%d] ha perdido el turno y sigue el siguiente jugador\n",
                                aux_salida->nombre, aux_salida->numero_del_jugador
                            );
                            printf("-----------------------------\n");

                            if (aux_salida->prendas == TRUE)
                                aux_salida->prendas = FALSE;
                            if (aux_salida->prendas = TURNO_PERDIDO)
                            {
                                if (contador_de_turnos == 1)
                                {
                                    contador_de_turnos = 0;
                                    aux_salida->prendas = FALSE;
                                }
                                contador_de_turnos++;
                            }
                        }
                        else
                        {
                            printf("Turno del jugador: [%s] Nro [%d] \n\n", aux_salida->nombre, aux_salida->numero_del_jugador);
                            printf("Opciones: [ w ] - Tirar Dado: ");

                            fflush(stdin);
                            scanf("%c", &opcion);

                            if (opcion_correcta(0, opcion))
                            {
                                srand(time(NULL));
                                dado = 1 + rand() % 6;

                                casilla_anterior = aux_lista[contador]->numero_del_trayecto;

                                nueva_lista = avanzar_siguiente_casilla(
                                    &aux_lista[contador],
                                    (aux_lista[contador]->numero_del_trayecto + dado)
                                );

                                if (!esta_vacio((void *)nueva_lista->siguiente))
                                {
                                    printf("\n-----------------------------\n");
                                    printf("/////////// DADO ////////////\n");
                                    printf("-----------------------------\n");
                                    printf("El dado ha caido en el Nro [%d]\n", dado);
                                    printf("-----------------------------\n");

                                    printf("\n-----------------------------\n");
                                    printf("///// CASILLAS ACTUALES /////\n");
                                    printf("-----------------------------\n");

                                    printf(
                                        "El jugador [%s] Nro [%d] Estaba en la casilla [%d] y ha avanzado hasta la casilla [%d]\n",
                                        aux_salida->nombre,
                                        aux_salida->numero_del_jugador,
                                        casilla_anterior,
                                        nueva_lista->numero_del_trayecto
                                    );

                                    printf("-----------------------------\n");

                                    if (juego_de_la_oca_verificar(nueva_lista, oca, 13))
                                    {
                                        printf("\n-----------------------------\n");
                                        printf("/ LA SUERTE ESTA DE TU LADO /\n");
                                        printf("-----------------------------\n");

                                        printf(
                                            "Mensaje: El jugador [%s] Nro [%d] a caido en la casilla [%d] Oca\n",
                                            aux_salida->nombre,
                                            aux_salida->numero_del_jugador,
                                            nueva_lista->numero_del_trayecto
                                        );

                                        printf(
                                            "Mensaje: El jugador avanza hasta la siguiente casilla [%d] oca y mantiene el turno\n",
                                            avanzar_siguiente_casilla(
                                                &aux_lista[contador],
                                                oca[juego_de_la_oca_posicion(nueva_lista, oca, 13)]
                                            )->numero_del_trayecto
                                        );

                                        printf("-----------------------------\n");

                                        turno = TRUE;

                                        if (esta_vacio((void *)aux_lista[contador]->siguiente))
                                        {
                                            printf("\n------------------------------------------------------------\n");
                                            printf("Para continuar presione - cualquier tecla: ");
                                            fflush(stdin);
                                            getchar();
                                        }
                                    }
                                    else
                                        turno = FALSE;

                                    if (juego_de_la_oca_verificar(nueva_lista, puente, 2))
                                    {
                                        printf("\n-----------------------------\n");
                                        printf("/// MALA SUERTE CAMPEON /////\n");
                                        printf("-----------------------------\n");

                                        printf(
                                            "Mensaje: El jugador [%s] Nro [%d] a caido en la casilla [%d]\n",
                                            aux_salida->nombre,
                                            aux_salida->numero_del_jugador,
                                            nueva_lista->numero_del_trayecto
                                        );

                                        printf(
                                            "Mensaje: El jugador avanza hasta la siguiente casilla [%d] posadas y pierde el turno\n",
                                            avanzar_siguiente_casilla(
                                                &aux_lista[contador],
                                                posadas
                                            )->numero_del_trayecto
                                        );

                                        printf("-----------------------------\n");

                                        aux_salida->prendas = TRUE;
                                    }

                                    if (pozo == nueva_lista->numero_del_trayecto)
                                    {
                                        printf("\n-----------------------------\n");
                                        printf("/// MALA SUERTE CAMPEON /////\n");
                                        printf("-----------------------------\n");

                                        printf(
                                            "Mensaje: El jugador [%s] Nro [%d] a caido en la casilla [%d]\n",
                                            aux_salida->nombre,
                                            aux_salida->numero_del_jugador,
                                            nueva_lista->numero_del_trayecto);

                                        printf("Mensaje: El jugador pierde el turno hasta que otro jugador caiga en el pozo\n");

                                        printf("-----------------------------\n");

                                        prenda = aux_salida->numero_del_jugador;
                                    }

                                    if (laberinto == nueva_lista->numero_del_trayecto)
                                    {
                                        printf("\n-----------------------------\n");
                                        printf("/// MALA SUERTE CAMPEON /////\n");
                                        printf("-----------------------------\n");

                                        printf(
                                            "Mensaje: El jugador [%s] Nro [%d] a caido en la casilla [%d]\n",
                                            aux_salida->nombre,
                                            aux_salida->numero_del_jugador,
                                            nueva_lista->numero_del_trayecto);

                                        printf("Mensaje: El jugador pierde el turno dos veces hasta que otro jugador caiga en el pozo\n");

                                        printf("-----------------------------\n");

                                        turno = aux_salida->numero_del_jugador;
                                    }

                                    if (juego_de_la_oca_verificar(nueva_lista, dados, 2))
                                    {
                                        printf("\n-----------------------------\n");
                                        printf("/ LA SUERTE ESTA DE TU LADO /\n");
                                        printf("-----------------------------\n");

                                        printf(
                                            "Mensaje: El jugador [%s] Nro [%d] a caido en la casilla [%d] Oca\n",
                                            aux_salida->nombre,
                                            aux_salida->numero_del_jugador,
                                            nueva_lista->numero_del_trayecto
                                        );

                                        printf("Mensaje: El jugador avanza tanto como resulte en los dados\n");

                                        srand(time(NULL));
                                        dado = 1 + rand() % 6;

                                        casilla_anterior = aux_lista[contador]->numero_del_trayecto;

                                        nueva_lista = avanzar_siguiente_casilla(
                                            &aux_lista[contador],
                                            (dado + aux_lista[contador]->numero_del_trayecto)
                                        );

                                        printf("El dado ha caido en el Nro [%d]\n", dado);
                                        printf(
                                            "Mensaje: El jugador estaba en la casilla [%d] ahora esta en la casilla Nro [%d]\n",
                                            casilla_anterior, nueva_lista->numero_del_trayecto
                                        );

                                        printf("-----------------------------\n");
                                    }

                                    if (calavera == nueva_lista->numero_del_trayecto)
                                    {
                                        printf("\n-----------------------------\n");
                                        printf("/// MALA SUERTE CAMPEON /////\n");
                                        printf("-----------------------------\n");

                                        printf(
                                            "Mensaje: El jugador [%s] Nro [%d] a caido en la casilla [%d]\n",
                                            aux_salida->nombre,
                                            aux_salida->numero_del_jugador,
                                            nueva_lista->numero_del_trayecto
                                        );

                                        printf(
                                            "Mensaje: El jugador retrocede de la casilla [%d] hasta la casilla [%d]\n",
                                            nueva_lista->numero_del_trayecto,
                                            retroceder_anterior_casilla(&aux_lista[contador], 1)->numero_del_trayecto
                                        );

                                        printf("-----------------------------\n");
                                    }

                                    nueva_lista = NULL;
                                }
                                else
                                {
                                    printf("\n-----------------------------\n");
                                    printf("/////////// DADO ////////////\n");
                                    printf("-----------------------------\n");
                                    printf("El dado ha caido en el Nro [%d]\n", dado);
                                    printf("-----------------------------\n");

                                    printf("\n-----------------------------\n");
                                    printf("///// CASILLAS ACTUALES /////\n");
                                    printf("-----------------------------\n");

                                    printf(
                                        "El jugador [%s] Nro [%d] Estaba en la casilla [%d] y ha avanzado hasta la casilla [%d]\n",
                                        aux_salida->nombre,
                                        aux_salida->numero_del_jugador,
                                        casilla_anterior,
                                        aux_lista[contador]->numero_del_trayecto
                                    );

                                    printf("\n------------------------------------------------------------\n");
                                    printf("Para continuar presione - cualquier tecla: ");
                                    fflush(stdin);
                                    getchar();
                                }
                            }
                        }

                        if (esta_vacio((void *)aux_lista[contador]->siguiente))
                        {
                            limpiar_terminal();

                            printf("------------------------------------------------------------\n");
                            printf("/////////////////// FIN DE LA PARTIDA //////////////////////\n");
                            printf("------------------------------------------------------------\n\n");

                            printf(
                                "Mensaje: El jugador [%s] Nro [%d] ha llegado a la ultima casilla y ha ganado la partida\n",
                                aux_salida->nombre,
                                aux_salida->numero_del_jugador
                            );

                            printf("\n------------------------------------------------------------\n");
                            printf("Para continuar presione - cualquier tecla: ");
                            fflush(stdin);
                            getchar();

                            opcion = '*';
                        }
                        else
                        {
                            printf("\n------------------------------------------------------------\n");
                            printf("Para continuar presione - cualquier tecla: ");
                            fflush(stdin);
                            getchar();

                            limpiar_terminal();

                            if (turno == FALSE)
                            {
                                avanzar_turnos(&aux_salida);
                                contador++;

                                if (esta_vacio((void *)aux_salida))
                                    aux_salida = salida;
                                if (contador > (contador_de_alumnos - 1))
                                    contador = 0;
                            }
                        }
                    }

                    if (!esta_vacio((void *)salida))
                    {
                        insertar_nodo_arbol(&raiz, aux_salida);

                        mensaje = MessageBox(
                            NULL,
                            _T("Desea continuar jugando?"),
                            TITULO_DE_LA_APP,
                            MB_YESNO | MB_ICONQUESTION
                        );

                        switch (mensaje)
                        {
                        case IDYES:
                            ronda++;
                            contador = 0;
                            contador_de_alumnos = 0;

                            rewind(archivo);

                            borrar_la_lista(&aux_lista[0], contador_de_alumnos);
                            copiar_la_lista(lista, &aux_lista[0], contador_de_alumnos);

                            limpiar_terminal();

                            opcion = 'w';
                            break;
                        case IDNO:
                            fclose(archivo);
                            opcion = '*';
                            break;
                        }

                        borrar_nodo_jugador(&entrada, &salida, &nuevo_jugador);
                    }
                    else
                    {
                        fclose(archivo);
                        mensaje = IDNO;
                        MessageBox(
                            NULL,
                            _T("No hay mas datos que extraer del archivo"),
                            TITULO_DE_LA_APP,
                            MB_OK | MB_ICONWARNING
                        );
                        opcion = 'w';
                    }
                }

                if (!esta_vacio((void *)raiz))
                {
                    limpiar_terminal();
                    printf("------------------------------------------------------------\n");
                    printf("/////////////////// ARBOL DE GANADORES /////////////////////\n");
                    printf("------------------------------------------------------------\n\n");

                    printf("Los ganadores son: \n");
                    recorrer_arbol(raiz);

                    printf("\n------------------------------------------------------------\n");
                    printf("Para continuar presione - cualquier tecla: ");
                    fflush(stdin);
                    getchar();

                    opcion = 'w';

                    limpiar_terminal();
                }
            }
            else
            {
                MessageBox(
                    NULL,
                    _T("No se ha encontrado el archivo"),
                    TITULO_DE_LA_APP,
                    MB_OK | MB_ICONERROR
                );

                limpiar_terminal();

                opcion = 'w';
            }
            break;
        case 3:
            mensaje = MessageBox(
                NULL,
                _T("Borrar los datos almacenados de los jugadores?"),
                TITULO_DE_LA_APP,
                MB_YESNO | MB_ICONQUESTION
            );
            switch (mensaje)
            {
            case IDYES:
                if (esta_vacio((void *)remove("db\\datos_de_los_alumnos.dat")))
                    MessageBox(
                        NULL,
                        _T("Archivo eliminado correctamente"),
                        TITULO_DE_LA_APP,
                        MB_OK | MB_ICONINFORMATION
                    );
                else
                    MessageBox(
                        NULL,
                        _T("El archivo no pudo ser eliminado"),
                        TITULO_DE_LA_APP,
                        MB_OK | MB_ICONINFORMATION
                    );
                opcion = 'w';
                break;
            case IDNO:
                opcion = 'w';
                break;
            }

            limpiar_terminal();
            break;
        case 4:
            limpiar_terminal();

            printf("------------------------------------------------------------\n");
            printf("////////////////////////// SALIDA //////////////////////////\n");
            printf("------------------------------------------------------------\n\n");

            printf("Desea salir del juego?:\n");
            printf("\t> Y: Salir del juego\n");
            printf("\t> N: Te arrepientes\n\n");

            printf("------------------------------------------------------------\n");
            printf("Ingrese una de las opciones disponibles: ");

            fflush(stdin);
            scanf("%c", &opcion);

            opcion = (opcion == 'y' || opcion == 'Y') ? '*' : 'w';

            limpiar_terminal();
            break;
        default:
            opcion = 'w';
            limpiar_terminal();
            break;
        }
    } while (opcion_correcta(0, opcion));

    aux_salida = NULL;

    borrar_la_lista(&aux_lista[0], contador_de_alumnos);
    borrar_nodo_juego(&lista, &nueva_lista);
    borrar_arbol(raiz);

    raiz = NULL;

    return EXIT_SUCCESS;
}