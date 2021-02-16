#include "semantico.h"
#include "parser2.h"
#include "simbolo.h"
#include <stdio.h>
extern token *yylex();
extern int yylineno;

token *tokenActual;
int dir;
tabla_simbolos tablaSimbolos;
tabla_simbolos tablaTipos;

void eat(int clase)
{
    if (equals(tokenActual, clase))
    {
        tokenActual = yylex();
    }
    else
    {
        error("Error de sintaxis");
    }
}

void parse()
{
    //inicializar TS y TT
    A();
    //imprimir TS y TT
}

void A() {
  // PilaTS.push(nuevaTablaTS())
  // PilaTT.push(nuevaTablaTT())
  dir = 0;
  B();
  G();
  if(equals(tokenActual, FIN)) {
    puts("Fin de análisis sintáctico.");
    return;
  } else {
    puts("Error al final del análisis sintáctico");
  }
}

void B(){
  if (equals(tokenActual, INT)
    || equals(tokenActual, FLOAT)
    || equals(tokenActual, CHAR)
    || equals(tokenActual, DOUBLE)
    || equals(tokenActual, VOID)) {
      // simbolo* c = C();
      // simbolo* f = crea_simbolo_v();
      // f->tipo = c->tipo;
      // F(f);
      // eat(PCOMA);
      // B();
  }
}

simbolo C(){
  simbolo* c = crea_simbolo_v();
  // simbolo* d = D();
  // simbolo* e = crea_simbolo_v();
  // e->base = d->base;
  // E(e);
  // c->tipo = e->tipo;
  return c;
}
