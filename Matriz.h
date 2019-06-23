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
        void AgregarEn(int fila,int col,const string &dato);
        int Filas() {return filas;}
        int Cols() {return cols;}
        string Dot();
        string Pintar();
        void Volcar(Matriz *ref);
    private:
        NodoM<string> *pivoteMatriz;
        string PalDotRow(NodoM<string> *nodito);
        string PalDotCol(NodoM<string> *nodito);
        int filas;
        int cols;
        bool esVacia;
        //Sirve para saber si ya existe la esquina 0,0
        bool YaExiste;
};

/**
 * Vacía la matriz de referencia en la matriz actual
 * @param vaciar
 */
void Matriz::Volcar(Matriz* ref){
    //Obtiene el apuntador de matriz pivote;
    NodoM<string> *pivoteVaciar = ref->pivoteMatriz;
    //Obtiene las fila 
    NodoM<string> *pivoteFila = pivoteVaciar->abajo;
    //Obtiene la columna
    NodoM<string> *pivoteCol;
    //Recorre las filas (encabezados)
    while(pivoteFila){
        //Recupera el primero nodo celda de la fila
        pivoteCol = pivoteFila->siguiente;
        while(pivoteCol){
            //Agrega el nuevo dato a la matriz
            this->AgregarEn(pivoteCol->fila, pivoteCol->col, pivoteCol->Dato());
            //Recorrer las celdas de la fila
            pivoteCol = pivoteCol->siguiente;
        }    
        pivoteFila = pivoteFila->abajo;
    }
}

/**
 * Inicializa todas los parametros de la matriz
 */
Matriz::Matriz(){
    filas = 0;
    cols = 0;    
    esVacia = true;
    pivoteMatriz = new NodoM<string>(false);
    pivoteMatriz->fila = -1;
    pivoteMatriz->col = -1;
    pivoteMatriz->Dato("Matriz");
    YaExiste = false;
}
/**
 * Inserta el dato de un nodo de la matriz en la posición (fila, col) específicada
 * @param fila 
 * @param col
 * @param dato
 */
void Matriz::AgregarEn(int fila,int col, const string &dato){
    //Establece cuatro apuntadores para recorrer y agregar encabezados de filas o columnas si fuera necesarios
    //y para recorrer y agregar el nodo (o modificarlo)
    NodoM<string> *filaPiv = pivoteMatriz;
    NodoM<string> *colPiv = pivoteMatriz;
    NodoM<string> *filaAdd = pivoteMatriz;
    NodoM<string> *colAdd = pivoteMatriz;
    //Determina si exsite las filas necesarias
    if (fila > (filas-1)){
        //No hay filas suficientes
        //Recorrer la fila hasta antes de llegar a un apuntador nulo
        while(filaPiv->abajo){
            //Recorre hacia abajo
            filaPiv = filaPiv->abajo;
        }
        //Determina cuantas filas encabezado deberá agregar
        int difFila = fila - filas + 1;
        //Agrega los nodos encabezados
        while(difFila){
            NodoM<string> *nuevoFila = new NodoM<string>(true);
            nuevoFila->fila = filaPiv->fila + 1;
            //Enlaza los nodos
            if (filaPiv->Dato().compare("Matriz")!=0)
                nuevoFila->arriba = filaPiv;
            filaPiv->abajo = nuevoFila;
            //Disminuye el contador
            difFila--;
            //Aumenta las filas
            filas++;
            //Mueve el apuntador
            filaPiv = filaPiv->abajo;
        }
    }
    //Determina si existen las columnas necesarias
    if(col > (cols-1)){
        //No hay cols suficientes
        //Recorrer la col hasta antes de llegar a un apuntador nulo
        while(colPiv->siguiente){
            //recorre hacia siguiente;
            colPiv = colPiv->siguiente;
        }
        //Determina cuántas columnas encabezado deberá agregar      
        //Crea las 'col' columnas necesarias
        int difCol = col - cols + 1;
        while(difCol){
            NodoM<string> *nuevoCol = new NodoM<string>(true);
            nuevoCol->col = colPiv->col + 1;
            //Enlaza los nodos
            if (colPiv->Dato().compare("Matriz")!=0)
                nuevoCol->anterior = colPiv;
            colPiv->siguiente = nuevoCol;
            //Disminuye el contador
            difCol--;
            //Aumenta las filas
            cols++;
            //Mueve el apuntador
            colPiv = colPiv->siguiente;
        }
    }
    //Recorre las filas
    while(filaAdd->abajo && filaAdd->abajo->fila <= fila){
        //Recorre hacia abajo
        filaAdd = filaAdd->abajo;
    }
    //Recorre las columnas
    while(colAdd->siguiente && colAdd->siguiente->col <= col){
        //Recorre hacia la derecha
        colAdd = colAdd->siguiente;
    }
    //Se está en la coordenada deseada
    //Recorre hasta encontrar el nodo col o uno anterior a él 
    while(filaAdd->siguiente && filaAdd->siguiente->col <= col){
        filaAdd = filaAdd->siguiente;
    }
    //Recorre hasta encontrar el nodo fila o uno anterior a él
    while(colAdd->abajo && colAdd->abajo->fila <= fila){
        colAdd = colAdd->abajo;
    }
    //Determina si la coordenada es igual a (fila, col)
    if(colAdd->col == col && colAdd->fila == fila && filaAdd->fila == fila && filaAdd->col == col )
    {
        //Si es la posicion (0,0)
        if (fila == 0 && col == 0){ 
            if(YaExiste){
                //Ya existe solo cambia el nodo siguiente
                filaAdd->Dato(dato);
                colAdd->Dato(dato);
                return;
            }
            NodoM<string> *nuevo = new NodoM<string>(fila, col, dato);
            //Enlaza el nodo nuevo a la filaPiv
            nuevo->siguiente = filaAdd->siguiente;
            nuevo->anterior = filaAdd;
            if (filaAdd->siguiente)
                filaAdd->siguiente->anterior = nuevo;
            filaAdd->siguiente = nuevo;
            //Enlaza el nodo nuevo a la colPiv
            nuevo->arriba = colAdd;
            nuevo->abajo = colAdd->abajo;
            if(colAdd->abajo)
                colAdd->abajo->arriba = nuevo;
            colAdd->abajo = nuevo;
            esVacia = false;
            YaExiste = true;
        } else {
            filaAdd->Dato(dato);
            colAdd->Dato(dato);
        }
    } 
    else 
    {
        NodoM<string> *nuevo = new NodoM<string>(fila, col, dato);
        //Enlaza el nodo nuevo a la filaPiv
        nuevo->siguiente = filaAdd->siguiente;
        nuevo->anterior = filaAdd;
        if (filaAdd->siguiente)
            filaAdd->siguiente->anterior = nuevo;
        filaAdd->siguiente = nuevo;
        //Enlaza el nodo nuevo a la colPiv
        nuevo->arriba = colAdd;
        nuevo->abajo = colAdd->abajo;
        if(colAdd->abajo)
            colAdd->abajo->arriba = nuevo;
        colAdd->abajo = nuevo;
        esVacia = false;
    }
}
/**
 * Genera el string que se utlizará para graficar la matriz
 * @return 
 */
string Matriz::Dot(){
    //Si está vacía no devuelve nada
    if(esVacia)
        return string();
    stringstream retorno;
    stringstream auxNodos;
    stringstream auxFila;
    stringstream auxCol;
    NodoM<string> *tempFila_ = pivoteMatriz;
    NodoM<string> *pivFila;
    //Sive para priorizar las columna de las filas
    bool flag = true;
    //Siver para priorizar el grupo 1 en el nodo Matriz
    bool flag1 = true;
    bool flag2 = true;
    //Recorre por primera vez toda la matriz creando todos los nodos
    while(tempFila_){
        pivFila = tempFila_;
        //Recorrer las celdas
        flag2 = true;
        while(pivFila){
            auxNodos << "p" << pivFila << "[label =\"" ;
            //Determina si es o no cabecera
            if (!pivFila->EsCabecera())
                auxNodos << pivFila->Dato();
            else
                if (!flag){
                    auxNodos << pivFila->fila;
                } else {
                    auxNodos << pivFila->col;
                }
            auxNodos << "\"; group = "; 
            if (!flag1){
                if (!flag2)
                    auxNodos << pivFila->col + 2 ;
                else {
                    auxNodos << pivFila->col + 1;
                    flag2 = false;
                }
            } else {
                auxNodos << 1 ;
                flag1 = false;
            }
            auxNodos << "]" << endl;
            //Recorre al siguiente nodo
            pivFila = pivFila->siguiente;
        }
        //Se mueve a la siguiente fila
        tempFila_ = tempFila_->abajo;
        flag = false;
    }
    //Recorre de nuevo la matriz creando las conexiones entre los nodos
    //Recupera el "palindromo de la lista de encabezados columnas
    string palDotRow = PalDotRow(pivoteMatriz->siguiente);
    auxFila << "{rank=same; p"<< pivoteMatriz  << "->" << palDotRow.substr(0,palDotRow.length()-2) << ";}" << endl;
    //A través de un ciclo recorre las filas y recupera su lista (conexiones)
    NodoM<string> *tempFila = pivoteMatriz->abajo;
    while(tempFila){
        palDotRow = PalDotRow(tempFila);
        auxFila << "{rank=same; " << palDotRow.substr(0, palDotRow.length()-2) << ";}" << endl;
        tempFila = tempFila->abajo;
    }
    //Recorre por última vez la matriz creando las conexiones entre las columnas
    //Recupera el palindromo de la lista de encabezados de fila
    string palDotCol = PalDotCol(pivoteMatriz->abajo);
    auxCol << "p" << pivoteMatriz << "->" <<palDotCol.substr(0,palDotCol.length()-2) << ";" << endl;
    //A través de un ciclo recore la columnas y recupera su lista (conexiones)
    NodoM<string> *tempCol = pivoteMatriz->siguiente;
    while(tempCol){
        palDotCol = PalDotCol(tempCol);
        auxCol << palDotCol.substr(0,palDotCol.length()-2) << ";" << endl;
        tempCol = tempCol->siguiente;
    }
    retorno << "digraph sparse_matrix {" << endl ;
    retorno << "node [shape = box]" << endl;
    retorno << auxNodos.str() << endl << auxFila.str() << endl <<auxCol.str() << endl;
    retorno << "}";
    return retorno.str();
}
/**
 * Genera una cadena de nodos enlazados de forma "palindroma" desde una fila
 * @param nodito
 * @return 
 */
string Matriz::PalDotRow(NodoM<string> *nodito){
    stringstream retorno;
    retorno << "p" <<  nodito << "->";
    if (nodito->siguiente != NULL) {
        retorno << PalDotRow(nodito->siguiente);
        retorno << "p" << nodito << "->";  
    } 
    return retorno.str();
}
/**
 * Genera una cadena de nodos enlazados de forma "palindroma" desde una columna
 * @param nodito
 * @return 
 */
string Matriz::PalDotCol(NodoM<string> *nodito){
    stringstream retorno;
    retorno << "p" << nodito << "->";
    if (nodito->abajo != NULL) {
        retorno << PalDotCol(nodito->abajo);
        retorno << "p" << nodito << "->";   
    } 
    return retorno.str();
}
/**
 * Genera una imagen a través de una tabla anidada en un nodo de graphviz
 * @return 
 */
string Matriz::Pintar(){
    stringstream retorno;
    if (esVacia)
        return string();
    //Nodo temporales que se utilizarán para recorrer filas, columnas
    NodoM<string> *tempFila = pivoteMatriz->abajo;
    NodoM<string> *tempCelda;
    retorno << "graph G{" << endl << "node[shape=plaintext]" << endl;
    retorno << "a0[label=<" << endl;
    retorno << "<table border=\"0\" cellspacing=\"0\">" << endl;
    int contador = 0;
    while(tempFila){
        tempCelda = tempFila->siguiente;
        retorno << "<tr>" << endl;
        contador = 0;
        while(tempCelda){
            //Determina cuantas celdas hicieron falta de pintar
            for(contador ; contador < tempCelda->col ; contador++){
                retorno << "<td border=\"0\" bgcolor=\"white\"></td>" << endl;
            }
            retorno << "<td border=\"0\" bgcolor=\"" << tempCelda->Dato() << "\"></td>" << endl;
            contador++;
            //Verifica si el siguiente es nulo
            if (!tempCelda->siguiente){
                //Verifica si aun hay celdas pendientes de agregar
                for(contador ;  contador < cols ; contador++){
                    retorno << "<td border=\"0\" bgcolor=\"white\"></td>" << endl;
                }
            }
            tempCelda = tempCelda->siguiente;
        }
        if (!tempCelda)
            for(contador ; contador < cols; contador++)
                retorno << "<td border=\"0\" bgcolor=\"white\"></td>" << endl;
        retorno << "</tr>" << endl;
        tempFila = tempFila->abajo;
    }
    retorno << "</table>" << endl;
    retorno << ">];" << endl << "}";
    return retorno.str();
}

#endif /* MATRIZ_H */

