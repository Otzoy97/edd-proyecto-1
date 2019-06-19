/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cola.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:38 AM
 */

#ifndef COLA_H
#define COLA_H
#include "NodoL.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class Cola{
    public:
        Cola() : primero(0), ultimo(0), largo(0) {}
        void AgregarAlFinal(T dato);
        T Desencolar();
        int Largo() {return largo;}
        //string Dot();
        T Ver();
        NodoL<T> *Iterador(){ return primero;}
    private:
        //string Recorrer(NodoL<T> *nodito);
        NodoL<T> *primero;
        NodoL<T> *ultimo;
        int largo;
};
/**
 * Devuelve el primer dato de lalista
 * @return 
 */
template <class T> T Cola<T>::Desencolar(){
    T dato = primero->Dato();
    NodoL<T> *temp = primero;
    primero = temp->siguiente;
    delete temp;
    largo--;
    return dato;
}
/**
 * Encola un nuevo dato
 * @param dato
 */
template <class T> void Cola<T>::AgregarAlFinal(T dato){
    NodoL<T> *nuevo = new NodoL<T>(dato);
    if(primero!=NULL){
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
        largo++;
    } else {
        primero = nuevo;
        primero->siguiente = ultimo;
        ultimo = primero;
        largo++;
    }
}
/**
 * Devuelve el dato del primero nodo
 * @return 
 */
template <class T> T Cola<T>::Ver(){
    return primero->Dato();
}
/*
template <class T> string Cola<T>::Dot(){
    stringstream retorno;
    retorno << "subgraph C" << this << "{" <<  endl <<  Recorrer(primero) << "}" << endl;
    return retorno.str();
}

template <class T> string Cola<T>::Recorrer(NodoL<T>* nodito){
    stringstream retorno;
    if(nodito!=NULL){
        retorno << "p" << nodito << "[label=\"" << "\"];" << endl;
        if (nodito->siguiente!=NULL)
            retorno << "p" << nodito<< "-> p" << nodito->siguiente << endl;
        retorno << Recorrer(nodito->siguiente);
    }
    return retorno.str();
}*/

#endif /* COLA_H */

