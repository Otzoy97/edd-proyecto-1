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
        NodoB() : izq(0), der(0), dato(0), altura(0) {}
        NodoB(T dato_) : izq(0), der(0), dato(dato_), altura(0) {}
        NodoB(T dato_, int altura_) : izq(0), der(0), dato(dato_), altura(altura_) {}
        NodoB *izq;
        NodoB *der;
        T Dato() {return dato;}
        T* DatoPtr() {return &dato;}
        void Dato(T dato_) { dato = dato_; }
        int Altura() {return altura;}
        void Altura(int altura_) {altura = altura_;}
    private:
        int altura;
        T dato;
};


#endif /* NODOB_H */

