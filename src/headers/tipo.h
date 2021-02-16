#pragma once
#include <string>
using namespace std;

/**
 * Estructura para modelar entradas de la TT
 */
typedef struct tipo {
  int id;
  char *tipo;
  int tam;
  int elem;
  int tipoBase;
} tipo;

tipo *crea_tipo();
