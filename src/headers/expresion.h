#pragma once
using namespace std;


struct exp :: exp {
    int tipo;
    string dir;
    string base;

    exp(){}

    exp(string d) : dir(d){}
    exp(string b) : base(b){}
    exp(int tp) : tipo(tp){}
    exp(string d, int tp) : dir(d), tipo(tp){}
    exp(string d, string b, int tp) : dir(d), base(b), tipo(tp){}
};

struct boolExp : exp
{
    // Etiquetas
    string vddr;
    string fls;
    list<string> listaIndices;

    boolExp(){}
    boolExp(string d, string v, string f, int tp){
        super::exp(d);
        this.vddr = v;
        this.fls = f;
        this.tipo = tp;
    }
};

struct boolExpH : boolExp{
    string dirH;
    int tipoH;

    //TODO: Constructor
};

struct blockExp : exp{
    string sig; // Etiqueta de siguiente
    string sigH; //Para heredados
    blockExp(){}

    blockExp(string s): sig(s){}

    blockExpH(string s): sigH(s){}
};


struct argExp : exp {
    list<int> lista; //<Lista de tipos>

    argExp(){}
};

struct switchExp : blockExp{
    string prueba;
};

struct caseExp : switchExp{
    int id;
    string inicio;

    caseExp(){}

    caseExp(int i, string s) : id(i) , inicio(s){}
};

struct defaultExp : switchExp{
    string inicio;

    defaultExp() {}

    defaultExp(string s): inicio(s) {}
};


struct arrayExp : exp{
    int tam;

    arrayExp() {}

    arrayExp(int i){}//TODO: params
};

