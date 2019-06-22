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
#include "Lista.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {        
    Lista *l = new Lista();
    ArbolB *t = new ArbolB();
    for(int i = 0; i < 10; i++){
        Imagen img(i);
        for (int j = 0; j < 10; j++){
            Matriz *mat = new Matriz();
            for(int k = 0; k < 10; k++){
                for(int l = 0; l< 10 ; l++){
                    if(l%2 == 0)
                        mat->AgregarEn(k,l,"white");
                    else 
                        mat->AgregarEn(k,l,"black");
                }
            }
            Capa *cap = new Capa(mat,rand()%2+j);
            t->Agregar(*cap);
            img.Capas()->AgregarAlFinal(cap);
        }
        l->Agregar(img);
    }
    cout << l->ImagenDot(3);
    //cout << l->ListarImagenes();
    //cout << l->Dot();
    //cout << l->Renderizar(0);
    cout << endl << t->Dot() << endl;
    //cout << l->
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
    /*Matriz *matriz = new Matriz();
    matriz->AgregarEn(0,0,"red");
    matriz->AgregarEn(0,1,"yellow");
    matriz->AgregarEn(1,0,"blue");
    matriz->AgregarEn(1,1,"green");
    Matriz *vaciado = new Matriz();
    
    Matriz *mmatriz = new Matriz();
    mmatriz->AgregarEn(0,0,"black");
    mmatriz->AgregarEn(0,2,"yellow");
    mmatriz->AgregarEn(2,0,"blue");
    mmatriz->AgregarEn(2,2,"green");
    
    vaciado->Volcar(matriz);
    vaciado->Volcar(mmatriz);
    


    cout << matriz->Dot() << endl;
    cout << matriz->Pintar() << endl;
    
    cout << vaciado->Dot() << endl;
    cout << vaciado->Pintar() << endl;*/
    
    //Imagen img(0);// = new Imagen(0) ;
    
    
    //A/rbolB *d = new ArbolB();
    ///for(int i = 0 ; i < 10; i++){
////        Capa cap();
//        d->Agregar()
    //}
        
    //d->
    
}

