%{
  #include <stdio.h>
  #include "tokens.h"
  #define YY_DECL token *yylex(void)
%}

%option noyywrap
%option yylineno

num_ent [0-9]+
num_float [0-9]*"."[0-9]+
id [a-zA-Z][a-zA-Z0-9]*
whitespace [ \t\n]
boolean "true"|"false"
cadena \".*\"

%%

"," { ECHO; return crea_token(COMA); }
";" { ECHO; return crea_token(PCOMA); }
"[" { ECHO; return crea_token(CIZQ); }
"]" { ECHO; return crea_token(CDER); }
"(" { ECHO; return crea_token(PIZQ); }
")" { ECHO; return crea_token(PDER); }
":" { ECHO; return crea_token(DDOT); }

"int" { ECHO; return crea_token(INT); }
"float" { ECHO; return crea_token(FLOAT);}
"char" {ECHO; return crea_token(CHAR);}
"double" {ECHO; return crea_token(DOUBLE);}
"void" {ECHO; return crea_token(VOID);}

"if" { ECHO; return crea_token(IF); }
"else" { ECHO; return crea_token(ELSE); }
"do" { ECHO; return crea_token(DO); }
"while" { ECHO; return crea_token(WHILE); }
"break" { ECHO; return crea_token(BREAK); }
"switch" { ECHO; return crea_token(SWITCH); }
"default" { ECHO; return crea_token(DEFAULT); }
"case" { ECHO; return crea_token(CASE); }
"true" { ECHO; return crea_token(TRUE); }
"false" { ECHO; return crea_token(FALSE); }
"func" { ECHO; return crea_token(FUNC); }
"return" { ECHO; return crea_token(RETURN); }
"print" { ECHO; return crea_token(PRINT); }
"scan" { ECHO; return crea_token(SCAN); }

"&&" { ECHO; return crea_token(AND); }
"||" { ECHO; return crea_token(OR); }
"==" { ECHO; return crea_token(EQ); }
"!=" { ECHO; return crea_token(NEQ); }
"<" { ECHO; return crea_token(LESS); }
"<=" { ECHO; return crea_token(LEQ); }
">=" { ECHO; return crea_token(GEQ); }
">" { ECHO; return crea_token(GREATER); }
"+" { ECHO; return crea_token(PLUS); }
"-" { ECHO; return crea_token(MINUS); }
"*" { ECHO; return crea_token(MULT); }
"/" { ECHO; return crea_token(DIV); }
"%" { ECHO; return crea_token(MOD); }
"!" { ECHO; return crea_token(NOT); }
"=" {ECHO; return crea_token(ASIG); }
"{" {ECHO; return crea_token(LKEY); }
"}" {ECHO; return crea_token(RKEY); }

{cadena} { ECHO; return crea_token_valor(STR, yytext); }
{num_ent} { ECHO; return crea_token_valor_tipo(NUM, yytext, 0); }
{num_float} { ECHO; return crea_token_valor_tipo(NUM, yytext, 1); }
{id} { ECHO; return crea_token_valor(ID, yytext); }
{whitespace} { ECHO; }
<<EOF>> { puts("Fin de análisis léxico."); return crea_token(FIN); }
. { printf("Error léxico en la linea: %i\n", yylineno); exit(1); }

%%
