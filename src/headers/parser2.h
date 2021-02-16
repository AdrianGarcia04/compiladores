#pragma once
#include "tokens.h"
#include "tablasimbolos.h"
#include "simbolo.h"

/**
 * Función para prueba y empate del No-terminal A
 */
void A();

/**
 * Función para prueba y empate del No-terminal B
 */
void B();

/**
 * Función para prueba y empate del No-terminal C
 */
simbolo C();

/**
 * Función para prueba y empate del No-terminal D
 */
simbolo D();

/**
 * Función para prueba y empate del No-terminal E
 */
simbolo E();

/**
 * Función para prueba y empate del No-terminal F
 */
simbolo F();

/**
 * Función para prueba y empate del No-terminal FP (F prima)
 */
simbolo FP();

/**
 * Función para prueba y empate del No-terminal G
 */
simbolo G();

/**
 * Función para prueba y empate del No-terminal H
 */
simbolo H();

/**
 * Función para prueba y empate del No-terminal I
 */
simbolo I();

/**
 * Función para prueba y empate del No-terminal IP (I prima)
 */
simbolo IP();

/**
 * Función para prueba y empate del No-terminal J
 */
simbolo J();

/**
 * Función para prueba y empate del No-terminal K
 */
simbolo K();

/**
 * Función para prueba y empate del No-terminal KP (K prima)
 */
simbolo KP();

/**
 * Función para prueba y empate del No-terminal L
 */
simbolo L();

/**
 * Función para prueba y empate del No-terminal LP (L prima)
 */
simbolo LP();

/**
 * Función para prueba y empate del No-terminal LPP (L bi-prima)
 */
simbolo LPP();

/**
 * Función para prueba y empate del No-terminal M
 */
simbolo M();

/**
 * Función para prueba y empate del No-terminal N
 */
simbolo N();

/**
 * Función para prueba y empate del No-terminal O
 */
simbolo O();

/**
 * Función para prueba y empate del No-terminal P
 */
simbolo P();

/**
 * Función para prueba y empate del No-terminal Q
 */
simbolo Q();

/**
 * Función para prueba y empate del No-terminal QP (Q prima)
 */
simbolo QP();

/**
 * Función para prueba y empate del No-terminal R
 */
simbolo R();

/**
 * Función para prueba y empate del No-terminal RP (R prima)
 */
simbolo RP();

/**
 * Función para prueba y empate del No-terminal S
 */
simbolo S();

/**
 * Función para prueba y empate del No-terminal SP (S prima)
 */
simbolo SP();

/**
 * Función para prueba y empate del No-terminal T
 */
simbolo T();

/**
 * Función para prueba y empate del No-terminal TP (T prima)
 */
simbolo TP();

/**
 * Función para prueba y empate del No-terminal U
 */
simbolo U();

/**
 * Función para prueba y empate del No-terminal UP (U prima)
 */
simbolo UP();

/**
 * Función para prueba y empate del No-terminal V
 */
simbolo V();

/**
 * Función para prueba y empate del No-terminal VP (V prima)
 */
simbolo VP();

/**
 * Función para prueba y empate del No-terminal W
 */
simbolo W();

/**
 * Función para prueba y empate del No-terminal X
 */
simbolo X();

/**
 * Función para prueba y empate del No-terminal Y
 */
simbolo Y();

/**
 * Función para prueba y empate del No-terminal Z
 */
simbolo Z();

/**
 * Función para prueba y empate del No-terminal ZP (Z prima)
 */
simbolo ZP();

/**
 * Función para prueba y empate del No-terminal AA
 */
simbolo AA();

/**
 * Función para prueba y empate del No-terminal AAP (AA prima)
 */
simbolo AAP();

/**
 * Función para consumo de componente léxico actual al hacer empate
 */
void eat(int clase);

/**
 * Función principal de análisis sintáctico.
 * Debe llamar a función de símbolo inicial de la gramática.
 * También inicializar las tablas de símbolos y tipos.
 */
void parse();

/**
 * Función para reporte de errores sintácticos y semánticos.
 */
void error(string msg);

/**
 * (opcional) Función para buscar símbolos en la tabla de símbolos
 */
int buscar(string simbolo);

/**
 * Obtener tamaño de elemento de la tabla de tipos
 */
int getTam(int id);

/**
 * Función para imprimir Tabla de tipos
 */
void printTT(tabla_simbolos *TT);

/**
 * Función para imprimir Tabla de símbolos
 */
void printTS(tabla_simbolos *TS);
