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

struct boolExp {
    // Etiquetas
    string vddr;
    string fls;
    list<string> listaIndices;

    boolExp(){}
    boolExp(string vddr, string fls, list<string> listaIndices) : vddr(vddr), fls(fls), listaIndices(listaIndices){}
};

struct boolExpH{
    string dirH;
    int tipoH;

    boolExpH(){}
    boolExpH(string dirH, int tipoH) : dirH(dirH), tipoH(tipoH){}
};

struct blockExp{
    string sig; // Etiqueta de siguiente
    string sigH; //Para heredados

    blockExp(){}
    blockExp(string sig, string sigH) : sig(sig), sigH(sigH){}
};


struct argExp{
    list<int> lista; //<Lista de tipos>

    argExp(){}
    argExp(list<int> lista) : lista(lista){}
};

struct switchExp{
    string prueba;

    switchExp(){}
    switchExp(string prueba) : prueba(prueba){}
};

struct caseExp{
    int id;
    string inicio;

    caseExp(){}
    caseExp(int id, string inicio) : id(id) , inicio(inicio){}
};

struct defaultExp{
    string inicio;

    defaultExp() {}
    defaultExp(string inicio): inicio(inicio) {}
};


struct arrayExp{
    int tam;

    arrayExp() {}
    arrayExp(int tam): tam(tam) {}
};
