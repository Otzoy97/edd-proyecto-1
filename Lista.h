/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lista.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 06:23 PM
 */

#ifndef LISTA_H
#define LISTA_H

#include <string>
#include <sstream>
#include <iostream>
#include "Imagen.h"
#include "NodoL.h"

using namespace std;

class Lista {
    public:
        Lista() : primero(0), ultimo(0), largo(0) {}
        int Largo();
        void Agregar(Imagen dato);
        //bool Eliminar(int id);
        //bool Modificar(int id, Imagen &nuevo);
        bool Existe(int id){
            NodoL<Imagen> *temp = primero;
            do{
                if(temp->Dato().Id() == id){
                    return true;
                }
                temp = temp->siguiente;
            }while(temp!=primero);
            return false;
        }
        string Dot();
        string ListarImagenes();
        string ImagenDot(int id);
        string Renderizar(int id);
    private:
        NodoL<Imagen> *primero;
        NodoL<Imagen> *ultimo;
        int largo;
        //string Recorrer(NodoL<Imagen> *raiz);
};
/**
 * 
 * @param id
 * @return 
 */
string Lista::Renderizar(int id){
   if(!primero) 
       return string();
   //Recorre la lista buscando el id especificado
   NodoL<Imagen> *aux = primero;
   do{
       if (aux->Dato().Id() == id)
           return aux->Dato().Renderizar();
   } while (aux!=primero);
   return string();
}
/**
 * 
 * @return 
 */
string Lista::ListarImagenes(){
   stringstream str;
   if(!primero){
       return string();
   }
   //recorre la lista agregando las imagenes
   NodoL<Imagen> *aux = primero;
   stringstream aux_;
   do {
       aux_ << aux->DatoPtr();
       str << aux->Dato().Dot(aux_.str()) << endl;
       aux = aux->siguiente;
       aux_.clear();
       aux_.str(string());
   } while(aux != primero);
   return str.str();
}
/**
 * Recorre la cola de capas buscando la imagen que se desea graficar
 * Una vez localizada la imagen recupera las conexiones de las capas al arbolABB (DOT)
 * Luego recupera las conexiones de las capas con la imagen (DOT)
 * @param id
 * @return 
 */
string Lista::ImagenDot(int id){
    if(!primero){
        return string();
    }
    //Recorre la lsita buscando el id especificado
    NodoL<Imagen> *aux = primero;
    stringstream aux_;
    do{
        if(aux->Dato().Id() == id){
            aux_ << aux->DatoPtr();
            stringstream temp ;
            temp << aux->Dato().DotCapa() << endl;
            temp << aux->Dato().Dot(aux_.str());
            return temp.str();
        }
        aux = aux->siguiente;
    }while (aux!=primero);
    return string();
}
/**
 * Agrega un nuevo apuntador de tipo Imagen
 * @param dato
 */
void Lista::Agregar(Imagen dato){
    NodoL<Imagen> *nuevo = new NodoL<Imagen>(dato);
    if (primero != NULL){
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
 * 
 * @return 
 */
string Lista::Dot(){
    if (!primero)
        return string();
    stringstream retorno;
    retorno << "subgraph cluster" << this << "{" << endl;
    retorno << "color=white;"<< endl;
    retorno << "{rank = same ;";
    NodoL<Imagen> *aux = this->primero;
    do{
        retorno << "p" << aux->DatoPtr() << "->";
        aux = aux->siguiente;
    }while(aux!=this->primero);
    do{
        retorno << "p" << aux->DatoPtr() << "->";
        aux = aux->anterior;
    }while(aux!=this->primero);
    retorno << "p" << this->primero->DatoPtr() << "}" << endl << "}" << endl;
    return retorno.str();
}
#endif /* LISTA_H */

