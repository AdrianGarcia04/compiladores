#pragma once
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <string>
#include "tokens.h"
#include "tablasimbolos.h"
#include "tablasimbolos.h"
#include "tablatipos.h"
#include "tablacadenas.h"
#include "codigoint.h"
#include "expresion.h"
#include "semantico.h"

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
exp C();

/**
 * Función para prueba y empate del No-terminal D
 */
exp D();

/**
 * Función para prueba y empate del No-terminal E
 */
exp E(exp e);

/**
 * Función para prueba y empate del No-terminal F
 */
exp F(exp f);

/**
 * Función para prueba y empate del No-terminal FP (F prima)
 */
exp FP(exp fp);

/**
 * Función para prueba y empate del No-terminal G
 */
void G();

/**
 * Función para prueba y empate del No-terminal H
 */
argExp H();

/**
 * Función para prueba y empate del No-terminal I
 */
argExp I();

/**
 * Función para prueba y empate del No-terminal IP (I prima)
 */
argExp IP(exp ip);

/**
 * Función para prueba y empate del No-terminal J
 */
blockExp J(blockExp j);

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
void L(blockExp l);

/**
 * Función para prueba y empate del No-terminal LP (L prima)
 */
void LP(boolExpH l);

/**
 * Función para prueba y empate del No-terminal LPP (L bi-prima)
 */
void LPP();

/**
 * Función para prueba y empate del No-terminal M
 */
switchExp M(switchExp m);

/**
 * Función para prueba y empate del No-terminal N
 */
exp N();

/**
 * Función para prueba y empate del No-terminal O
 */
exp O();

/**
 * Función para prueba y empate del No-terminal P
 */
exp P();

exp PP(exp);

/**
 * Función para prueba y empate del No-terminal Q
 */
boolExp Q(boolExp q);

/**
 * Función para prueba y empate del No-terminal QP (Q prima)
 */
boolExpH QP(boolExpH q);

/**
 * Función para prueba y empate del No-terminal R
 */
exp R();

/**
 * Función para prueba y empate del No-terminal RP (R prima)
 */
exp RP();

/**
 * Función para prueba y empate del No-terminal S
 */
exp S();

/**
 * Función para prueba y empate del No-terminal SP (S prima)
 */
exp SP();

/**
 * Función para prueba y empate del No-terminal T
 */
exp T();

/**
 * Función para prueba y empate del No-terminal TP (T prima)
 */
exp TP();

/**
 * Función para prueba y empate del No-terminal U
 */
exp U();

/**
 * Función para prueba y empate del No-terminal UP (U prima)
 */
exp UP();

/**
 * Función para prueba y empate del No-terminal V
 */
exp V();

/**
 * Función para prueba y empate del No-terminal VP (V prima)
 */
exp VP();

/**
 * Función para prueba y empate del No-terminal W
 */
exp W();

/**
 * Función para prueba y empate del No-terminal X
 */
exp X();

/**
 * Función para prueba y empate del No-terminal Y
 */
exp Y();

/**
 * Función para prueba y empate del No-terminal Z
 */
exp Z();

/**
 * Función para prueba y empate del No-terminal ZP (Z prima)
 */
exp ZP();

/**
 * Función para prueba y empate del No-terminal AA
 */
arrayExp AA(arrayExp aa);

/**
 * Función para prueba y empate del No-terminal AAP (AA prima)
 */
arrayExp AAP(arrayExp aap);

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
