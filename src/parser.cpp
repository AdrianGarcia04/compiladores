#include "parser.h"
#include <stdio.h>
extern token *yylex();
extern int yylineno;

token *tokenActual;
int dir;
tabla_simbolos tablaSimbolos;
tabla_simbolos tablaTipos;

void eat(int clase) {
  if(equals(tokenActual, clase)) {
    tokenActual = yylex();
  } else {
    error("Error de sintaxis");
  }
}

void parse() {
  //inicializar TS y TT
  A();
  //imprimir TS y TT
}

void A() {
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
      C();
      F();
      eat(PCOMA);
      B();
  }
  // else error
}

void C(){
  D();
  E();
}

void D(){
  if (equals(tokenActual, INT)) {
    eat(INT);
  }
  else if (equals(tokenActual, FLOAT)) {
    eat(FLOAT);
  }
  else if (equals(tokenActual, CHAR)) {
    eat(CHAR);
  }
  else if (equals(tokenActual, DOUBLE)) {
    eat(DOUBLE);
  }
  else if (equals(tokenActual, VOID)) {
    eat(VOID);
  }
}

void E(){
  if (equals(tokenActual, CIZQ)) {
    string valor;
    eat(CIZQ);
    valor = tokenActual->valor;
    eat(NUM);
    eat(CDER);
    E();
  }
}

void F(){
  if (equals(tokenActual, ID)) {
    eat(ID);
    FP();
  }
  // else error
}

void FP(){
  if (equals(tokenActual, COMA)) {
    eat(COMA);
    eat(ID);
    FP();
  }
}

void G() {
  if (equals(tokenActual, FUNC)) {
    eat(FUNC);
    C();
    eat(ID);
    eat(PIZQ);
    H();
    eat(PDER);
    J();
    G();
  }
}

void H() {
  if (equals(tokenActual, INT)
    || equals(tokenActual, FLOAT)
    || equals(tokenActual, CHAR)
    || equals(tokenActual, DOUBLE)
    || equals(tokenActual, VOID)) {
      I();
  }
}

void I() {
  C();
  eat(ID);
  IP();
}

void IP() {
  if (equals(tokenActual, COMA)) {
    eat(COMA);
    C();
    eat(ID);
    IP();
  }
}

void J() {
  eat(LKEY);
  B();
  K();
  eat(RKEY);
}

void K() {
  L();
  KP();
}

void KP() {
  if (equals(tokenActual,ID) ||
    equals(tokenActual,IF) ||
    equals(tokenActual,WHILE) ||
    equals(tokenActual,DO) ||
    equals(tokenActual,BREAK) ||
    equals(tokenActual,LKEY) ||
    equals(tokenActual,RETURN) ||
    equals(tokenActual,SWITCH) ||
    equals(tokenActual,PRINT) ||
    equals(tokenActual,SCAN)) {
    L();
    KP();
  }
}

void L() {
  if (equals(tokenActual, ID)) {
    P();
    eat(ASIG);
    Q();
  }
  else if (equals(tokenActual, IF))
  {
    eat(IF);
    eat(PIZQ);
    Q();
    eat(PDER);
    L();
    if (equals(tokenActual, ELSE)) {
      eat(ELSE);
      L();
    }
  }
  else if (equals(tokenActual, WHILE)) {
    eat(WHILE);
    eat(PIZQ);
    Q();
    eat(PDER);
    L();
  }
  else if (equals(tokenActual, DO)) {
    eat(DO);
    L();
    eat(WHILE);
    eat(PIZQ);
    Q();
    eat(PDER);
  }
  else if (equals(tokenActual,BREAK))
  {
    eat(BREAK);
    eat(PCOMA);
  }
  else if (equals(tokenActual,LKEY))
  {
    J();
  }
  else if (equals(tokenActual,RETURN))
  {
    eat(RETURN);
    LPP();
  }
  else if (equals(tokenActual,SWITCH))
  {
    eat(SWITCH);
    eat(PIZQ);
    Q();
    eat(PDER);
    eat(LKEY);
    M();
    eat(RKEY);
  }
  else if (equals(tokenActual,PRINT))
  {
    eat(PRINT);
    U();
    eat(PCOMA);
  }
  else if (equals(tokenActual,SCAN))
  {
    eat(SCAN);
    P();
  }
}

void LP() {
  if (equals(tokenActual,ELSE))
  {
    eat(ELSE);
    L();
  }
}

void LPP() {
  if (equals(tokenActual,PCOMA))
  {
    eat(PCOMA);
  }
  else {
    U();
    eat(PCOMA);
  }
}

void M() {
  if (equals(tokenActual, CASE)) {
    N();
    M();
  }
  else if (equals(tokenActual, DEFAULT)) {
    O();
  }
}

void N() {
  eat(CASE);
  eat(NUM);
  eat(DDOT);
  K();
}

void O() {
  eat(DEFAULT);
  eat(DDOT);
  K();
}

void P() {
  eat(ID);
  if (equals(tokenActual, CIZQ)) {
    AA();
  }
}

void Q() {
  R();
  QP();
}

void QP() {
  if (equals(tokenActual, OR)) {
    eat(OR);
    R();
    QP();
  }
}

void R() {
  S();
  RP();
}

void RP() {
  if (equals(tokenActual, AND)) {
    eat(AND);
    S();
    RP();
  }
}

void S() {
  T();
  SP();
}

void SP() {
  if (equals(tokenActual, EQ)) {
    eat(EQ);
    T();
    SP();
  }
  else if (equals(tokenActual, NEQ)) {
    eat(NEQ);
    T();
    SP();
  }
}

void T() {
  U();
  TP();
}

void TP() {
  if (equals(tokenActual, LESS)) {
    eat(LESS);
    U();
  }
  else if (equals(tokenActual, LEQ)) {
    eat(LEQ);
    U();
  }
  else if (equals(tokenActual, GEQ)) {
    eat(GEQ);
    U();
  }
  else if (equals(tokenActual, GREATER)) {
    eat(GREATER);
    U();
  }
}

void U() {
  V();
  UP();
}

void UP() {
  if (equals(tokenActual, PLUS)) {
    eat(PLUS);
    V();
    UP();
  }
  else if (equals(tokenActual, MINUS)) {
    eat(MINUS);
    V();
    UP();
  }
}

void V() {
  W();
  VP();
}

void VP() {
  if (equals(tokenActual, MULT)) {
    eat(MULT);
    W();
    VP();
  }
  else if (equals(tokenActual, DIV)) {
    eat(DIV);
    W();
    VP();
  }
  else if (equals(tokenActual, MOD)) {
    eat(MOD);
    W();
    VP();
  }
}

void W() {
  if (equals(tokenActual, NOT)) {
    eat(NOT);
    W();
  }
  else if (equals(tokenActual, MINUS)) {
    eat(MINUS);
    W();
  }
  else if (equals(tokenActual, PIZQ)
    || equals(tokenActual, ID)
    || equals(tokenActual, NUM)
    || equals(tokenActual, STR)
    || equals(tokenActual, TRUE)
    || equals(tokenActual, FALSE)) {
    X();
  }
}

void X() {
  if (equals(tokenActual, PIZQ)) {
    eat(PIZQ);
    Q();
    eat(PDER);
  }
  else if (equals(tokenActual, ID)) {
    eat(ID);
    if (equals(tokenActual, CIZQ)) {
      AA();
    }
    else if (equals(tokenActual, PIZQ)) {
      eat(PIZQ);
      Y();
      eat(PDER);
    }
  }
  else if (equals(tokenActual, NUM)) {
    eat(NUM);
  }
  else if (equals(tokenActual, STR)) {
    eat(STR);
  }
  else if (equals(tokenActual, TRUE)) {
    eat(TRUE);
  }
  else if (equals(tokenActual, FALSE)) {
    eat(FALSE);
  }
}

void Y() {
  if (equals(tokenActual, NOT)
    || equals(tokenActual, MINUS)
    || equals(tokenActual, PIZQ)
    || equals(tokenActual, ID)
    || equals(tokenActual, NUM)
    || equals(tokenActual, STR)
    || equals(tokenActual, TRUE)
    || equals(tokenActual, FALSE)) {
    Z();
  }
}

void Z() {
  Q();
  ZP();
}

void ZP() {
  if (equals(tokenActual,COMA)) {
    eat(COMA);
    Q();
    ZP();
  }
}

void AA() {
  eat(CIZQ);
  Q();
  eat(CDER);
  AAP();
}

void AAP() {
  if (equals(tokenActual,CIZQ)) {
    eat(CIZQ);
    Q();
    eat(CDER);
    AAP();
  }
}

void error(string msg) {
  cout << msg << endl;
  cout << ": línea " << yylineno << endl;
  exit(1);
}
