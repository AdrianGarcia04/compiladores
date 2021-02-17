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
list<int> listaRetorno;
semantico sem;

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
        e.tipo = e.base; //TODO: Algo tiene que cambiar aqui.
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
        list<int> v;
        pilaTS.top().agregar(simbolo(id,dir,f.tipo,"var", v));
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
            list<int> v;
            pilaTS.top().agregar(simbolo(id,dir,fp.tipo,"var", v));
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
            if (sem.equivalentes(listaRetorno.front(),c.tipo)) {
                pilaTS.top().agregar(simbolo(id,-1,c.tipo,"func",h.lista));
                sem.genCod(cuadrupla("label", "","",id));
                blockExp j = blockExp();
                j.sig = sem.nuevaEtiqueta();
                j = J(j);
                G();
                sem.genCod(cuadrupla("label","","",j.sig));
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

argExp I() {
    argExp i = argExp();
    exp c = C();
    string id = tokenActual->valor;
    eat(ID);
    argExp ip = IP(c);
    if (!pilaTS.top().buscar(id)) {
        list<int> v;
        pilaTS.top().agregar(simbolo(id,dir,c.tipo,"param",v));
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
            list<int> v; //Muchos datos considerar a cambiar a apuntador.
            pilaTS.top().agregar(simbolo(id,dir,c.tipo,"param", v));
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
    K();
    eat(RKEY);
    sem.genCod(cuadrupla("label","","",j.sig));
    return j;
}

void K(){
    blockExp l;
    l.sig = sem.nuevaEtiqueta();
    sem.genCod(cuadrupla("label","","",l.sig));
    L(l);
    KP();
}

void KP(){
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
        blockExp l;
        l.sig = sem.nuevaEtiqueta();
        sem.genCod(cuadrupla("label","","",l.sig));
        L(l);
    }
}

void L(blockExp l) {
    switch (tokenActual->clase) {
        case ID: {
            exp p = P();
            eat(ASIG);
            boolExp q = Q(boolExp());
            eat(PCOMA);
            if (sem.equivalentes(p.tipo, q.tipo)) {
                string d1 = sem.reducir(q.dir, q.tipo, p.tipo);
                sem.genCod(cuadrupla("label", "", "", d1));
            } else {
                error("Tipos incompatibles");
            }
            break;
        }
        case IF: {
            eat(IF);
            eat(PIZQ);
            boolExp q;
            q.vddr = sem.nuevaEtiqueta();
            q.fls = sem.nuevoIndice();
            q = Q(q);
            eat(PDER);
            blockExp l1 = blockExp();
            l1.sig = l.sig;
            L(l1);
            boolExpH lp;
            lp.sig = l.sig;
            lp.listaIndices.push_back(q.fls);
            LP(lp);
            sem.genCod(cuadrupla("label", "", "", q.vddr));
            break;
        }
        case WHILE: {
            eat(WHILE);
            eat(PIZQ);
            boolExp q;
            q.vddr = sem.nuevaEtiqueta();
            q.fls = l.sig;
            q = Q(q);
            eat(PDER);
            blockExp l1;
            l1.sig = sem.nuevaEtiqueta();
            sem.genCod(cuadrupla("label", "", "", l1.sig));
            L(l1);
            sem.genCod(cuadrupla("label", "", "", q.vddr));
            sem.genCod(cuadrupla("goto", "", "", l1.sig));
            break;
        }
        case DO: {
            eat(DO);
            blockExp l1;
            l1.sig = sem.nuevaEtiqueta();
            sem.genCod(cuadrupla("label", "", "", l1.sig));
            L(l1);
            eat(WHILE);
            eat(PIZQ);
            boolExp q;
            q.vddr = sem.nuevaEtiqueta();
            q.fls = l.sig;
            q = Q(q);
            eat(PDER);
            sem.genCod(cuadrupla("label", "", "", q.vddr));
            break;
        }
        case BREAK: {
            eat(BREAK);
            eat(PCOMA);
            sem.genCod(cuadrupla("goto", "", "", l.sig));
            break;
        }
        case LKEY: {
            blockExp j;
            j.sig = l.sig;
            J(j);
            break;
        }
        case RETURN: {
            eat(RETURN);
            LPP();
            break;
        }
        case SWITCH: {
            eat(SWITCH);
            eat(PIZQ);
            boolExp q;
            q = Q(q);
            eat(PDER);
            eat(LKEY);
            switchExp m;
            m.etqPrueba = sem.nuevaEtiqueta();
            sem.genCod(cuadrupla("goto", "", "", m.etqPrueba));
            m.sig = l.sig;
            m.id = q.dir;
            m = M(m);
            eat(RKEY);
            sem.genCod(cuadrupla("label", "", "", m.etqPrueba));
            sem.genCod(cuadrupla("label", "", "", m.prueba));
            break;
        }
        case PRINT: {
            eat(PRINT);
            boolExpH u;
            u = U(u);
            eat(PCOMA);
            sem.genCod(cuadrupla("print", "", "", u.valor));
            break;
        }
        case SCAN: {
            eat(SCAN);
            exp p = P();
            sem.genCod(cuadrupla("scan", "", "", p.dir));
            break;
        }
        default:
            error("Valor no esperado");
    }
}

void LP(boolExpH lp){
    if (equals(tokenActual,ELSE)){
        eat(ELSE);
        blockExp l;
        l.sig = lp.sig;
        L(l);
        sem.genCod(cuadrupla("goto","","",l.sig));
        sem.genCod(cuadrupla("label","","",lp.listaIndices.front()));
        int ultima = sem.codigo.reemplazarIndices(lp.listaIndices,sem.numEtq);
        sem.actualizaEtqt(ultima);
    }else{
        int ultima= sem.codigo.reemplazarIndices(lp.listaIndices,sem.numEtq++);
        sem.actualizaEtqt(ultima);
    }
}

void LPP(){
    if (equals(tokenActual,PCOMA)){
        listaRetorno.push_back(4); //void == 4
        sem.genCod(cuadrupla("return","","",""));
    }else{
        boolExpH u;
        u = U(u);
        listaRetorno.push_back(u.tipo);
        sem.genCod(cuadrupla("return","","",u.dir));
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

exp P(){
    exp p;
    string id = tokenActual->valor;
    eat(ID);
    p.base = id;
    p = PP(p);
    //Una vez concluída P' p.dir y p.tipo están asignados.
    return p;
}

exp PP(exp p){
    exp pp;
    pp.base = p.base;
    if (equals(tokenActual,CIZQ)){
        arrayExp aa;
        aa.base = pp.base;
        aa = AA(aa);
        pp.dir = aa.dir;
        pp.tipo = aa.tipo;
    }else {
        if (pilaTS.top().buscar(pp.base)){
            pp.dir = pp.base;
            pp.tipo = pilaTS.top().get_tipo(pp.dir);
        }else {
            error("ID no declarado.");
        }
    }
}

boolExp Q(boolExp q){
    boolExp qu;
    qu.vddr = q.vddr;
    qu.fls = q.fls;
    boolExp r;
    r.vddr = q.vddr;
    r.fls = sem.nuevoIndice();
    r = R(r);
    boolExpH qp;
    qp.vddr = qu.vddr;
    qp.fls = qu.fls;
    qp.tipoH = r.tipo;
    qp.listaIndices.push_back(r.fls);
    qp = QP(qp);
    qu.tipo = qp.tipo;
    sem.genCod(cuadrupla("label","","",r.fls));
    return qu;
}

boolExpH QP(boolExpH q){
    boolExpH qp;
    qp.vddr = q.vddr;
    qp.fls = q.fls;
    qp.listaIndices = q.listaIndices;
    if (equals(tokenActual,OR)){
        eat(OR);
        boolExp r;
        r.vddr = q.vddr;
        r.fls = sem.nuevoIndice();
        r = R(r);
        if (sem.equivalentes(q.tipoH,r.tipo)){
            boolExpH qp1;
            qp1.tipoH = r.tipo;
            qp1.vddr = qp.vddr;
            qp1.fls = qp.fls;
            qp1.listaIndices = qp.listaIndices;
            qp1.listaIndices.push_back(r.fls);
            qp1 = QP(qp1);
            qp.tipo = qp1.tipo;
            sem.genCod(cuadrupla("label","","",qp1.fls));
        }else{
            error("Tipos no compatibles");
        }
    }else{
        int ultimaEtq = sem.codigo.reemplazarIndices(qp.listaIndices, stoi(qp.fls.substr(1)));
        sem.actualizaEtqt(ultimaEtq);
        qp.tipo = 0; //int
    }
    return qp;
}

boolExp R(boolExp r){
    boolExp r1;
    r1.vddr = r.vddr;
    r1.fls = r.fls;
    boolExp s;
    s.vddr = sem.nuevoIndice();
    s.fls = r.fls;
    s = S(s);
    sem.genCod(cuadrupla("label","","",s.vddr));
    boolExpH rp;
    rp.tipoH = s.tipo;
    rp.vddr = r1.vddr;
    rp.fls = r1.fls;
    rp.listaIndices.push_back(s.vddr);
    rp = RP(rp);
    r1.tipo = rp.tipo;
    return r1;
}

boolExpH RP(boolExpH rparam){
    boolExpH rp;
    rp.vddr = rparam.vddr;
    rp.fls = rparam.fls;
    rp.tipoH = rparam.tipoH;
    rp.listaIndices = rparam.listaIndices;
    if (equals(tokenActual, AND)) {
        boolExp s;
        s.vddr = sem.nuevoIndice();
        s.fls = rp.fls;
        s = S(s);
        if (sem.equivalentes(rp.tipoH,s.tipo)){
            sem.genCod(cuadrupla("label","","",s.vddr));
            boolExpH rp1;
            rp1.tipoH = s.tipo;
            rp1.vddr = rp.vddr;
            rp1.fls = rp.fls;
            rp1.listaIndices = rp.listaIndices;
            rp1.listaIndices.push_back(s.vddr);
            rp1 = RP(rp1);
            rp.tipo = rp1.tipo;
        }else{
            error("Tipos no compatibles");
        }
    }else{
        int ultima = sem.codigo.reemplazarIndices(rp.listaIndices,stoi(rp.vddr.substr(1)));
        sem.actualizaEtqt(ultima);
        rp.tipo = 0; //Int
    }

}

void U() {
  exp u = exp();
  exp v = V();
  exp up = exp();
  up.tipo = v.tipo;
  up.dir = v.dir;
  up = UP(up);
  u.tipo = up.tipo;
  u.dir = up.dir;
  return u;
}

void UP(exp upparam) {
  exp up = exp();
  if (equals(tokenActual, PLUS)) {
    eat(PLUS);
    exp v = V();
    exp up1 = UP();
    if (sem.equivalentes(upparam.tipo, v.tipo)) {
      up1.tipo = sem.maximo(upparam.tipo, v.tipo);
      up1.dir = sem.nuevaTemporal();
      up.dir = up1.dir;
      string d1 = sem.ampliar(upparam.dir, upparam.tipo, up1.tipo);
      string d2 = sem.ampliar(v.dir, v.tipo, up1.tipo);
      sem.genCod(cuadrupla(upparam.dir, "=", d1, "+" + d2));
    }
    else {
      error("Tipos incompatibles");
    }
  }
  else if (equals(tokenActual, MINUS)) {
    eat(MINUS);
    exp v = V();
    exp up1 = UP();
    if (sem.equivalentes(upparam.tipo, v.tipo)) {
      up.tipo = up1.tipo;
      up.dir = up1.dir;
      up1.tipo = sem.maximo(upparam.tipo, v.tipo);
      up1.tipo = nuevaTemporal();
      string d1 = sem.ampliar(upparam.dir, upparam.tipo, up1.tipo);
      string d2 = sem.ampliar(v.dir, v.tipo, up1.tipo);
      genCod(cuadrupla(upparam.dir, "=", d1, "-" + d2));
    }
    else {
      error("Tipos incompatibles");
    }
  }
  else {
    up.tipo = upparam.tipo;
    up.dir = upparam.dir;
  }
  return up;
}

exp V() {
  exp v = exp();
  exp w = W();
  vp.tipo = w.tipo;
  vp.dir = w.dir;
  exp vp = VP(vp);
  v.tipo = vp.tipo;
  v.dir = vp.dir;
  return v;
}

exp VP(exp vpparam) {
  exp vp = exp();
  if (equals(tokenActual, MULT)) {
    eat(MULT);
    exp w = W();
    exp vp1 = VP();
    if (sem.equivalentes(vpparam.tipo, w.tipo)) {
      vp.tipo = vp1.tipo;
      vp.dir = vp1.dir;
      vp1.tipo = 0;
      vp1.dir = nuevaTemporal();
      genCod(cuadrupla(vp1.dir + "=", v.dir, "*", w.dir));
    }
    else {
      error("Tipos incompatibles");
    }
  }
  else if (equals(tokenActual, DIV)) {
    eat(DIV);
    exp w = W();
    exp vp1 = VP();
    if (sem.equivalentes(vpparam.tipo, w.tipo)) {
      vp.tipo = vp1.tipo;
      vp.dir = vp1.dir;
      vp1.tipo = 0;
      vp1.dir = nuevaTemporal();
      genCod(cuadrupla(vp1.dir + "=", v.dir, "/", w.dir));
    }
    else {
      error("Tipos incompatibles");
    }
  }
  else if (equals(tokenActual, MOD)) {
    eat(MOD);
    exp w = W();
    exp vp1 = VP();
    if (sem.equivalentes(vpparam.tipo, w.tipo)) {
      vp.tipo = vp1.tipo;
      vp.dir = vp1.dir;
      vp1.tipo = 0;
      vp1.dir = nuevaTemporal();
      genCod(cuadrupla(vp1.dir + "=", v.dir, "%", w.dir));
    }
    else {
      error("Tipos incompatibles");
    }
  }
  else {
    vp.tipo = vpparam.tipo;
    vp.dir = vpparam.dir;
  }
  return vp;
}

exp W() {
  exp w = exp();
  if (equals(tokenActual, NOT)) {
    eat(NOT);
    exp w1 = W();
    w.dir = sem.nuevaTemporal();
    w.tipo = w1.tipo;
    genCod(cuadrupla(w.dir + "=", "!", w1.dir, ""));
  }
  else if (equals(tokenActual, MINUS)) {
    eat(MINUS);
    exp w1 = W();
    w.dir = sem.nuevaTemporal();
    w.tipo = w1.tipo;
    genCod(cuadrupla(w.dir + "=", "-", w1.dir, ""));
  }
  else {
    exp x = X();
    w.dir = x.dir;
    w.tipo = x.tipo;
  }
  return w;
}

exp X() {
  exp x = exp();
  if (equals(tokenActual, PIZQ)) {
    eat(PIZQ);
    boolExp q = Q();
    eat(PDER);
    x.dir = q.dir;
    x.tipo = q.tipo;
  }
  else if (equals(tokenActual, ID)) {
    string id = tokenActual->valor;
    eat(ID);
    exp xp = exp();
    xp.base = id;
    xp = XP(xp);
    x.dir = xp.dir;
    x.tipo = xp.tipo;
  }
  else if (equals(tokenActual, NUM)) {
    int numval = stoi(tokenActual->valor);
    eat(NUM);
    x.dir = numval;
    x.tipo = tokenActual->tipo;
  }
  else if (equals(tokenActual, STR)) {
    string cadena = tokenActual->valor;
    eat(STR);
    cadenas.agregar(cadena);
    x.dir = cadenas.get_ultima_pos();
    x.tipo = 2; // Cadena
  }
  else if (equals(tokenActual, TRUE)) {
    eat(TRUE);
    x.dir = 1;
    x.tipo = 0;
  }
  else if (equals(tokenActual, FALSE)) {
    eat(FALSE);
    x.dir = 0;
    x.tipo = 0;
  }
  return x;
}

exp XP(exp xpparam) {
  exp xp = exp();
  if (equals(tokenActual, CIZQ)) {
    exp aa = exp();
    aa.base = xpparam.base;
    aa = AA(aa);
    xp.dir = sem.nuevaTemporal();
    xp.tipo = aa.tipo;
    sem.genCod(cuadrupla(xp.dir + "=", xp.base + "[", aa.dir, "]"));
  }
  else if (equals(tokenActual, PIZQ)) {
    eat(PIZQ);
    argExp y = Y();
    eat(PDER);
    if (pilats.fondo().buscar(xpparam.base)) {
      if (pilaTS.fondo().get_var(xpparam.base) == "func") {
        if (equivalentesListas(pilaTS.fondo().get_args(xpparam.base), y.lista)) {
          xp.tipo = pilaTS.top().get_tipo(xpparam.base);
          xp.dir = nuevaTemporal();
          genCod(cuadrupla(xp.dir + "=", "call " + xp.base, ",", to_string(y.lista.size())));
        }
        else {
          error("El número o tipo de parámetros no coincide");
        }
      }
      else {
        error("El id no es una funcion");
      }
    }
    else {
      error("El id no está declarado");
    }
  }
  else {
    xp.dir = xpparam.base;
    xp.tipo = pilaTS.top().get_tipo(xpparam.dir);
  }
  return xp;
}

argExp Y() {
  argExp y = argExp();
  if (equals(tokenActual, NOT)
    || equals(tokenActual, MINUS)
    || equals(tokenActual, PIZQ)
    || equals(tokenActual, ID)
    || equals(tokenActual, NUM)
    || equals(tokenActual, STR)
    || equals(tokenActual, TRUE)
    || equals(tokenActual, FALSE)) {
    argExp z = Z();
    y.lista = z.lista;
  }
  else {

  }
  return y;
}

void Z() {
  argExp zp = argExp();
  boolExp q = Q();
  argExp zp1 = ZP();
  zp.lista = zp1.lista;
  zp.lista.push_back(q.tipo);
  genCod(cuadrupla("param", "", "", to_string(q.dir)));
}

argExp ZP() {
  argExp zp = argExp();
  if (equals(tokenActual,COMA)) {
    eat(COMA);
    boolExp q = Q();
    argExp zp1 = ZP();
    zp.lista = zp1.lista;
    zp.lista.push_back(q.tipo);
    genCod(cuadrupla("param", "", "", to_string(q.dir)));
  }
  else {
    ; // lista vacia
  }
  return zp;
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
        if (pilaTT.top().get_nom(tipoTmp) == "array") { // array
          exp aap = exp();
          aap.tipo = pilaTT.top().get_base(tipoTmp);
          aap.dir = sem.nuevaTemporal();
          aap.dir = pilaTT.top().get_tam(aap.tipo);
          sem.genCod(cuadrupla(aaParam.dir + "=", q.dir, "*", aaParam.tam)));
          aap = AAP(aap);
          aa.dir = aap.dir;
          aa.tipo = aap.tipo;
        }
        else {
          error("El id no es un arreglo");
        }
      }
      else {
        error("El índice del arreglo debe ser un entero");
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
      if (pilaTT.top().get_nom(aapParam.tipo) == "array") { // array
        arrayExp aap1 = arrayExp();
        aap1.tipo = pilaTT.top().get_base(aapParam.tipo);
        string dirTmp = sem.nuevaTemporal();
        aap1.dir = sem.nuevaTemporal();
        aap1.tam = pilaTT.top().get_tam(aapParam.tipo);
        sem.genCod(cuadrupla("dirTmp =", q.dir, "*", to_string(aap1.tam))); //TODO
        sem.genCod(cuadrupla(aap1.dir, "=", "", to_string(aapParam + dirTmp))); //TODO
        aap1 = AAP(aap1);
        aap.dir = aap1.dir;
        aap.tipo = aap1.tipo;
      }
      else {
        error("El id no es un arreglo");
      }
    }
    else {
      error("El índice del arreglo debe ser un entero");
    }
  }
  else {
    aap.dir = aapParam.dir;
    aap.tipo = aapParam.tipo;
  }
  return aap;
}

bool equivalentesListas(list<string> l1, list<string> l2) {
  return l1 == l2;
}

tablasimbolos fondo(stack<tablasimbolos> pila) {
  list<tablasimbolos> aux;
  while (!pila.empty()) {
    aux.push_back(pila.top());
    pila.pop();
  }
  tablasimbolos fondo = aux.front();
  for(tablasimbolos tabla : aux) {
    pila.push(tabla);
  }
  return fondo;
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
