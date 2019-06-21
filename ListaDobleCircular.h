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

class ListaDobleCircular{
    public:
        ListaDobleCircular(): primero(0), ultimo(0), largo(0) {}
        void AgregarAlFinal(Imagen* dato);
        void Eliminar(int id);
        int Largo(){return largo;}
        string Dot(const string &padre, int grupo);
    private:
        
        NodoL<Imagen*> *primero;
        NodoL<Imagen*> *ultimo;
        int largo;
};
/**
 * Elimina una imagen seǵun el id
 * @param id
 */
void ListaDobleCircular::Eliminar(int id){
    NodoL<Imagen*> *temp = primero;
    if(temp->Dato()->Id() == id){
        if(largo > 1){
            inicio = temp->siguiente;
            temp->siguiente->anterior =NULL;
        }else {
            inicio =NULL;
        }
        largo--;
        delete temp;
        return;
    }
    do{
        if(temp->Dato()->Id() == id){
            NodoL<Imagen*> *aux = temp->siguiente;
            temp->anterior->siguiente = aux;
            if (aux!=NULL)
                aux->anterior = temp->anterior;
            break;
        }
        temp = temp->siguiente;
    }while(temp != primero);
    largo--;
    delete temp;
    return;
}
/**
 * Agrega una nueva imagen al final de la lista
 * @param dato
 */
void ListaDobleCircular::AgregarAlFinal(Imagen* dato){
    NodoL<Imagen*> *nuevo = new NodoL<Imagen*>(dato);
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
string ListaDobleCircular::Dot(const string &padre, int grupo){
    stringstream str;
    str << "subgraph cluster" << this << "{" << endl << "color=white" << endl;
    str << padre << "->" << primero->Dato() << endl;
    ///Servirá para recorrer la lista
    NodoL<Imagen*> *temp = primero;
    do {
        str << "p" << temp->Dato() << "[label=\"Imagen]" <<  << "\"; group =" << grupo << "]" << endl;
        if(temp->siguiente != primero){
            NodoL<Imagen*> *aux = temp->siguiente;
            str << "p" << temp->Dato() << "-> p" << aux->Dato() << endl;
        }
        temp = temp->siguiente;
    } while (temp != primero);
    str << "}" ;
    return str.str();
}
#endif /* LISTADOBLECIRCULAR_H */

