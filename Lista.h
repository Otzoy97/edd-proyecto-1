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
        string Dot(const string &padre);
    private:
        NodoL<Imagen*> *primero;
        NodoL<Imagen*> *ultimo;
        int largo;
        string Recorrer(NodoL<Imagen> *raiz);
};
/**
 * Agrega un nuevo apuntador de tipo Imagen
 * @param dato
 */
void Lista::Agregar(Imagen &dato){
    NodoL<Imagen*> nuevo = new NodoL(dato);
    if (primero != NULL){
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    } else {
        primero = nuevo;
        primero->siguiente = ultimo;
        primero = ultimo;
    }
}
/**
 * Modifica un apuntador de tipo Imagen
 * @param id
 * @param nuevo
 * @return 
 */
bool Lista::Modificar(int id, Imagen &nuevo){
    NodoL<Imagen*> temp = primero;
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
    NodoL<Imagen*> temp = primero;
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
    NodoL<Imagen*> aux;
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
    stringstream retorno;
    retorno << "p" << padre << " -> p" << primero << endl << Recorrer(primero);
    return retorno.str();
}
/**
 * 
 * @param raiz
 * @return 
 */
string Lista::Recorrer(NodoL<Imagen>* raiz){
    stringstream retorno;
    if(raiz!=NULL){
        retorno << "p" << raiz << "[label=\"Img" << raiz->Dato()->Id() << "\"];" << endl;
        if (raiz->siguiente != NULL)
            retorno << "p" << raiz << "-> p" << raiz->siguiente << endl;
        retorno << Recorrer(raiz->siguiente);
    }
    return retorno.str();
}
#endif /* LISTA_H */

