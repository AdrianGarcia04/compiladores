#pragma once
using namespace std;
#include <string>
#include <vector>

/**
 * Estructura para modelar símbolos de la TS
 */
typedef struct simbolo {
  string id;
  int dir;
  int tipo;
  int var;
  vector<int> args;
} simbolo;

simbolo *crea_simbolo();
