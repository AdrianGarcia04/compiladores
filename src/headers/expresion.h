#pragma once
#include <string>
#include <list>
using namespace std;


struct exp {
    int tipo;
    string dir;
    string base;

    exp(){}

    exp(int tipo, string dir, string base) : tipo(tipo), dir(dir), base(base){}
};

struct boolExp : exp {
    // Etiquetas
    string vddr;
    string fls;
    list<string> listaIndices;

    boolExp(){}
    boolExp(string vddr, string fls, list<string> listaIndices) : vddr(vddr), fls(fls), listaIndices(listaIndices){}
};

struct boolExpH : boolExp {
    string dirH;
    int tipoH;
    string sig;
    string valor;
    boolExpH(){}
    boolExpH(string dirH, int tipoH) : dirH(dirH), tipoH(tipoH){}
};

struct blockExp : exp {
    string sig; // Etiqueta de siguiente

    blockExp(){}
    blockExp(string sig) : sig(sig){}
};


struct argExp : exp {
    list<int> lista; //<Lista de tipos>

    argExp(){}
    argExp(list<int> lista) : lista(lista){}
};

struct switchExp : blockExp {
    string prueba;
    string etqPrueba;
    string id;
    switchExp(){}
    switchExp(string prueba) : prueba(prueba){}
};

struct caseExp : switchExp {
    int id;
    string inicio;

    caseExp(){}
    caseExp(int id, string inicio) : id(id) , inicio(inicio){}
};

struct defaultExp : switchExp {
    string inicio;

    defaultExp() {}
    defaultExp(string inicio): inicio(inicio) {}
};


struct arrayExp : exp {
    int tam;

    arrayExp() {}
    arrayExp(int tam): tam(tam) {}
};
