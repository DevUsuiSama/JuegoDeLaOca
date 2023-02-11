#ifndef __DEFINICION_H__
#define __DEFINICION_H__

#ifndef _STDIO_H
#include <stdio.h>
#endif // !_STDIO_H
#ifndef _STDLIB_H
#include <stdlib.h>
#endif // !_STDLIB_H
#ifndef _WINDOWS_H
#include <windows.h>
#endif // !_WINDOWS_H
#ifndef _TCHAR_H_
#include <tchar.h>
#endif // !_TCHAR_H_
#ifndef __DECLARACION_H__
#include "declaracion.h"
#endif // !__DECLARACION_H__

#include <direct.h>

//////////////////////////////////////////////////////////////////////////

// Modulo General

//////////////////////////////////////////////////////////////////////////

BOOL esta_vacio(void* nodo)
{
    return (nodo == NULL);
}

//////////////////////////////////////////////////////////////////////////

// Módulos para la estructura <JugadorOca> tipo cola

//////////////////////////////////////////////////////////////////////////

void encolar_nodo(Jugador **entrada, Jugador **salida, Jugador **nuevo)
{
    if (esta_vacio((void *)*entrada))
    {
        *entrada = *nuevo;
        *salida = *nuevo;
    }
    else
    {
        (*entrada)->siguiente = *nuevo;
        *entrada = *nuevo;
    }
    *nuevo = NULL;
}

void desencolar_nodo(Jugador **entrada, Jugador **salida, Jugador **nuevo)
{
    *nuevo = *salida;
    if (esta_vacio((void *)(*salida)->siguiente))
        *entrada = NULL;
    *salida = (*salida)->siguiente;
    (*nuevo)->siguiente = NULL;
}

void borrar_nodo_jugador(Jugador **entrada, Jugador **salida, Jugador **nuevo)
{
    while (!esta_vacio((void *)*salida))
    {
        desencolar_nodo(&(*entrada), &(*salida), &(*nuevo));
        free(*nuevo);
    }
}

//////////////////////////////////////////////////////////////////////////

// Módulos para la estructura <JuegoDeLaOca> tipo lista enlazada doble

//////////////////////////////////////////////////////////////////////////

void insertar_nodo_juego(Juego **lista, Juego **nuevo)
{
    if (esta_vacio((void *)*lista))
        *lista = *nuevo;
    else
    {
        (*nuevo)->siguiente = *lista;
        (*lista)->anterior = *nuevo;
        *lista = *nuevo;
    }
    *nuevo = NULL;
}

void crear_lista(Juego **lista, Juego **nuevo, int numero)
{
    for (int i = numero; i >= 0; i--)
    {
        *nuevo = (Juego *)malloc(sizeof(Juego));
        if (!esta_vacio((void *)*nuevo))
        {
            (*nuevo)->numero_del_trayecto = i;
            (*nuevo)->siguiente = NULL;
            (*nuevo)->anterior = NULL;
            insertar_nodo_juego(&(*lista), &(*nuevo));
        }
        else
            MessageBox(
                NULL,
                _T("No hay espacio suficiente en memoria"),
                TITULO_DE_LA_APP,
                MB_OK | MB_ICONERROR
            );
    }
}

void copiar_la_lista(Juego* lista, Juego** aux, int numero)
{
    for (int i = 0; i < numero; i++)
        *(aux + i) = lista;
}

void borrar_la_lista(Juego** lista, int numero)
{
    for (int i = 0; i < numero; i++)
        if (!esta_vacio((void *)*(lista + i)))
            *(lista + i) = NULL;
}

void avanzar(Juego **lista)
{
    if (!esta_vacio((void *)*lista))
        *lista = (*lista)->siguiente;
}

Juego *avanzar_siguiente_casilla(Juego **lista, int numero)
{
    while ((*lista)->siguiente != NULL && (*lista)->numero_del_trayecto < numero)
        avanzar(&(*lista));
    return *lista;
}

void retroceder(Juego **lista)
{
    if (!esta_vacio((void *)*lista))
        *lista = (*lista)->anterior;
}

Juego *retroceder_anterior_casilla(Juego **lista, int numero)
{
    while ((*lista)->anterior != NULL && (*lista)->numero_del_trayecto > numero)
        retroceder(&(*lista));
    return *lista;
}

void desenlazar_nodo(Juego **lista, Juego **nuevo)
{
    *nuevo = *lista;
    *lista = (*lista)->siguiente;
    if (!esta_vacio((void *)*lista))
        (*lista)->anterior = NULL;
    (*nuevo)->siguiente = NULL;
}

void borrar_nodo_juego(Juego **lista, Juego **nuevo)
{
    while (!esta_vacio((void *)*lista))
    {
        desenlazar_nodo(&(*lista), &(*nuevo));
        free(*nuevo);
    }
}

//////////////////////////////////////////////////////////////////////////

// Módulos para verificar las reglas del juego <JuegoDeLaOca>

//////////////////////////////////////////////////////////////////////////

BOOL juego_de_la_oca_verificar(Juego *lista, int oca[], int numero)
{
    for (int i = 0; i < numero; i++)
        if (lista->numero_del_trayecto == oca[i])
            return TRUE;
    return FALSE;
}

int juego_de_la_oca_posicion(Juego *lista, int oca[], int numero)
{
    for (int i = 0; i < numero; i++)
        if (lista->numero_del_trayecto == oca[i])
            return (i++);
}

//////////////////////////////////////////////////////////////////////////

// Modulo para avanzar turnos <JugadorOca>

//////////////////////////////////////////////////////////////////////////

void avanzar_turnos(Jugador **lista)
{
    if (!esta_vacio((void *)*lista))
        *lista = (*lista)->siguiente;
}

//////////////////////////////////////////////////////////////////////////

// Módulos para cargar y leer los ganadores de la partida Oca
// <ArbolesDeGanadores>

//////////////////////////////////////////////////////////////////////////

void insertar_nodo_arbol(Arbol **raiz, Jugador *jugador)
{
    if (esta_vacio((void *)*raiz))
    {
        *raiz = (Arbol *)malloc(sizeof(Arbol));
        if (!esta_vacio((void *)*raiz))
        {
            strcpy((*raiz)->nombre, jugador->nombre);
            strcpy((*raiz)->apellido, jugador->apellido);
            (*raiz)->izquierda = NULL;
            (*raiz)->derecha = NULL;
        }
        else
            MessageBox(
                NULL,
                _T("No hay espacio suficiente en memoria"),
                TITULO_DE_LA_APP,
                MB_OK | MB_ICONERROR
            );
    }
    else
    {
        if (strcmp(jugador->apellido, (*raiz)->apellido) < 0)
            insertar_nodo_arbol(&((*raiz)->izquierda), jugador);
        else if (strcmp(jugador->apellido, (*raiz)->apellido) > 0)
            insertar_nodo_arbol(&((*raiz)->derecha), jugador);
    }
}

void recorrer_arbol(Arbol *raiz)
{
    if (!esta_vacio((void *)raiz))
    {
        printf("\t> %s %s\n", raiz->nombre, raiz->apellido);
        recorrer_arbol(raiz->izquierda);
        recorrer_arbol(raiz->derecha);
    }
}

void borrar_arbol(Arbol *raiz)
{
    if (!esta_vacio((void *)raiz))
    {
        borrar_arbol(raiz->izquierda);
        borrar_arbol(raiz->derecha);
        free(raiz);
    }
}

//////////////////////////////////////////////////////////////////////////

// Modulo para cargar los datos del alumno

//////////////////////////////////////////////////////////////////////////

void cargar_datos_del_alumno(FILE** archivo, Alumno datos_del_alumno)
{
    mkdir("db");
    if ((*archivo = fopen("db\\datos_de_los_alumnos.dat", "ab")) != NULL)
    {
        fwrite(&datos_del_alumno, sizeof(Alumno), 1, *archivo);
        fclose(*archivo);
    }
}

#endif // !__DEFINICION_H__