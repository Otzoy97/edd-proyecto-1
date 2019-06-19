/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodoL.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:08 AM
 */

#ifndef NODOL_H
#define NODOL_H
#include "INodo.h"

template <class T> class NodoL : public INodo{
    public:
        NodoL* anterior;
        NodoL* siguiente;
        NodoL() : anterior(0), siguiente(0), dato(0){}
        NodoL(T dato_) : anterior(0), siguiente(0), dato(dato_){}
        T Dato(){return dato;}
    private:
        T dato;
};


#endif /* NODOL_H */

