#pragma once
using namespace std;
#include <string>
#include <vector>

/**
 * Estructura para modelar símbolos de la TS
 */
typedef struct simbolo {
  int tipo;
  int dir; //dirección
  string id; //identificador
  int var; 
  vector<int> args; //argumentos
} simbolo ;

/**
 * Inicialización de símbolos
 */
simbolo *crea_simbolo(string id, int dir, int type, int var, vector<int> args);
