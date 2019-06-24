/* 
 * File:   main.cpp
 * Author: sorem
 *
 * Created on 17 de junio de 2019, 01:16 PM
 */

#include "NodoB.h"

#include <cstdlib>
#include <stdlib.h>
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
#include "ListaDoble.h"

#include "Matriz.h"
#include "NodoM.h"
#include "Lista.h"

#include "Pila.h"


using namespace std;

bool LeerCapa(string const &);
bool LeerUsuario(string const &);
bool LeerImagen(string const &);
void EscribirArchivo(string const &, string const &);
void Graphviz(string const&);

ArbolB *arbolCapas = new ArbolB();
ArbolAVL *arbolUsuarios = new ArbolAVL();
Lista *listaImagenes = new Lista();


/*
 * 
 */
int main(int argc, char** argv) {
    /*ListaDoble *l = new ListaDoble();
    for(int i = 0 ; i< 0;i++){
        l->AgregarAlFinal(i);
    }
    l->Eliminar(0);
    l->Eliminar(1);
    l->Eliminar(9);
    l->Eliminar(5);
    l->AgregarAlFinal(10);
    l->AgregarAlFinal(10);        
    cout <<l->Dot("a") << endl;*/
    LeerCapa("/home/sorem/capas");
    LeerImagen("/home/sorem/imagenes");
    LeerUsuario("/home/sorem/Descargas/usuarios.txt");
    stringstream str;
    str << "digraph G{" << listaImagenes->Dot() << listaImagenes->ListarImagenes() << "}" <<endl;
    EscribirArchivo("img",str.str());
    Graphviz("img");
    str.str(string());
    str << "digraph G{" << arbolCapas->Dot() << "}" << endl;
    EscribirArchivo("capasTree", str.str());
    Graphviz("capasTree");
    str.str(string());
    EscribirArchivo("userTree", arbolUsuarios->Dot());
    Graphviz("userTree");
}

bool LeerCapa(string const &url){
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
        return 0;
    }
    //Procede a leer el archivo
    while(getline(archivoEntrada,linea)){
        for(int i = 0 ; i < linea.length() ; i++){
            if(!pila->EsVacio()){
                //La pila no está vacía y llego a un } 
                if (linea.at(i) == '}'){
                    cout << "No se ha leído correctamente el archivo -> " << lineaArchivo << endl;
                    return 0;
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
                } else if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) {
                    //Espacio, saltos de linea, tabulaciones
                    continue;
                } else {
                    cout << "No se ha leído correctamente el archivo -> " << lineaArchivo << endl;
                    return 0;
                }
            } else {
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) 
                    continue;
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
    return 1;
}

bool LeerImagen(string const &url){
    //Almacena el archivo de entrada
    ifstream archivoEntrada;
    //Alojará una línea leída del archivo
    string linea = "";
    int lineaArchivo = 0;
    //Automat a pila
    Pila<int> *pila = new Pila<int>();
    Imagen img;
    NodoB<Capa> *temp;
    //Abre el archivo
    archivoEntrada.open(url);
    //Verifica que exista el archivo
    if(!archivoEntrada){
        cout << "No se pudo abrir el archivo " << url << endl << "¿Estará mal escrito?" << endl;
        return 0;
    }
    //Procede a leer el archivo y guradar datos
    while(getline(archivoEntrada,linea)){
        for(int i = 0 ;  i < linea.length() ; i++){
            if(!pila->EsVacio()){
                // } , 
                if (linea.at(i) == '}'){
                    do{
                        //Procede a buscar el id en el arbolB
                        temp = arbolCapas->Buscar(pila->Ver());
                        if(!temp){
                            cout << "La capa " << pila->Desapilar() << " no existe en memoria. Línea " << lineaArchivo << endl;
                            continue;
                        }
                        //Existe el nodo, procede a guardar el apuntador 
                        img.Capas()->AgregarAlInicio(temp->DatoPtr());
                        //Despila el nodo
                        pila->Desapilar();
                    }while(!pila->EsVacio());
                    listaImagenes->Agregar(img);
                    continue;
                }
                //{ ,(conteo de pila == 1), 0
                if(linea.at(i) == '{' && pila->Largo() == 1){
                    img = Imagen(pila->Desapilar());
                    continue;
                }
                // "," , ( largo >= 1) , 0
                if (linea.at(i) == ',' && pila->Largo() >= 1){
                    pila->Apilar(0);
                    continue;
                }
                //Concatena numeros
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(pila->Desapilar()*10 + (linea.at(i) - '0') );
                    continue;
                }
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) {
                    //Espacio, saltos de linea, tabulaciones
                    continue;
                }
            } else {
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) 
                    continue;
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(linea.at(i) - '0');
                    continue;
                }
                if (linea.at(i) == '{'){
                    //La pila está vacía y encontró un {
                    cout << "No se ha leído correctamente el archivo -> " << lineaArchivo << endl;
                    return 0;
                }
            }
        }
        lineaArchivo++;
    }
    return 1;
}

bool LeerUsuario(string const &url){
    //Almacena el archivo de entrada
    ifstream archivoEntrada;
    //Alojará una línea leída del archivo
    string linea ="";
    int lineaArchivo = 0;
    string nombreUsuario = "";
    //ListaDobleCircular *listad;
    //Automata a pila
    Pila<int> *pila = new Pila<int>();
    //Abre el archivo
    archivoEntrada.open(url);
    //Verifica que exista el archivo
    if (!archivoEntrada){
        cout << "No se pudo abrir el archivo " << url << endl << "¿Estará mal escrito?" << endl;
        return 0;
    }
    //Procede a leer el archivo y guardar datos
    while(getline(archivoEntrada, linea)){
        for(int i = 0 ; i < linea.length() ; i++){
            if(!pila->EsVacio()){
                if(linea.at(i) >= '0' && linea.at(i) <= '9'){
                    pila->Apilar(pila->Desapilar()*10 + (linea.at(i) - '0') );
                    continue;
                }
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) 
                    continue;
                if (linea.at(i) == ','){
                    pila->Apilar(0);
                    continue;
                }
                if (linea.at(i) == ';' && nombreUsuario.length() > 0){
                    ListaDoble *lista = new ListaDoble();
                    //Fin de la línea, se procede a leer el contenido de la pila y meterlo a la lista del usuario
                    while(!pila->EsVacio()){
                        //Busca en la lista de imagenes el id
                        if (listaImagenes->Existe(pila->Ver()))
                            lista->AgregarAlFinal(pila->Desapilar());
                        else 
                            cout << "La imagen " << pila->Desapilar() << " no existe. No se puede agregar a " << nombreUsuario << ". Linea " << lineaArchivo << endl;
                    }
                    Usuario user(nombreUsuario,lista);
                    //Agrega el usuario al arbol
                    arbolUsuarios->Agregar(user);
                    nombreUsuario = "";
                    continue;
                }
            } else {
                //Continua leyendo alguna cadena, [A-Za-z0-9], -1, E;
                if ( ((linea.at(i) >= 'a' && linea.at(i) <= 'z') || (linea.at(i) >= 'A' && linea.at(i) <= 'Z') || (linea.at(i) >= '0' && linea.at(i) <= '9'))){
                    nombreUsuario += linea.at(i);
                    continue;
                }
                if (linea.at(i) == 32 || linea.at(i) == 9 || linea.at(i) == 10 || linea.at(i) == 11) 
                    continue;
                if (linea.at(i) == ':'){
                    pila->Apilar(0);
                    continue;
                }
                if (linea.at(i) == ';' && nombreUsuario.length() > 0 && pila->Ver() == 0 ){
                    ListaDoble *lista = new ListaDoble();
                    Usuario user(nombreUsuario,lista);
                    arbolUsuarios->Agregar(user);
                    nombreUsuario = "";
                    continue;
                }
            }
        }
        lineaArchivo++;
    }
        
}

void EscribirArchivo(string const &nombre, string const &contenido){
    ofstream archivo;
    archivo.open(nombre);
    archivo << contenido;
    archivo.close();
}

void Graphviz(string const &nombre){
    string cmd = "dot -Tpng "  + nombre + " -o " + nombre + ".png";
    string cmd_d = "eog " + nombre + ".png";
    system(cmd.c_str());
    system(cmd_d.c_str());
}
