#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__

typedef struct JugadorOca
{
    int numero_del_jugador;
    int prendas;
    char nombre[30];
    char apellido[30];
    struct JugadorOca* siguiente;
} Jugador;

typedef struct DatosAlumno
{
    char nombre[30];
    char apellido[30];
    int cantidad;
} Alumno;

typedef struct JuegoDeLaOca
{
    int numero_del_trayecto;
    struct JuegoDeLaOca *siguiente;
    struct JuegoDeLaOca *anterior;
} Juego;

typedef struct ArbolDeGanadores
{
    char nombre[30];
    char apellido[30];
    struct ArbolDeGanadores* derecha;
    struct ArbolDeGanadores* izquierda;
} Arbol;

#endif // !__ESTRUCTURAS_H__