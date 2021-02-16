#pragma once
#include "tokens.h"
#include "tablasimbolos.h"
#include "simbolo.h"
#include "expresion.h"

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
exp* C();

/**
 * Función para prueba y empate del No-terminal D
 */
exp* D();

/**
 * Función para prueba y empate del No-terminal E
 */
exp* E();

/**
 * Función para prueba y empate del No-terminal F
 */
exp* F(exp* f);

/**
 * Función para prueba y empate del No-terminal FP (F prima)
 */
exp* FP();

/**
 * Función para prueba y empate del No-terminal G
 */
exp* G();

/**
 * Función para prueba y empate del No-terminal H
 */
exp* H();

/**
 * Función para prueba y empate del No-terminal I
 */
exp* I();

/**
 * Función para prueba y empate del No-terminal IP (I prima)
 */
exp* IP();

/**
 * Función para prueba y empate del No-terminal J
 */
exp* J();

/**
 * Función para prueba y empate del No-terminal K
 */
exp* K();

/**
 * Función para prueba y empate del No-terminal KP (K prima)
 */
exp* KP();

/**
 * Función para prueba y empate del No-terminal L
 */
exp* L();

/**
 * Función para prueba y empate del No-terminal LP (L prima)
 */
exp* LP();

/**
 * Función para prueba y empate del No-terminal LPP (L bi-prima)
 */
exp* LPP();

/**
 * Función para prueba y empate del No-terminal M
 */
exp* M();

/**
 * Función para prueba y empate del No-terminal N
 */
exp* N();

/**
 * Función para prueba y empate del No-terminal O
 */
exp* O();

/**
 * Función para prueba y empate del No-terminal P
 */
exp* P();

/**
 * Función para prueba y empate del No-terminal Q
 */
exp* Q();

/**
 * Función para prueba y empate del No-terminal QP (Q prima)
 */
exp* QP();

/**
 * Función para prueba y empate del No-terminal R
 */
exp* R();

/**
 * Función para prueba y empate del No-terminal RP (R prima)
 */
exp* RP();

/**
 * Función para prueba y empate del No-terminal S
 */
exp* S();

/**
 * Función para prueba y empate del No-terminal SP (S prima)
 */
exp* SP();

/**
 * Función para prueba y empate del No-terminal T
 */
exp* T();

/**
 * Función para prueba y empate del No-terminal TP (T prima)
 */
exp* TP();

/**
 * Función para prueba y empate del No-terminal U
 */
exp* U();

/**
 * Función para prueba y empate del No-terminal UP (U prima)
 */
exp* UP();

/**
 * Función para prueba y empate del No-terminal V
 */
exp* V();

/**
 * Función para prueba y empate del No-terminal VP (V prima)
 */
exp* VP();

/**
 * Función para prueba y empate del No-terminal W
 */
exp* W();

/**
 * Función para prueba y empate del No-terminal X
 */
exp* X();

/**
 * Función para prueba y empate del No-terminal Y
 */
exp* Y();

/**
 * Función para prueba y empate del No-terminal Z
 */
exp* Z();

/**
 * Función para prueba y empate del No-terminal ZP (Z prima)
 */
exp* ZP();

/**
 * Función para prueba y empate del No-terminal AA
 */
exp* AA();

/**
 * Función para prueba y empate del No-terminal AAP (AA prima)
 */
exp* AAP();

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