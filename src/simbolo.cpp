#include <stdio.h>
#include "simbolo.h"

simbolo *crea_simbolo(string id, int dir, int tipo, int var, vector<int> args) {
  simbolo *s_out = (simbolo*)malloc(sizeof(simbolo));
  s_out->id = id;
  s_out->dir = dir;
  s_out->tipo = tipo;
  s_out->var = var;
  s_out->args = args;
  return s_out;
}

simbolo *crea_simbolo_v() {
  simbolo *s_out = (simbolo*)malloc(sizeof(simbolo));
  return s_out;
}
