/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArbolB.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:55 PM
 */

#ifndef ARBOLB_H
#define ARBOLB_H
#include <string>
#include <sstream>
#include <iostream>
#include "NodoB.h"
#include "Capa.h"

using namespace std;

class ArbolB{
    public:
        ArbolB() : raiz(0) {}
        void Agregar(Capa dato);
        NodoB<Capa> *Buscar(int id);
        void Eliminar(int id);
        bool EsVacia() { return raiz == NULL; }
    private:
        NodoB<Capa> *raiz;
        void Agregar(NodoB<Capa> *raiz, Capa dato);
        NodoB<Capa> *Buscar(NodoB<Capa> *raiz, int id);
        void Eliminar(NodoB<Capa> *raiz, int id);
        void Reemplazar(NodoB<Capa> *raiz, NodoB<Capa> *aux);
};
/**
 * 
 * @param dato
 */
void ArbolB::Agregar(Capa dato){
    Agregar(raiz, dato);
}
/**
 * 
 * @param id
 * @return 
 */
NodoB<Capa>* ArbolB::Buscar(int id){
    return Buscar(raiz, id);
}
/**
 * 
 * @param id
 */
void ArbolB::Eliminar(int id){
    if(!EsVacia()){
        Eliminar(raiz, id);
    }
}
/**
 * 
 * @param raiz
 * @param id
 * @return 
 */
void ArbolB::Agregar(NodoB<Capa>* root, Capa dato){
    if(root == NULL){
        NodoB<Capa> *root = new NodoB<Capa>(dato);
    } else if (dato.Id() <= root->Dato().Id()){
        if(root->izq != NULL)
            Agregar(root->izq, dato);
        else
            root->izq = new NodoB<Capa>(dato);
    } else if (dato.Id() > root->Dato().Id()){
        if(root->der != NULL)
            Agregar(root->der, dato);
        else 
            root->der = new NodoB<Capa>(dato);
    }
}
/**
 * 
 * @param raiz
 * @param id
 * @return 
 */
NodoB<Capa> *ArbolB::Buscar(NodoB<Capa>* root, int id){
    if(root == NULL)
        return NULL;
    if (root->Dato().Id() == id)
        return root;
    if (root->Dato().Id() < id)
        return Buscar(root->der, id);
    else
        return Buscar(root->izq, id);
}
/**
 * 
 * @param raiz
 * @param id
 * @return 
 */
void ArbolB::Eliminar(NodoB<Capa>* root, int id){
    if (root == NULL)
        return;
    if (root->Dato().Id() < id)
        Eliminar(root->der, id);
    else if (root->Dato().Id() > id)
        Eliminar(root->izq, id);
    else if(root->Dato().Id() == id){
        NodoB<Capa> *aux = root;
        if (root->izq == NULL)
            aux = aux->der;
        else if (root->der == NULL)
            aux = aux->izq;
        else 
            Reemplazar(raiz->izq, aux);
        delete aux;
    }
}
/**
 * 
 * @param raiz
 * @param aux
 */
void ArbolB::Reemplazar(NodoB<Capa>* raiz, NodoB<Capa>* aux){
    if (raiz->der == NULL){
        aux->Dato() = raiz->Dato();
        aux = raiz;
        raiz = raiz->izq;
    } else 
        Reemplazar(raiz->der, aux);
}

#endif /* ARBOLB_H */

