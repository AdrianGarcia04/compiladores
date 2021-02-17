#include "parser2.h"
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
stack<tablasimbolos> pilaTS;
stack<tablatipos> pilaTT;
tablacadenas cadenas;
stack<int> pilaDir;
//Lista de Retorno

void parse() {
    A();
    //imprimir TS y TT
}

void A() {
   pilaTS.push(tablasimbolos());

   tablatipos tablaTipos = tablatipos();
   tablaTipos.agregar(tipo_s(0, "int",    4, -1, -1));
   tablaTipos.agregar(tipo_s(1, "float",  4, -1, -1));
   tablaTipos.agregar(tipo_s(2, "char",   4, -1, -1));
   tablaTipos.agregar(tipo_s(3, "double", 4, -1, -1));
   tablaTipos.agregar(tipo_s(4, "void",   4, -1, -1));
   pilaTT.push(tablaTipos);

   dir = 0;
   // B();
   // G();
   if(equals(tokenActual, FIN)) {
     puts("Fin de análisis sintáctico.");
     return;
   } else {
     puts("Error al final del análisis sintáctico");
   }
 }

void B() {
   if (equals(tokenActual, INT)
     || equals(tokenActual, FLOAT)
     || equals(tokenActual, CHAR)
     || equals(tokenActual, DOUBLE)
     || equals(tokenActual, VOID)) {
       exp c = C();
       exp f = exp();
       f.tipo = c.tipo;
       F(f);
       eat(PCOMA);
       B();
   }
 }

 exp C() {
   exp c = exp();
   exp d = D();
   exp e = exp();
   e.base = d.tipo;
   e = E(e);
   c.tipo = e.tipo;
   return c;
 }

 exp D() {
   exp d = exp();
   if (equals(tokenActual, INT)) {
     eat(INT);
     d.tipo = 0;
   }
   else if (equals(tokenActual, FLOAT))
   {
     eat(FLOAT);
     d.tipo = 1;
   }
   else if (equals(tokenActual, CHAR))
   {
     eat(CHAR);
     d.tipo = 2;
   }
   else if (equals(tokenActual, DOUBLE))
   {
     eat(DOUBLE);
     d.tipo = 3;
   }
   else if (equals(tokenActual, VOID))
   {
     eat(VOID);
     d.tipo = 4;
   }
   return d;
 }

exp E(exp ep) {
     exp e = exp();
     e.base = ep.base;
    if (equals(tokenActual, CIZQ)) {
      eat(CIZQ);
      int numval = stoi(tokenActual->valor);
      eat(NUM);
      eat(CDER);
      exp e1 = E(e);
      pilaTT.top().agregar(tipo_s(5,"array",numval,-1,e1.tipo));
      e.tipo = pilaTT.top().tabla.back().id;
    } else {
        e.tipo = e.base;
    }
    return e;
}

exp F(exp ft) {
    string id = tokenActual->valor;
    eat(ID);
    exp f = exp();
    f.tipo = ft.tipo;
    exp fp = FP(f);
    if (!pilaTS.top().buscar(id)) {
        pilaTS.top().agregar(simbolo(id,dir,f.tipo,"var", nullptr));
        dir += pilaTT.top().get_tam(f.tipo);
    }else{
        error("El id no está definido.");
    }
    return f;

}

exp FP(exp fpt) {
    if (equals(tokenActual,COMA)) {
        eat(COMA);
        string id = tokenActual -> valor;
        eat(ID);
        exp fp = exp();
        fp.tipo = fpt.tipo;
        if (!pilaTS.top().buscar(id)) {
            pilaTS.top().agregar(simbolo(id,dir,fp.tipo,"var", nullptr));
            dir += pilaTT.top().get_tam(fp.tipo);
        }else{
            error("El id ya está declarado");
        }
        return fp;
    }
}

void G() {
    if (equals(tokenActual,FUNC)) {
        eat(FUNC);
        exp c = C();
        string id = tokenActual->valor;
        eat(ID);
        eat(PIZQ);
        argExp h = H(); //Por definir
        eat(PDER);
        //Lista de Retorno = nullptr
        pilaTS.push(tablasimbolos());
        pilaTT.push(tablatipos());
        pilaDir.push(dir);
        dir = 0;
        if (!pilaTS.top().buscar(id)) {
            /*equivalentes(listaRetorno.tipo,c.tipo)*/
            if (true) {
                pilaTS.top().agregar(simbolo(id,-1,c.tipo,'func',h.lista));
                genCod(cuadrupla("label", "","",id));
                blockExp j = blockExp();
                j.sig = nuevaEtiqueta();
                j = J(j);
                G();
                genCod(cuadrupla("label","","",j.sig));
            }else{
                error("Retorno no coincide");
            }
        }else{
            error(id + " no declarado");
        }
        pilaTS.pop();
        pilaTT.pop();
        dir = pilaDir.top();
        pilaDir.pop();
    }

}

argExp H() {
    argExp h = argExp();
    if (equals(tokenActual, INT)
        || equals(tokenActual, FLOAT)
        || equals(tokenActual, CHAR)
        || equals(tokenActual, DOUBLE)
        || equals(tokenActual, VOID)) {
        argExp i = I();
        h.lista = i.lista;
    }else{ //H -> eps

    }
    return h;
}

exp I() {
    argExp i = argExp();
    exp c = C();
    string id = tokenActual->valor;
    eat(ID);
    argExp ip = IP(c);
    if (!pilaTS.top().buscar(id)) {
        pilaTS.top().agregar(simbolo(id,dir,c.tipo,"param", nullptr));
        dir += pilaTT.top().get_tam(c.tipo);
    }else{
        error(id + "ya está declarado");
    }
    i.lista = ip.lista;
    i.lista.push_back(c.tipo);
    return i;
}

argExp IP(exp ci) {
    argExp ip = argExp();
    if (equals(tokenActual, COMA)) {
        eat(COMA);
        exp c = C();
        string id = tokenActual->valor;
        eat(ID);
        argExp ip1 = IP(c);
        if (!pilaTS.top().buscar(id)) {
            pilaTS.top().agregar(simbolo(id,dir,c.tipo,"param", nullptr));
            dir += pilaTT.top().get_tam(c.tipo);
        }else{
            error(id + "ya está declarado");
        }
        ip.lista = ip1.lista;
        ip.lista.push_back(c.tipo);
        return ip;
    }else{
        ip.lista.push_back(ci.tipo);
    }
}

blockExp J(blockExp jh){
    blockExp j = blockExp();
    eat(LKEY);
    j.sig = jh.sig;
    B();
    blockExp k = K(j);
    eat(RKEY);
    genCod(cuadrupla("label","","",j.sig));
    return j;
}

blockExp K(blockExp j){
    blockExp k = blockExp();
    k.sig = j.sig;
    blockExp l = L();
    blockExp kp = blockExp();
    kp.sigH = k.sig;
    kp = KP(kp);
    l.sig = kp.sig;
    return k;
}

blockExp KP(blockExp k){
    blockExp kp;
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
        blockExp l = L();
        kp.sigH = k.sigH;
        kp = KP(kp);
        l.sig = kp.sig;
    }else{
        kp.sig = kp.sigH;
    }
    return kp;
}

blockExp L(){
    switch (tokenActual->clase) {
        case ID:
            exp p = P();
            eat(ASIG);
            boolExp q = Q();
            eat(PCOMA);
            if (equivalentes(p.tipo,q.tipo)){
                string d1 = reducir(q.dir,q.tipo,p.tipo);
                genCod(cuadrupla("label","","",d1));
            }else{
                error("Tipos incompatibles");
            }
            break;
        case IF:
            eat(IF);
            eat(PIZQ);
            boolExp q;
            q.vddr = nuevaEtiqueta();
            q.fls = nuevoIndice();

    }
}

switchExp M(switchExp mparam) {
  switchExp m = switchExp();
  if (equals(tokenActual, CASE))
  {
    switchExp n = switchExp();
    n.sig = mparam.sig;
    blockExp n = N(n);
    switchExp m1 = switchExp();
    m1.sig = mparam.sig;
    M(m1);
    m.prueba = m.prueba || m1.prueba;
    return m;
  }
  else if (equals(tokenActual, DEFAULT))
  {
    switchExp o = switchExp();
    o.sig = mparam.sig;
    O(o.sig);
    m.prueba = o.prueba;
  }
}

blockExp N(switchExp mparam) {
  eat(CASE);
  eat(NUM);
  eat(DDOT);
  blockExp k = blockExp();
  k.sig = mparam.sig;
  K();
  caseExp n = caseExp();
  n.inicio = sem.nuevaEtiqueta();
  // sem.genCod(cuadrupla(to_string() + "=="    ));
  sem.genCod(cuadrupla("label", "", "", n.inicio));
}

void O(switchExp oparam) {
  eat(DEFAULT);
  eat(DDOT);
  switchExp k = switchExp();
  k.sig = oparam.sig;
  K();
  caseExp o = caseExp();
  o.inicio = sem.nuevaEtiqueta();
  sem.genCod(cuadrupla("label", "", "", o.inicio));
}

exp AA(exp aaParam) {
  exp aa = exp();
  if (equals(tokenActual,CIZQ)) {
    eat(CIZQ);
    exp q = Q();
    eat(CDER);
    if (pilaTS.top().buscar(aaParam.base)) {
      if (q.tipo == 0) {
        int tipoTmp = pilaTS.top().get_tipo(q.base);
        if (pilaTT.top().get_nom(tipoTmp) == 5) { // array
          exp aap = exp();
          aap.tipo = pilaTT.top().get_base(tipoTmp);
          aap.dir = nuevaTemporal();
          aap.dir = pilaTT.top().get_tam(aap.tipo);
          // genCod(cuadrupla("dirTmp", "","",id));
          AAP();
          aa.dir = aap.dir;
          aa.tipo = aap.tipo;
        }
        else {
          error("El id no es un arreglo");
        }
      }
      else {
        error("El índice del arreglo debe ser un entero")
      }
    }
    else {
      error("El id no está declarado");
    }
  }
  else {
    aa.dir = aaParam.dir;
    aa.tipo = aaParam.tipo;
  }
  return aa;
}

exp AAP(exp aapParam) {
  exp aap = exp();
  if (equals(tokenActual,CIZQ)) {
    eat(CIZQ);
    exp q = Q();
    eat(CDER);
    if (q.tipo == 0) { // INT
      if (pilaTT.top().get_nom(aapParam.tipo) == 5) { // array
        exp aap1 = exp();
        aap1.tipo = pilaTT.top().get_base(aapParam.tipo);
        int dirTmp = nuevaTemporal();
        aap1.dir = nuevaTemporal();
        aap1.tam = pilaTT.top().get_tam(aapParam.tipo);
        // genCod(cuadrupla("dirTmp", "","",id));
        // genCod(cuadrupla("dirTmp", "","",id));
        AAP();
        aap.dir = aap1.dir;
        aap.tipo = aap1.tipo;
      }
      else {
        error("El id no es un arreglo");
      }
    }
    else {
      error("El índice del arreglo debe ser un entero")
    }
  }
  else {
    aap.dir = aapParam.dir;
    aap.tipo = aapParam.tipo;
  }
  return aap;
}

void eat(int clase) {
    if (equals(tokenActual, clase))
        tokenActual = yylex();
    else
        error("Error de sintaxis");
}

void error(string msg) {
  cout << msg << endl;
  cout << ": línea " << yylineno << endl;
  exit(1);
}
