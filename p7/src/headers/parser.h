#pragma once
#include "tokens.h"
#include "tablasimbolos.h"

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
void C();

/**
 * Función para prueba y empate del No-terminal D
 */
void D();

/**
 * Función para prueba y empate del No-terminal E
 */
void E();

/**
 * Función para prueba y empate del No-terminal F
 */
void F();

/**
 * Función para prueba y empate del No-terminal FP (F prima)
 */
void FP();

/**
 * Función para prueba y empate del No-terminal G
 */
void G();

/**
 * Función para prueba y empate del No-terminal H
 */
void H();

/**
 * Función para prueba y empate del No-terminal I
 */
void I();

/**
 * Función para prueba y empate del No-terminal IP (I prima)
 */
void IP();

/**
 * Función para prueba y empate del No-terminal J
 */
void J();

/**
 * Función para prueba y empate del No-terminal K
 */
void K();

/**
 * Función para prueba y empate del No-terminal KP (K prima)
 */
void KP();

/**
 * Función para prueba y empate del No-terminal L
 */
void L();

/**
 * Función para prueba y empate del No-terminal L
 */
void LP();

/**
 * Función para prueba y empate del No-terminal L
 */
void LPP();

/**
 * Función para prueba y empate del No-terminal M
 */
void M();

/**
 * Función para prueba y empate del No-terminal N
 */
void N();

/**
 * Función para prueba y empate del No-terminal O
 */
void O();

/**
 * Función para prueba y empate del No-terminal P
 */
void P();

/**
 * Función para prueba y empate del No-terminal Q
 */
void Q();

/**
 * Función para prueba y empate del No-terminal QP (Q prima)
 */
void QP();

/**
 * Función para prueba y empate del No-terminal R
 */
void R();

/**
 * Función para prueba y empate del No-terminal RP (R prima)
 */
void RP();

/**
 * Función para prueba y empate del No-terminal S
 */
void S();

/**
 * Función para prueba y empate del No-terminal S
 */
void SP();

/**
 * Función para prueba y empate del No-terminal T
 */
void T();

/**
 * Función para prueba y empate del No-terminal TP (T prima)
 */
void TP();

/**
 * Función para prueba y empate del No-terminal U
 */
void U();

/**
 * Función para prueba y empate del No-terminal UP (U prima)
 */
void UP();

/**
 * Función para prueba y empate del No-terminal V
 */
void V();

/**
 * Función para prueba y empate del No-terminal V
 */
void VP();

/**
 * Función para prueba y empate del No-terminal W
 */
void W();

/**
 * Función para prueba y empate del No-terminal X
 */
void X();

/**
 * Función para prueba y empate del No-terminal Y
 */
void Y();

/**
 * Función para prueba y empate del No-terminal Z
 */
void Z();

/**
 * Función para prueba y empate del No-terminal ZP (Z prima)
 */
void ZP();

/**
 * Función para prueba y empate del No-terminal ZP (Z prima)
 */
void AA();

/**
 * Función para prueba y empate del No-terminal ZP (Z prima)
 */
void AAP();

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
