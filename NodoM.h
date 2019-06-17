/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodoM.h
 * Author: otzoy
 *
 * Created on 15 de junio de 2019, 08:41 PM
 */

#ifndef NODOM_H
#define NODOM_H
#include "INodo.h" 

template <class T> class NodoM : public INodo{
    public:
        NodoM *arriba;
        NodoM *abajo;
        NodoM *anterior;
        NodoM *siguiente;
        NodoM(bool esCabecera_) : arriba(0), abajo(0), anterior(0), siguiente(0), esCabecera(esCabecera_), fila(0), col(0) {}
        NodoM() : arriba(0), abajo(0), anterior(0), siguiente(0), dato(0), esCabecera(0), fila(0), col(0) {}
        NodoM(int fila_, int col_, T dato_) : fila(fila_), col(col_), dato(dato_), esCabecera(false) {}
        int fila, col;
        T Dato() {return dato;}
        void Dato(T dato_) { dato = dato_; }
        bool EsCabecera(){ return esCabecera; }
    private:      
        bool esCabecera;
        T dato;
        
};


#endif /* NODOM_H */

