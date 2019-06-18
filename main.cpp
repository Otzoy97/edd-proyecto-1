/* 
 * File:   main.cpp
 * Author: sorem
 *
 * Created on 17 de junio de 2019, 01:16 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "Capa.h"
#include "Usuario.h"
#include "Imagen.h"

#include "ArbolAVL.h"
#include "ArbolBB.h"

#include "Cola.h"
#include "ListaDobleCircular.h"

#include "Matriz.h"
#include "NodoM.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    /*int i = 0;
    NodoM<string> *a = new NodoM<string>(0,0,"A");
    NodoM<string> *b = new NodoM<string>(0,0,"A");
    bool c = a->col == b->col;
    bool d = a->col == i;
    bool e = b->col == i;
    bool f = b->col == i == a->col;
    bool g = d && e;
    cout << c << endl << d << endl << e << endl <<f << endl << g << endl;
    */
    
    
    
    
    Matriz *matriz = new Matriz();
    matriz->AgregarEn(1,1,"A");
    
    matriz->AgregarEn(2,3,"B");
    matriz->AgregarEn(2,3,"E");
    matriz->AgregarEn(0,1,"C");
    matriz->AgregarEn(1,5,"D");
    matriz->AgregarEn(2,1, "T");
    matriz->AgregarEn(2,5,"G");
    matriz->AgregarEn(2,5,"W");
    matriz->AgregarEn(0,5,"G");
    matriz->AgregarEn(1,0,"K");
    matriz->AgregarEn(0,0,"X");
    matriz->AgregarEn(2,0,"Y");
    matriz->AgregarEn(0,0,"L");
    matriz->AgregarEn(0,0,"ZZ");

    cout << matriz->Dot();
}

