#ifndef __DECLARACION_H__
#define __DECLARACION_H__

#ifndef _WINDOWS_H
#include <windows.h>
#endif // !_WINDOWS_H

#include "estructuras.h"
#include "definicion.h"

//////////////////////////////////////////////////////////////////////////

// Modulo General

//////////////////////////////////////////////////////////////////////////

BOOL esta_vacio(void* raiz);

//////////////////////////////////////////////////////////////////////////

// Módulos para la estructura <JugadorOca> tipo cola

//////////////////////////////////////////////////////////////////////////

void encolar_nodo(Jugador** entrada, Jugador** salida, Jugador** nuevo);

void desencolar_nodo(Jugador** entrada, Jugador** salida, Jugador** nuevo);

void borrar_nodo_jugador(Jugador** entrada, Jugador** salida, Jugador** nuevo);

//////////////////////////////////////////////////////////////////////////

// Módulos para la estructura <JuegoDeLaOca> tipo lista enlazada doble

//////////////////////////////////////////////////////////////////////////

void insertar_nodo_juego(Juego** lista, Juego** nuevo);

void crear_lista(Juego** lista, Juego** nuevo, int numero);

void copiar_la_lista(Juego* lista, Juego** aux, int numero);

void avanzar(Juego** lista);

Juego* avanzar_siguiente_casilla(Juego** lista, int numero);

void retroceder(Juego** lista);

Juego* retroceder_anterior_casilla(Juego** lista, int numero);

void desenlazar_nodo(Juego** lista, Juego** nuevo);

void borrar_nodo_juego(Juego** lista, Juego** nuevo);

//////////////////////////////////////////////////////////////////////////

// Módulos para verificar las reglas del juego <JuegoDeLaOca>

//////////////////////////////////////////////////////////////////////////

BOOL juego_de_la_oca_verificar(Juego* lista, int oca[], int numero);

int juego_de_la_oca_posicion(Juego* lista, int oca[], int numero);

//////////////////////////////////////////////////////////////////////////

// Modulo para avanzar turnos <JugadorOca>

//////////////////////////////////////////////////////////////////////////

void avanzar_turnos(Jugador** lista);

//////////////////////////////////////////////////////////////////////////

// Módulos para cargar y leer los ganadores de la partida Oca
// <ArbolesDeGanadores>

//////////////////////////////////////////////////////////////////////////

void insertar_nodo_arbol(Arbol** raiz, Jugador* jugador);

void recorrer_arbol(Arbol* raiz);

void borrar_arbol(Arbol* raiz);

//////////////////////////////////////////////////////////////////////////

// Modulo para cargar los datos del alumno

//////////////////////////////////////////////////////////////////////////

void cargar_datos_del_alumno(FILE** archivo, Alumno datos_del_alumno);

#endif // !__DECLARACION_H__