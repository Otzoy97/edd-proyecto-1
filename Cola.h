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
        void Encolar(T dato);
        T Desencolar();
        int Largo() {return largo;}
        string Dot(const string &nombre);
        T Ver();
    private:
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
template <class T> void Cola<T>::Encolar(T dato){
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
/**
 * 
 * @param nombre
 * @return 
 */
template <class T> string Cola<T>::Dot(const string &nombre){
    stringstream str;
    return str.str();
};

#endif /* COLA_H */

