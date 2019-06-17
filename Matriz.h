/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matriz.h
 * Author: otzoy
 *
 * Created on 15 de junio de 2019, 09:58 PM
 */

#ifndef MATRIZ_H
#define MATRIZ_H
#include "NodoM.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Matriz{
    public:
        ///Constructor por defecto
        Matriz();
        void AgregarEn(int fila, int col, string dato);
        int Filas() {return filas;}
        int Cols() {return cols;}
        string Dot();
        string Renderizar();
    private:
        NodoM<string> *pivoteFilaInicio;
        NodoM<string> *pivoteFilaFinal;
        NodoM<string> *pivoteColInicio;
        NodoM<string> *pivoteColFinal;
        int filas;
        int cols;
        bool esVacia;
};
/**
 * Inicializa todas los parametros de la matriz
 */
Matriz::Matriz(){
    filas = 1;
    cols = 1;
    
    pivoteFilaInicio = new NodoM<string>(true);
    pivoteFilaInicio->Dato("");
    
    pivoteFilaFinal = new NodoM<string>(true);
    pivoteFilaFinal->Dato("");
    
    pivoteColInicio = new NodoM<string>(true);
    pivoteColInicio->Dato("");
    
    pivoteColFinal = new NodoM<string>(true);
    pivoteColFinal->Dato("");
    
    pivoteFilaInicio->fila = 0;
    pivoteColInicio->col = 0;
    
    pivoteFilaInicio->abajo = pivoteFilaFinal;
    pivoteFilaFinal->arriba = pivoteFilaInicio;
    pivoteFilaFinal = pivoteFilaInicio;
    
    pivoteColInicio->siguiente = pivoteColFinal;
    pivoteColFinal->anterior = pivoteColInicio;
    pivoteColFinal = pivoteFilaInicio;
    
    esVacia = true;
}

/**
 * Inserta el dato de un nodo de la matriz en la posición (fila, col) específicada
 * @param fila 
 * @param col
 * @param dato
 */
void Matriz::AgregarEn(int fila, int col, string dato){
    //Recorrer las n filas y luego las ncol
    //Si no existe las crea en el instanste y las enlaza al nodofila/nodocolumna anterior inmediato
    //Coloca el nodo en la posición especificada
    NodoM<string> *filaPiv = pivoteFilaInicio;
    NodoM<string> *colPiv = pivoteColInicio;
    //Crea las filas necesarias
    if(fila > (filas-1)){
        //Crear las 'fila' filas necesarias
        int difFila = fila - filas + 1;
        int contadorFila = filas - 1 ;
        while(difFila){
            NodoM<string> *nuevoFila = new NodoM<string>(true);
            //Establece el número de fila
            nuevoFila->fila = contadorFila++;
            //Enlaza la fila
            nuevoFila->arriba = pivoteFilaFinal;
            pivoteFilaFinal->abajo = nuevoFila;
            pivoteFilaFinal = nuevoFila;
            //Disminuye el contador
            difFila--;
            filas++;
        }
    }
    //Crea las columnas necesarias
    if(col > (cols-1)){
        //Crea las 'col' columnas necesarias
        int difCol = col - cols + 1;
        int contadorCol = cols - 1;
        while(difCol){
            NodoM<string> *nuevoCol = new NodoM<string>(true);
            //Establece el número de col
            nuevoCol->col = contadorCol++;
            //Enlaza la columna
            nuevoCol->anterior = pivoteColFinal;
            pivoteColFinal->siguiente = nuevoCol;
            pivoteColFinal = nuevoCol;
            //Disminuye el contador
            difCol--;
            cols++;
        }
    }
    //Recorre las filas
    while(filaPiv->abajo!=NULL && filaPiv->abajo->fila <= fila){
        //Recorre hacia abajo
        filaPiv = filaPiv->abajo;
    }
    //Recorre las columnas
    while(colPiv->siguiente!=NULL && colPiv->siguiente->col <= col){
        //Recorre hacia la derecha
        colPiv = colPiv->siguiente;
    }
    //Se está en la coordenada deseada
    //Recorre hasta encontrar el nodo col o uno anterior a él 
    while(filaPiv->siguiente != NULL && filaPiv->siguiente->col <= col){
        filaPiv = filaPiv->siguiente;
    }
    //Recorre hasta encontrar el nodo fila o uno anterior a él
    while(colPiv->abajo != NULL && colPiv->abajo->fila <= fila){
        colPiv = colPiv->abajo;
    }
    //Determina si la coordenada es igual a (fila, col)
    if(colPiv->col == col && filaPiv->fila == fila)
    {
        //Solo cambia el dato de la coordenada
        filaPiv->Dato(dato);
        colPiv->Dato(dato);
        esVacia = false;
    } 
    else 
    {
        NodoM<string> *nuevo = new NodoM<string>(fila, col, dato);
        //Enlaza el nodo nuevo a la filaPiv
        nuevo->siguiente = filaPiv->siguiente;
        nuevo->anterior = filaPiv;
        if (filaPiv->siguiente !=NULL)
            filaPiv->siguiente->anterior = nuevo;
        filaPiv->siguiente = nuevo;
        //Enlaza el nodo nuevo a la colPiv
        nuevo->arriba = colPiv;
        nuevo->abajo = colPiv->abajo;
        if(colPiv->abajo != NULL)
            colPiv->abajo->arriba = nuevo;
        colPiv->abajo = nuevo;
        esVacia = false;
    }
}
/**
 * Genera el string que se utlizará para graficar la matriz
 * @return 
 */
string Matriz::Dot(){
    stringstream str;
    if (esVacia) 
        return str.str();
    stringstream rangoAux;
    str << "digraph sparce_matrix {" << endl;
    str << "node [shape = box]" << endl;
    str << "mtr [label =\"Matriz\"];" << endl;
    //Enlaza toda las fila de encabezados columna con mtr
    str << "mtr -> p" << pivoteColInicio << endl;
    NodoM<string> *tempCol = pivoteColInicio;
    while(tempCol != NULL){
        str << "p" <<  tempCol << "[label =\""<< tempCol->col <<"\"]" <<endl;
        rangoAux << "; p" << tempCol;
        if (tempCol->anterior!=NULL)
            str << "p" << tempCol->anterior << "-> p" << tempCol << endl;
        if (tempCol->siguiente!=NULL)
            str << "p" << tempCol->siguiente << "-> p" << tempCol << endl;
        if (tempCol->abajo != NULL)
            str << "p" << tempCol->abajo << "-> p" << tempCol << endl;
        tempCol = tempCol->siguiente;
    }
    //Pone en el mismo rango a los encabezados de las columnas
    str << endl << "{rank = same; mtr" << rangoAux.str() << "}" << endl;
    //Recorrer las filas y columnas enlazando los nodos
    //Coloca en el mismo rango a todas las filas
    str << "mtr -> p" << pivoteFilaInicio << endl;
    //Se utiliza para recorrer filas
    NodoM<string> *tempFila = pivoteFilaInicio;
    //Se utiliza para recorrer entre columnas
    NodoM<string> *pivFila;
    //Recorre cada fila
    while(tempFila != NULL){
        //Asigna el nuevo nodo fila
        pivFila = tempFila;
        //Limpia el rangoAux
        rangoAux.str( std::string() );
        rangoAux.clear();
        //Recorrer cada columna de la fila
        while (pivFila != NULL){
            str << "p" << pivFila << "[label =\"" ;
            //Determina si es o no cabecera
            if (pivFila->EsCabecera())
                str << pivFila->fila;
            else 
                str << pivFila->Dato();
            str << "\"]" << endl;
            //Guarda el puntero para luego agregarlo al mismo rango 
            rangoAux << "; p" << tempFila;
            //Enlaza todos los nodos
            if (pivFila->arriba != NULL)
                str << "p" << pivFila->arriba << "-> p" << pivFila << endl;
            if (pivFila->abajo != NULL)
                str << "p" << pivFila->abajo << "-> p" << pivFila << endl;
            if (pivFila->siguiente != NULL)
                str << "p" << pivFila << "-> p" << pivFila->siguiente << " [constraint = false]" << endl;
            if (pivFila->anterior != NULL)
                str << "p" << pivFila->anterior << "-> p" << pivFila << " [constraint = false]" << endl;    
            //Recorre al siguiente nodo
            pivFila = pivFila->siguiente;
        }        
        //Establece todos los punteros de la fila al mismo rango
        str << "{rank = same" << rangoAux.str() << "}" << endl;
        //Se mueve a la siguiente fila
        tempFila = tempFila->abajo;
    }
    str << "}" << endl;
    return str.str();
}
#endif /* MATRIZ_H */

