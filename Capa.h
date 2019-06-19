/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Capa.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 01:09 AM
 */

#ifndef CAPA_H
#define CAPA_H
#include "Matriz.h"

class Capa {
public:
    Capa(Matriz* capa_, int id_) : Capa_(capa_) , id (id_) {}
    int id;
    Matriz* Capa_;
private:
};

#endif /* CAPA_H */

