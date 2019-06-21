/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodoB.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:11 AM
 */

#ifndef NODOB_H
#define NODOB_H
#include "INodo.h"

template <class T> class NodoB : public INodo{
    public:
        NodoB() : izq(0), der(0), dato(0){}
        NodoB(T dato_) : izq(0), der(0), dato(dato_) {}
        NodoB *izq;
        NodoB *der;
        T Dato() {return dato;}
        T* DatoPtr() {return &dato;}
    private:
        T dato;
};


#endif /* NODOB_H */

