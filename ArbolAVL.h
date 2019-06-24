/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArbolAVL.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:55 PM
 */

#ifndef ARBOLAVL_H
#define ARBOLAVL_H
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "NodoB.h"
#include <algorithm>
#include "Usuario.h"

using namespace std;

class ArbolAVL{
    public:
        ArbolAVL() : raiz(0) {}
        void Agregar(Usuario dato){
            raiz = Insertar(raiz, dato);
        };
        void Remover(string id){
            raiz = Remover(raiz, id);
        }
        NodoB<Usuario> *Buscar(string id){
            return Buscar(raiz, id);
        }
        /**
         * Obtiene el dot del árbol espejo
         * @return 
         */
        string DotEspejo(){
            stringstream str;
            str << "digraph G {" << endl << "node[shape=record];" << endl;
            str << this->RecorrerEspejo(raiz) << endl;
            str << "}";
            return str.str();
        }
        /**
         * Obtiene el dot del árbol
         * @return 
         */
        string Dot(){
            stringstream str;
            str << "digraph G {" << endl << "node[shape=record];" << endl;
            str << this->Recorrer(raiz) << endl;
            str << "}";
            return str.str();
        }
    private:
        NodoB<Usuario> *raiz;
        /**
         * Elimina un nodo y vacía el subarbol que representa
         * @param raiz
         */
        void Vaciar(NodoB<Usuario>* raiz){
            if(raiz==NULL)
                return;
            Vaciar(raiz->izq);
            Vaciar(raiz->der);
            delete raiz;
        }
        /**
         * Inserta un nuevo usuario
         * @param raiz
         * @param dato
         * @return 
         */
        NodoB<Usuario> *Insertar(NodoB<Usuario>* raiz, Usuario dato){
            if(!raiz){
                //Llegó a un nodo nulo, allí inserta el nodo
                raiz = new NodoB<Usuario>(dato,0);
            } else if (dato.Id() < raiz->Dato().Id()) {
                //El dato es menor que el dato actual
                //Se inserta en el lado izquierdo del subárbol
                raiz->izq = Insertar(raiz->izq, dato);
                if (Altura(raiz->izq) - Altura(raiz->der) == 2 ){
                    NodoB<Usuario> *temp = raiz->izq;
                    if (dato.Id() < temp->Dato().Id())
                        raiz = SimpleDer(raiz);
                    else 
                        raiz = DobleDer(raiz);
                }
            } else if (dato.Id() > raiz->Dato().Id()) {
                //El dato es mayor que el dato actual
                //Se inserta en el lado derecho del subárbol
                raiz->der = Insertar(raiz->der, dato);
                if (Altura(raiz->der) - Altura(raiz->izq) == 2){
                    NodoB<Usuario> *temp = raiz->der;
                    if(dato.Id() > temp->Dato().Id())
                        raiz = SimpleIzq(raiz);
                    else 
                        raiz = DobleIzq(raiz);
                }
            }
            raiz->Altura(max(Altura(raiz->izq), Altura(raiz->der)) + 1);
            return raiz;
        }
        /**
         * Realiza una rotación simple hacia la derecha
         * @param raiz
         * @return 
         */
        NodoB<Usuario> *SimpleDer(NodoB<Usuario>* &raiz ){
            if(raiz->izq){
                NodoB<Usuario> *temp = raiz->izq;
                raiz->izq = temp->der;
                temp->der = raiz;
                raiz->Altura(max(Altura(raiz->izq), Altura(raiz->der)) + 1);
                temp->Altura(max(Altura(temp->izq), raiz->Altura()) + 1);
                return temp;
            }
            return raiz;
        }
        /**
         * Realiza una rotación simple hacia la izquierda
         * @param raiz
         * @return 
         */
        NodoB<Usuario> *SimpleIzq(NodoB<Usuario>* &raiz){
            if (raiz->der){
                NodoB<Usuario> *temp = raiz->der;
                raiz->der = temp->izq;
                temp->izq = raiz;
                raiz->Altura(max(Altura(raiz->izq),Altura(raiz->der)) + 1);
                temp->Altura(max(Altura(raiz->der),raiz->Altura()) + 1);
                return temp;
            }
            return raiz;
        }
        /**
         * 
         * @param raiz
         * @return 
         */
        NodoB<Usuario> *DobleIzq(NodoB<Usuario>* &raiz){
            raiz->der = SimpleDer(raiz->der);
            return SimpleIzq(raiz);
        }
        /**
         * 
         * @param 
         * @return 
         */
        NodoB<Usuario> *DobleDer(NodoB<Usuario>* &raiz){
            raiz->izq = SimpleIzq(raiz->izq);
            return SimpleDer(raiz);
        }
        /**
         * Busca el valor más pequeño del árbol
         * @param 
         * @return 
         */
        NodoB<Usuario> *BuscarMin(NodoB<Usuario>* raiz){
            if(!raiz)
                return NULL;
            else if(!raiz->izq)
                return raiz;
            else 
                return BuscarMin(raiz->izq);
        }
        /**
         * Busca el valor más grande del árbol
         * @param 
         * @return 
         */
        NodoB<Usuario> *BuscarMax(NodoB<Usuario>* raiz){
            if(!raiz)
                return NULL;
            else if(!raiz->der)
                return raiz;
            else 
                return BuscarMax(raiz->der);
        }
        /**
         * Busca y elimina un nodo del árbol
         * @param raiz
         * @param id
         * @return 
         */
        NodoB<Usuario> *Remover(NodoB<Usuario>* raiz, string id){
            NodoB<Usuario> *temp;
            if (!raiz)
                //Nunca se encontró el nodo
                return NULL;
            else if (id < raiz->Dato().Id())
                raiz->izq = Remover(raiz->izq, id);
            else if (id > raiz->Dato().Id())
                raiz->der = Remover(raiz->der, id);
            //Se encontró el elemento
            //Tiene dos hijos
            else if (raiz->izq && raiz->der){
                temp = BuscarMin(raiz->der);
                raiz->Dato(temp->Dato());
                raiz->der = Remover(raiz->der, raiz->Dato().Id());
            }
            //Con al menos un hijo
            else {
                temp = raiz;
                if (!raiz->izq)
                    raiz = raiz->der;
                else if (!raiz->der)
                    raiz = raiz->izq;
                delete temp;
            }
            if (!raiz)
                return raiz;
            raiz->Altura(max(Altura(raiz->izq), Altura(raiz->der)) + 1);
            //Si el nodo se desbalancea
            //Si el nodo izquierdo es eliminado, derecha
            if(Altura(raiz->izq)-Altura(raiz->der) == -2){
                //DER-DER
                if(Altura(raiz->der->der) - Altura(raiz->der->izq) == 1)
                    return SimpleIzq(raiz);
                //DER IZQ
                else 
                    return DobleIzq(raiz);
            } 
            else if (Altura(raiz->der) - Altura(raiz->izq) == 2){
                //IZQ IZQ
                if(Altura(raiz->izq->izq) - Altura(raiz->izq->der) == 1)
                    return SimpleDer(raiz);
                //IZQ DER
                else
                    return DobleDer(raiz);
            }
            return raiz;
        }
        /**
         * Busca un usuario dado su identificador
         * @param raiz
         * @param id
         * @return 
         */
        NodoB<Usuario> *Buscar(NodoB<Usuario>* raiz, string id){
            //NodoB<Usuario> *temp;
            if(!raiz){
                cout << "El usuario \"" << id << "\" no existe";
                return NULL;
            }
            else if (id < raiz->Dato().Id())
                return Buscar(raiz->izq, id);
            else if (id > raiz->Dato().Id())
                return Buscar(raiz->der, id);
            else if (id == raiz->Dato().Id())
                return raiz;
        }
        /**
         * Recupera la altura del subárbol
         * @param raiz
         * @return 
         */
        int Altura(NodoB<Usuario>* raiz){
            return (!raiz ? -1 : raiz->Altura());
        }
        /**
         * Recorre el árbol generando su dot
         * @param raiz
         * @return 
         */
        string Recorrer(NodoB<Usuario> *raiz){
            stringstream b;
            if(!raiz)
                return string();
            b << "pUser_" << raiz->Dato().Id() << "x[label=\"<f0> | <f1> " << raiz->Dato().Id() << " | <f2> \"];" << endl;
            b << raiz->Dato().Imagenes()->Dot( "\"pUser_" + raiz->Dato().Id() + "x\":f1" );
            if(raiz->izq){
                NodoB<Usuario> *tempUser = raiz->izq;
                b << "\"pUser_" << raiz->Dato().Id() << "x\":f0 -> \"pUser_" << tempUser->Dato().Id() << "x\":f1" << endl;
                b << Recorrer(raiz->izq);
            }
            if(raiz->der){
                NodoB<Usuario> *tempUser = raiz->der;
                b << "\"pUser_" << raiz->Dato().Id() << "x\":f2 -> \"pUser_" << tempUser->Dato().Id() << "x\":f1" << endl;
                b << Recorrer(raiz->der);
            }
            return b.str();
        }
        /**
         * Recorre el árbol generando su espejo
         * @param raiz
         * @return 
         */
        string RecorrerEspejo(NodoB<Usuario> *raiz){
            stringstream b;
            if(!raiz)
                return string();
            b << "pUser_" << raiz->Dato().Id() << "x[label=\"<f0> | <f1> " << raiz->Dato().Id() << " | <f2> \"];" << endl;
            b << raiz->Dato().Imagenes()->Dot( "\"pUser_" + raiz->Dato().Id() + "x\":f1" );
            if(raiz->izq){
                NodoB<Usuario> *tempUser = raiz->izq;
                b << "\"pUser_" << raiz->Dato().Id() << "x\":f2 -> \"pUser_" << tempUser->Dato().Id() << "x\":f1" << endl;
                b << Recorrer(raiz->izq);
            }
            if(raiz->der){
                NodoB<Usuario> *tempUser = raiz->der;
                b << "\"pUser_" << raiz->Dato().Id() << "x\":f0 -> \"pUser_" << tempUser->Dato().Id() << "x\":f1" << endl;
                b << Recorrer(raiz->der);
            }
            return b.str();
        }
};


#endif /* ARBOLAVL_H */

