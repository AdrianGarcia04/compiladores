#include "semantico.h"
#include "parser2.h"
#include "simbolo.h"
#include "tablasimbolos.h"
#include "tablatipos.h"
#include "expresion.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <string>

extern token *yylex();
extern int yylineno;
using namespace std;

token *tokenActual;
int dir;
pila_simbolos* pilaSimbolos;
pila_tipos* pilaTipos;
stack<string> cadenas;

void eat(int clase) {
    if (equals(tokenActual, clase))
    {
        tokenActual = yylex();
    }
    else
    {
        error("Error de sintaxis");
    }
}

void error(string msg) {
  cout << msg << endl;
  cout << ": línea " << yylineno << endl;
  exit(1);
}

void parse() {
    pilaSimbolos = crear_pila_simbolos();
    pilaTipos = crear_pila_tipos();
    /*
    0 - int
    1 - float
    2 - char
    3 - double
    4 - void
    */


    A();
    //imprimir TS y TT
}

void A() {
  pilaSimbolos->insertar_tabla();
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
      exp* c = C();
      exp* f = crea_exp();
      f->tipo = c->tipo;
      F(f);
      eat(COMA);
      B();
  }
}

exp* C(){
  exp* c = crea_exp();
  // exp* d = D();
  // exp* e = crea_exp();
  // e->base = d->base;
  // E(e);
  // c->tipo = e->tipo;
  return c;
}

exp* D() {
  exp* d = crea_exp();
  if (equals(tokenActual, INT)) {
    eat(INT);
    d->tipo = 0;
  }
  else if (equals(tokenActual, FLOAT))
  {
    eat(FLOAT);
    d->tipo = 1;
  }
  else if (equals(tokenActual, CHAR))
  {
    eat(CHAR);
    d->tipo = 2;
  }
  else if (equals(tokenActual, DOUBLE))
  {
    eat(DOUBLE);
    d->tipo = 3;
  }
  else if (equals(tokenActual, VOID))
  {
    eat(VOID);
    d->tipo = 4;
  }
  return d;
}

// exp* E() {
//   if (equals(tokenActual, CIZQ)) {
//     string valor;
//     eat(CIZQ);
//     valor = tokenActual->valor;
//     eat(NUM);
//     eat(CDER);
//     E();
//   }
// }
