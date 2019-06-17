/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaDobleCircular.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:23 AM
 */

#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H
#include "NodoL.h"
#include "Imagen.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

template <class T> class ListaDobleCircular{
    public:
        ListaDobleCircular(): primero(0), ultimo(0), largo(0) {}
        void AgregarAlFinal(Imagen dato);
        int Largo(){return largo;}
        string Dot(const string &nombre);
    private:
        NodoL<Imagen> *primero;
        NodoL<Imagen> *ultimo;
        int largo;
};
/**
 * Agrega una nueva imagen al final de la lista
 * @param dato
 */
template <class T> void ListaDobleCircular<T>::AgregarAlFinal(Imagen dato){
    NodoL<Imagen> *nuevo = new NodoL<Imagen>(dato);
    if(primero!=NULL){
        nuevo->siguiente = primero;
        nuevo->anterior = ultimo;
        primero->anterior = nuevo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    } else {
        primero = nuevo;
        ultimo = primero;
    }
}
/**
 * Genera el texto que se utilizará para generar el gráfico
 * @param nombre
 * @return 
 */
template <class T> string ListaDobleCircular<T>::Dot(const string& nombre){
    stringstream str;
    return str.str();
}

#endif /* LISTADOBLECIRCULAR_H */

