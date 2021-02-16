#pragma once

#include <stack>
#include <vector>
#include <string>
#include "simbolo.h"

using namespace std;

typedef struct tabla_simbolos{
    vector<simbolo> tabla;
public:
    bool buscar(string id);
    bool insertar(simbolo s);
    int getTipo(string id);
    void imprimir();
} tabla_simbolos;

typedef struct pila_simbolos{
    stack<tabla_simbolos> pila;
public:
    void push() ;
    void pop();
    tabla_simbolos top();
} pila_simbolos;

pila_simbolos* crear_pila_simbolos();
