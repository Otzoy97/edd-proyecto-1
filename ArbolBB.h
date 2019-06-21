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
        string Dot(); 
    private:
        NodoB<Capa> *raiz;
        string Recorrer(NodoB<Capa> *raiz);
        NodoB<Capa> *Agregar(NodoB<Capa> *raiz, Capa dato);
        NodoB<Capa> *Buscar(NodoB<Capa> *raiz, int id);
        void Eliminar(NodoB<Capa> *raiz, int id);
        void Reemplazar(NodoB<Capa> *raiz, NodoB<Capa> *aux);
};
/**
 * Visita todos los nodos creando su representación gráfica y enlzándolos
 * @param raiz
 * @return 
 */
string ArbolB::Recorrer(NodoB<Capa> *raiz){
    stringstream b;
    if (!raiz)
        return string();
    b << "p" << raiz->DatoPtr() <<"[label=\"<f0> | <f1> Capa " << raiz->Dato().id << "| <f2> \"];" << endl;
    if(raiz->izq){
        NodoB<Capa> *tempCapa =  raiz->izq;
        Capa temp = tempCapa->Dato();
        b << "\"p" << raiz->DatoPtr() << "\":f0 -> \"p"  << tempCapa->DatoPtr() << "\":f1" << endl;
        b << Recorrer(raiz->izq);
    }
    if(raiz->der){
        NodoB<Capa> *tempCapa = raiz->der;
        Capa temp = tempCapa->Dato();
        b << "\"p" << raiz->DatoPtr() << "\":f2 -> \"p"  << tempCapa->DatoPtr() << "\":f1" << endl;
        b << Recorrer(raiz->der);
    }
    return b.str();
}
/**
 * Genera el archivo dot del árbol
 * @return 
 */
string ArbolB::Dot(){
    stringstream str;
    str << "subgraph cluster" << this << "{" << endl;
    str << "node [shape=record]" << endl << "color=white" << endl; 
    str << Recorrer(raiz);
    str << "}";
    return str.str();
}


/**
 * Agrega un nuevo nodo al árobl
 * @param dato
 */
void ArbolB::Agregar(Capa dato){
    if (!raiz)
        raiz = Agregar(this->raiz, dato);
    else 
        Agregar(this->raiz, dato);
}
/**
 * Busca un id de capa en el árbol
 * @param id
 * @return 
 */
NodoB<Capa>* ArbolB::Buscar(int id){
    return Buscar(raiz, id);
}
/**
 * Elimina un nodo del árbol
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
NodoB<Capa> *ArbolB::Agregar(NodoB<Capa>* root, Capa dato){
    if (root == NULL) return new NodoB<Capa>(dato);
    if (dato.id < root->Dato().id)
        root->izq = Agregar(root->izq, dato);
    else if (dato.id > root->Dato().id)
        root->der =  Agregar(root->der, dato);
    return root;
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
    if (root->Dato().id == id)
        return root;
    if (root->Dato().id < id)
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
    if (root->Dato().id < id)
        Eliminar(root->der, id);
    else if (root->Dato().id > id)
        Eliminar(root->izq, id);
    else if(root->Dato().id == id){
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

