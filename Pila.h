/* 
 * File:   Pila.h
 * Author: sorem
 *
 * Created on 18 de junio de 2019, 02:39 PM
 */

#ifndef PILA_H
#define	PILA_H
#include "NodoL.h" 
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class Pila{
    public:
        void Apilar(T dato);
        T Ver();
        T Desapilar();
        bool EsVacio();
        int Largo() {return largo;}
    private:
        int largo = 0;
        NodoL<T> *inicio;
};

template <class T> bool Pila<T>::EsVacio(){
    return inicio == NULL;
}

template <class T> T Pila<T>::Ver(){
    return inicio->Dato();
}

template <class T> T Pila<T>::Desapilar(){
    T dato = inicio->Dato();
    NodoL<T> *temp = inicio;
    inicio = temp->siguiente;
    delete temp;
    largo--;
    return dato;
}

template <class T> void Pila<T>::Apilar(T dato){
    NodoL<T> *nuevo = new NodoL<T>(dato);
    if (!EsVacio()){
        nuevo->siguiente = inicio;
        inicio = nuevo;
        largo++;
    } else {
        inicio = nuevo;
        largo++;
    }
}

#endif	/* PILA_H */

