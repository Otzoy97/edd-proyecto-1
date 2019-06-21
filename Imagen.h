/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Imagen.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:52 AM
 */

#ifndef IMAGEN_H
#define IMAGEN_H

//#include "Matriz.h"
#include "Capa.h"
#include "Cola.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Imagen {
public:
    Imagen(const int &id_);
    int Id();
    Cola<Capa*> *Capas();
    string Renderizar();
    string Dot(const string &padre);
    string DotCapa();
private:
    int id;
    string Recorrer(NodoL<Capa*> nodito);
    Cola<Capa*> *colaCapas;
};
string Imagen::DotCapa(){
    stringstream str;
    str << "subgraph clusterPC" << this << "{" << endl << "color=white"<< endl;
    NodoL<Capa*> *iterador = colaCapas->Iterador();
    while(iterador){
        str << "p" << iterador << "-> \"pCapa_" << iterador->Dato()->id  << "x\":f1" << endl;
        iterador = iterador->siguiente;
    }
    str << "}";
    return str.str();
}
/**
 * Recupera el dot de la cola de capas
 * @param ref nombre del nodo imagen
 * @param group
 * @return 
 */
string Imagen::Dot(const string &padre){
    if (!colaCapas->Largo())
        return string();
    stringstream retorno;
    retorno << "subgraph cluster" << this << "{" << endl << "color=white" << endl;
    NodoL<Capa*> *iterador = colaCapas->Iterador();
    retorno << "p" << padre << "[label=\"Imagen " << this->id << "\"; group = " << this->id + 1 << ";  shape=box];" <<  endl;
    retorno << "p" << padre << " -> p" <<  iterador/*->Dato()->Capa_*/ << endl;
    while(iterador){
        retorno << "p" << iterador/*->Dato()->Capa_*/ << "[label=\"Capa " << iterador->Dato()->id << "\"; group = "<< this->id + 1 <<"; style=rounded; shape=box];" << endl;
        if (iterador->siguiente){
            NodoL<Capa*> *aux = iterador->siguiente;
            retorno << "p" << iterador/*->Dato()->Capa_*/ << "-> p"  << aux/*->Dato()->Capa_*/ << endl;
        }
        iterador = iterador->siguiente;
    }
    retorno << "}" << endl;
    return retorno.str();
}

/**
 * Renderiza las capas de la imagen
 * @return 
 */
string Imagen::Renderizar(){
    Matriz *imagen = new Matriz();
    //Recupera el inicio de la cola
    NodoL<Capa*> *pivCola = colaCapas->Iterador();
    //Recorre la lista
    while(pivCola){
        //Vuelca las capas almacenadas en la cola
        imagen->Volcar(pivCola->Dato()->Capa_);
        //Se mueve al siguiente nodo
        pivCola = pivCola->siguiente;
    }
    //Retorna un texto dot
    return imagen->Pintar();
}
/**
 * Recupera la cola de capas
 * @return 
 */
Cola<Capa*> *Imagen::Capas(){
    return colaCapas;
}
/**
 * Recupera el id de la imagen
 * @return 
 */
int Imagen::Id(){
    return id;
}
/**
 * Constructor
 * @param id_
 */
Imagen::Imagen(const int& id_){
    id = id_;
    colaCapas = new Cola<Capa*>();
}

#endif /* IMAGEN_H */

