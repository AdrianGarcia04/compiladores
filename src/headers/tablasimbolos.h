#pragma once

#include <stack>
#include <vector>
#include <string>
#include "simbolo.h"

using namespace std;

struct tabla_simbolos{
    vector<simbolo> tabla;    
public:
    bool buscar(string id);
    bool insertar(simbolo s);
    int getTipo(string id);
    void imprimir();
};

// typedef struct tabla_simbolos tabla_simbolos;

struct pila_simbolos{
    stack<tabla_simbolos> pila;
public:
    void push() ;
    void pop();
    tabla_simbolos top();
};

// typedef struct pila_simbolos pila_simbolos;



