#include "semantico.h"
#include "parser2.h"
#include "tablasimbolos.h"
#include "tablatipos.h"
#include "tablacadenas.h"
#include "expresion.h"
#include "codigoint.h"
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
    /*
    0 - int
    1 - float
    2 - char
    3 - double
    4 - void
    */

    pilaTS.push(tablasimbolos());
    tablatipos tablaTipos = tablatipos();

    tablaTipos.agregar(tipo_s(0, "int",    4, -1, -1));
    tablaTipos.agregar(tipo_s(1, "float",  4, -1, -1));
    tablaTipos.agregar(tipo_s(2, "char",   4, -1, -1));
    tablaTipos.agregar(tipo_s(3, "double", 4, -1, -1));
    tablaTipos.agregar(tipo_s(4, "void",   4, -1, -1));
    pilaTT.push(tablaTipos);

    // A();
    //imprimir TS y TT
}

void A() {
   pilaTS.push(tablasimbolos()); //Espero este sea el constructor
   pilaTT.push(tablatipos());
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
       exp c = C();
       exp f = exp();
       f.tipo = c.tipo;
       F(f);
       eat(PCOMA);
       B();
   }
 }

 exp C(){
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
    if (!pilaTS.top().buscar(id)){
        pilaTS.top().agregar(simbolo(id,dir,f.tipo,"var", nullptr));
        dir += pilaTT.top().get_tam(f.tipo);
    }else{
        error("El id no está definido.");
    }
    return f;

}

exp FP(exp fpt){
    if (equals(tokenActual,COMA)){
        eat(COMA);
        string id = tokenActual -> valor;
        eat(ID);
        exp fp = exp();
        fp.tipo = fpt.tipo;
        if (!pilaTS.top().buscar(id)){
            pilaTS.top().agregar(simbolo(id,dir,fp.tipo,"var", nullptr));
            dir += pilaTT.top().get_tam(fp.tipo);
        }else{
            error("El id ya está declarado");
        }
        return fp;
    }
}

void G(){
    if (equals(tokenActual,FUNC)){
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
        if (!pilaTS.top().buscar(id)){
            /*equivalentes(listaRetorno.tipo,c.tipo)*/
            if (true){
                pilaTS.top().agregar(simbolo(id,-1,c.tipo,'func',h.lista));
                genCod(cuadrupla("label", "","",id));
                blockExp j = blockExp();
                j.sig = nuevaEtq();
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

argExp H(){
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
    if (!pilaTS.top().buscar(id)){
        pilaTS.top().agregar(simbolo(id,dir,c.tipo,"param", nullptr));
        dir += pilaTT.top().get_tam(c.tipo);
    }else{
        error(id + "ya está declarado");
    }
    i.lista = ip.lista;
    i.lista.push_back(c.tipo);
    return i;
}

argExp IP(exp ci){
    argExp ip = argExp();
    if (equals(tokenActual, COMA)) {
        eat(COMA);
        exp c = C();
        string id = tokenActual->valor;
        eat(ID);
        argExp ip1 = IP(c);
        if (!pilaTS.top().buscar(id)){
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
