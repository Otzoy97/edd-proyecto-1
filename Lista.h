/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lista.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 06:23 PM
 */

#ifndef LISTA_H
#define LISTA_H

#include <string>
#include <sstream>
#include <iostream>
#include "Imagen.h"
#include "NodoL.h"

using namespace std;

class Lista {
    public:
        Lista() : primero(0), ultimo(0), largo(0) {}
        int Largo();
        void Agregar(Imagen &dato);
        bool Eliminar(int id);
        bool Modificar(int id, Imagen &nuevo);
        string Dot();
    private:
        NodoL<Imagen> *primero;
        NodoL<Imagen> *ultimo;
        int largo;
        //string Recorrer(NodoL<Imagen> *raiz);
};
/**
 * Agrega un nuevo apuntador de tipo Imagen
 * @param dato
 */
void Lista::Agregar(Imagen dato){
    NodoL<Imagen> nuevo = new NodoL(dato);
    if (primero != NULL){
        primero = nuevo;
        ultimo = primero;
    } else {
        nuevo->siguiente = primero;
        nuevo->anterior = ultimo;
        primero->anterior = nuevo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
}
/**
 * Modifica un apuntador de tipo Imagen
 * @param id
 * @param nuevo
 * @return 
 */
bool Lista::Modificar(int id, Imagen &nuevo){
    NodoL<Imagen> temp = primero;
    while(temp!=NULL){
        if(temp->Dato()->Id() == id){
            temp->Dato() = nuevo;
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}
/**
 * Elimina un apuntador de tipo Imagen
 * @param id
 */
bool Lista::Eliminar(int id){
    NodoL<Imagen> temp = primero;
    if(temp->Dato()->Id() == id){
        if(temp->siguiente != NULL){
            primero = temp->siguiente;
            temp->siguiente->anterior = NULL;
        } else {
            primero = NULL;
            ultimo = NULL;
        }
        delete temp;
        return true;
    }
    NodoL<Imagen> aux;
    while(temp->siguiente!=NULL){
        aux = temp->siguiente;
        if(aux->Dato()->Id() == id){
            temp->siguiente = aux->siguiente;
            break;
        }
        temp = temp->siguiente;
    }
    delete aux;
    delete temp;
    return false;
}
/**
 * 
 * @return 
 */
string Lista::Dot(const string &padre){
    if (!primero)
        return string();
    stringstream retorno;
    retorno << "subgraph cluster" << this << "{" << endl;
    retorno << "color=white;"<< endl;
    retorno << "{rank = same ;";
    NodoL<Imagen> *aux = this->primero;
    do{
        retorno << aux->Dato() << "->";
        aux->siguiente;
    }while(aux!=this->primero);
    do{
        retorno << aux->Dato();
        if(aux!=this->primero)
            retorno << "->";
        aux->anterior;
    }while(aux!=this->primero);
    retorno << "}" << endl << "}" << endl;
    return retorno.str();
}
/**
 * 
 * @param raiz
 * @return 
 */
string Lista::Recorrer(NodoL<Imagen>* raiz){
    //stringstream retorno;
    //if(raiz!=NULL){
    //    retorno << "p" << raiz->Dato() << "[label=\"Imagen " << raiz->Dato().Id() <<  "\"; group = " << raiz->Dato().Id() <<"];" << endl;
    //    if (raiz->siguiente != NULL){
    //        NodoL<Imagen> *aux = raiz->siguiente;
    //        retorno << "p" << raiz->Dato() << "-> p" << aux->Dato() << endl;
    //    }
    //    retorno << Recorrer(raiz->siguiente);
    //}
    return string(); //retorno.str();
}
#endif /* LISTA_H */

