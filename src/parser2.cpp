#include "semantico.h"
#include "parser.h"
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
