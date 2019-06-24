/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Usuario.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:51 AM
 */

#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <sstream>
#include <iostream>
#include "ListaDoble.h"
#include "Imagen.h"

using namespace std;

class Usuario {
public:
    Usuario(string id_, ListaDoble *lista_): id(id_) , lista(lista_){} 
    ListaDoble *Imagenes() {return lista;}
    string Id() {return id;}
private:
    string id;
    //Lista con enteros que especifican id de imagenes
    ListaDoble *lista;
};

#endif /* USUARIO_H */

