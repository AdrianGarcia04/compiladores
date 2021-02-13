#include <stdio.h>
#include "tokens.h"

token *crea_token(int clase) {
  token *t_out = (token*)malloc(sizeof(token));
  t_out->clase = clase;
  return t_out;
}

token *crea_token_valor(int clase, string valor) {
  token *t_out = (token*)malloc(sizeof(token));
  t_out->clase = clase;
  t_out->valor = valor;
  return t_out;
}

token *crea_token_valor_tipo(int clase, string valor, int tipo) {
  token *t_out = (token*)malloc(sizeof(token));
  t_out->clase = clase;
  t_out->valor = valor;
  t_out->tipo = tipo;
  return t_out;
}

int equals(token *t1, int clase) {
  return t1->clase == clase;
}
