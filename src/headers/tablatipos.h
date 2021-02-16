#pragma once

#include <stack>
#include <vector>
#include <string>
#include "tipo.h"

using namespace std;

typedef struct tabla_tipos {
    vector<tipo> tabla;
public:
    bool buscar(int id);
    bool insertar(tipo s);
    void imprimir();
} tabla_tipos;

typedef struct pila_tipos{
    stack<tabla_tipos*> pila;
public:
    void push(tabla_tipos* tabla);
    void pop();
    tabla_tipos* top();
    void insertar_tabla();
} pila_tipos;

tabla_tipos* crear_tabla_tipos();

pila_tipos* crear_pila_tipos();
