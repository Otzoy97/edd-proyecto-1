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

#ifndef LISTADOBLE_H
#define LISTADOBLE_H
#include "NodoL.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class ListaDoble{
    public:
        ListaDoble(): primero(0), ultimo(0), largo(0) {}
        void AgregarAlFinal(int dato);
        void Eliminar(int id);
        int Largo(){return largo;}
        string Dot(const string &padre/*, int grupo*/);
    private:
        
        NodoL<int> *primero;
        NodoL<int> *ultimo;
        int largo;
};
/**
 * Elimina una imagen seǵun el id
 * @param id
 */
void ListaDoble::Eliminar(int id){
    NodoL<int> *temp = primero;
    if(temp->Dato() == id){
        if(largo > 1){
            primero = primero->siguiente;
            primero->anterior = NULL;
        }else {
            primero =NULL;
        }
        largo--;
        delete temp;
        return;
    }
    while(temp){
        if(temp->Dato() == id){
            if (temp!=ultimo){
                NodoL<int> *aux = temp->siguiente;
                temp->anterior->siguiente = aux;
                if (aux!=NULL)
                    aux->anterior = temp->anterior;
            } else {                
                ultimo = ultimo->anterior;
                ultimo->siguiente = NULL;
            }
            break;
        }
        temp = temp->siguiente;
    }
    largo--;
    delete temp;
    return;
}
/**
 * Agrega una nueva imagen al final de la lista
 * @param dato
 */
void ListaDoble::AgregarAlFinal(int dato){
    NodoL<int> *nuevo = new NodoL<int>(dato);
    if(primero!=NULL){
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
        largo++;
    } else {
        primero = nuevo;
        ultimo = primero;
        largo++;
    }
}
/**
 * Genera el texto que se utilizará para generar el gráfico de las imagenes que posee el usuario
 * y posteriormente enlazarlas con el gráfico del árbol B
 * @param nombre
 * @return 
 */
string ListaDoble::Dot(const string &padre/*, int grupo*/){
    if(!primero)
        return string();
    stringstream str;
    //str << "subgraph cluster" << this << "{" << endl << "color=white" << endl << "node[shape=record]" << endl;
    str << endl << padre << "-> p" << this << "_" << primero->DatoPtr() << endl;
    ///Servirá para recorrer la lista
    NodoL<int> *temp = primero;
    while(temp) {
        str << "p" << this << "_"  <<temp->DatoPtr() << "[label=\"Imagen " << temp->Dato() /*<< "\"; group =" << grupo*/ << "\"]" << endl;
        if(temp->siguiente){
            NodoL<int> *aux = temp->siguiente;
            str << "p" << this << "_" << temp->DatoPtr() << "-> p" << this << "_" <<aux->DatoPtr() << endl;
        }
        temp = temp->siguiente;
    } 
    //str << "}" ;
    return str.str();
}
#endif /* LISTADOBLECIRCULAR_H */

