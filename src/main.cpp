#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

extern FILE *yyin;
extern token *yylex();
extern token *tokenActual;

int main(int argc, char **argv) {
  if(argc < 2) {
    puts("Falta archivo de entrada.");
    exit(1);
  }
  printf("Archivo de entrada: ");
  puts(argv[1]);
  FILE *fin = fopen(argv[1], "r");
  yyin = fin;

  puts("Comenzando análisis...");
  tokenActual = yylex();
  parse();
}
