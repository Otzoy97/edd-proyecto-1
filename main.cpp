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
#include <fstream>
#include <bits/stdc++.h>

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

#include "Pila.h"


using namespace std;

void LeerCapa(string const &);
void LeerUsuario(string const &);
void LeerImagen(string const &);

ArbolB *arbolCapas = new ArbolB();

/*
 * 
 */
int main(int argc, char** argv) {  
    LeerCapa("/home/sorem/Descargas/capas(copia).txt");
    cout << arbolCapas->EsVacia() << endl;
    if (!arbolCapas->EsVacia()) {
        //cout <<arbolCapas->DotEspejo() << endl ;
        //cout << arbolCapas->Dot() << endl;
        cout << arbolCapas->Buscar(4)->Dato().Capa_->Pintar() << endl;
    }
    /*
    regex r("((\\w)|([[:space:]]))*");
    string a = " kfghj \n \n dfghj ";
    if (regex_match(a,r))
        cout << "sí";*/
    //string archivo;
    //getline (cin, archivo);
    
    //archvi.LeerCapa("/home/sorem/Descargas/capas(copia).txt");
    
    /*     
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

void LeerCapa(string const &url){
    //Almacea el archivo de entrada
    ifstream archivoEntrada;
    //Alojará una línea leída del archivo
    string linea;
    string color = "";
    int lineaArchivo = 0;
    //Automata a pila
    Pila<int> *pila = new Pila<int>();
    Capa cap = Capa();
    //Abre el archivo
    archivoEntrada.open(url);
    //Verifica  que exista el archivo
    if(!archivoEntrada){
        cout << "No se pudo abrir el archivo " << url << endl << "¿Estará mal escrito?" << endl;
        return;
    }
    //Procede a leer el archivo
    while(getline(archivoEntrada,linea)){
        for(int i = 0 ; i < linea.length() ; i++){
            if(!pila->EsVacio()){
                //La pila no está vacía y llego a un } 
                if (linea.at(i) == '}'){
                    cout << "No se ha leído correctamente el archivo -> " << lineaArchivo << endl;
                    return;
                }
                //Comienza a leer alguna cadena, [#A-Za-z] , 0, -1
                if ( (linea.at(i) == '#' ||  (linea.at(i) >= 'a' && linea.at(i) <= 'z') || (linea.at(i) >= 'A' && linea.at(i) <= 'Z')) && pila->Ver() == 0){
                    color += linea.at(i);
                    pila->Apilar(pila->Desapilar()-1);
                    continue;
                }
                //Continua leyendo alguna cadena, [A-Za-z0-9], -1, E;
                if ( ((linea.at(i) >= 'a' && linea.at(i) <= 'z') || (linea.at(i) >= 'A' && linea.at(i) <= 'Z') || (linea.at(i) >= '0' && linea.at(i) <= '9')) && pila->Ver() == -1){
                    color += linea.at(i);
                    continue;
                }
                //{ ,(conteo de pila == 1), Zo
                if(linea.at(i) == '{' && pila->Largo() == 1){
                    cap.id = pila->Desapilar();
                    cap.Capa_ = new Matriz();
                    continue;
                }
                // "," , ( 1 <= conteo de pila <= 2 ) , 0
                if (linea.at(i) == ',' && pila->Largo() >= 1 && pila->Largo() <= 2){
                    pila->Apilar(0);
                    continue;
                }
                //Concatena numeros
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(pila->Desapilar()*10 + (linea.at(i) - '0') );
                    continue;
                }
                // ";" , -1 , Zo;
                if (linea.at(i) == ';' && pila->Largo() == 3 && pila->Desapilar() == -1){
                    cap.Capa_->AgregarEn(pila->Desapilar(), pila->Desapilar(), color);
                    color = "";
                    continue;
                } else {
                    cout << "No se ha leído correctamente el archivo -> " << lineaArchivo << endl;
                    return;
                }
            } else {
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(linea.at(i) - '0');
                    continue;
                }
                if (linea.at(i) == '}'){
                    arbolCapas->Agregar(cap);
                    cap = Capa();
                    continue;
                }
            }
        }
        lineaArchivo++;
    }
}

