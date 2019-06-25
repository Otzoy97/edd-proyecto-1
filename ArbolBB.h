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
#include "Matriz.h"

using namespace std;

class ArbolB{
    public:
        ArbolB() : raiz(0) {}
        void Agregar(Capa dato);
        NodoB<Capa> *Buscar(int id);
        //void Eliminar(int id);
        bool EsVacia() { return raiz == NULL; }
        string Dot(); 
        string DotEspejo();
        /**
         * Recorre el arbol listando todos los nodos que sean hojas
         */
        void ListarHojas(){
            ListarHojas(raiz);
        }
        /**
         * Recorre el árbol y determina su profundidad
         * @return 
         */
        int Profundidad(){
            return Profundidad(raiz);
        }
        /**
         * Lista las capas preorden
         */
        void Preorden(){
            Preorden(raiz);
        }
        /**
         * Lista las capas inorden
         */
        void Inorden(){
            Inorden(raiz);
        }
        /**
         * Lista las capas postorden
         */
        void Postorden(){
            Postorden(raiz);
        }
        /**
         * Renderiza una imagen en postorden
         * @param ref
         */
        void RenderizaPostorden(Matriz* ref){
            RenderizarPO(raiz, ref);
        }
    private:
        void RenderizarPO(NodoB<Capa> *raiz, Matriz* ref){
            if(!raiz)
                return;
            RenderizarPO(raiz->izq, ref);
            RenderizarPO(raiz->der, ref);
            ref->Volcar(raiz->Dato().Capa_);
        }
        void Preorden(NodoB<Capa> *raiz){
            if (!raiz)
                return;
            cout << "Capa " << raiz->Dato().id << endl;
            Preorden(raiz->izq);
            Preorden(raiz->der);
        }
        void Inorden(NodoB<Capa> *raiz){
            if(!raiz)
                return;
            Inorden(raiz->izq);
            cout << "Capa " << raiz->Dato().id << endl;
            Inorden(raiz->der);
        }
        void Postorden(NodoB<Capa> *raiz){
            if(!raiz)
                return;
            Postorden(raiz->izq);
            Postorden(raiz->der);
            cout << "Capa " << raiz->Dato().id << endl;
        }
        
        /**
         * Recorre el arbol en busca de su profundidad :v
         * @param raiz
         * @return 
         */
        int Profundidad(NodoB<Capa> *raiz){
            if (!raiz)
                return 0;
            int p_izq = Profundidad(raiz->izq);
            int p_der = Profundidad(raiz->der);
            if (p_izq > p_der)
                return p_izq + 1;
            else 
                return p_der + 1;
        }
        /**
         * Lista todas los nodos que sean hojas
         * @param raiz
         */
        void ListarHojas(NodoB<Capa> *raiz){
            if(!raiz)
                return;
            if( !(raiz->izq || raiz->der) ){
                cout << "Capa " << raiz->Dato().id << " es hoja" << endl;
                return;
            }
            ListarHojas(raiz->izq);
            ListarHojas(raiz->der);
        }
        NodoB<Capa> *raiz;
        string Recorrer(NodoB<Capa> *raiz);
        string RecorrerEspejo(NodoB<Capa>*);
        NodoB<Capa> *Agregar(NodoB<Capa> *raiz, Capa dato);
        NodoB<Capa> *Buscar(NodoB<Capa> *raiz, int id);
        //void Eliminar(NodoB<Capa> *raiz, int id);
        //void Reemplazar(NodoB<Capa> *raiz, NodoB<Capa> *aux);
};
/**
 * Devuelve un dot con el árbol espejo
 * @return 
 */
string ArbolB::DotEspejo(){
    stringstream sr;
    sr << "digraph clusterMirror" << this << "{"  << "color=white" << endl << "node[shape=record" << endl;
    sr << RecorrerEspejo(raiz);
    sr << "}";
    return sr.str();
}
/**
 * Recorre el arbol y genera su espejo
 * @param raiz
 * @return 
 */
string ArbolB::RecorrerEspejo(NodoB<Capa>* raiz){
    stringstream b;
    if(!raiz) 
        return string();
    b << "pCapa_" << raiz->Dato().id <<"x[label=\"<f0> | <f1> Capa " << raiz->Dato().id << "| <f2> \"];" << endl;
    if(raiz->izq){
        NodoB<Capa> *tempCapa =  raiz->izq;
        b << "\"pCapa_" << raiz->Dato().id << "x\":f2 -> \"pCapa_"  << tempCapa->Dato().id << "x\":f1" << endl;
        b << Recorrer(raiz->izq);
    }
    if(raiz->der){
        NodoB<Capa> *tempCapa = raiz->der;
        b << "\"pCapa_"<< raiz->Dato().id << "x\":f0 -> \"pCapa_"  << tempCapa->Dato().id << "x\":f1" << endl;
        b << Recorrer(raiz->der);
    }
    return b.str();
}
/**
 * Visita todos los nodos creando su representación gráfica y enlzándolos
 * @param raiz
 * @return 
 */
string ArbolB::Recorrer(NodoB<Capa> *raiz){
    stringstream b;
    if (!raiz)
        return string();
    b << "pCapa_" << raiz->Dato().id <<"x[label=\"<f0> | <f1> Capa " << raiz->Dato().id << "| <f2> \"];" << endl;
    if(raiz->izq){
        NodoB<Capa> *tempCapa =  raiz->izq;
        b << "\"pCapa_" << raiz->Dato().id << "x\":f0 -> \"pCapa_"  << tempCapa->Dato().id << "x\":f1" << endl;
        b << Recorrer(raiz->izq);
    }
    if(raiz->der){
        NodoB<Capa> *tempCapa = raiz->der;
        b << "\"pCapa_"<< raiz->Dato().id << "x\":f2 -> \"pCapa_"  << tempCapa->Dato().id << "x\":f1" << endl;
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
//void ArbolB::Eliminar(int id){
//    if(!EsVacia()){
//        Eliminar(raiz, id);
//    }
//}
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
/*void ArbolB::Eliminar(NodoB<Capa>* root, int id){
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
/*void ArbolB::Reemplazar(NodoB<Capa>* raiz, NodoB<Capa>* aux){
    if (raiz->der == NULL){
        aux->Dato() = raiz->Dato(); 
        aux = raiz;
        raiz = raiz->izq;
    } else 
        Reemplazar(raiz->der, aux);
}*/

#endif /* ARBOLB_H */

