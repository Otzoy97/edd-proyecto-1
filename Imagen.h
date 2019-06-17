/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Imagen.h
 * Author: otzoy
 *
 * Created on 16 de junio de 2019, 12:52 AM
 */

#ifndef IMAGEN_H
#define IMAGEN_H

class Imagen {
public:
    Imagen() : id(0) {}
    Imagen(const Imagen& orig);
    virtual ~Imagen();
    int Id() {return id;}
private:
    int id;

};

#endif /* IMAGEN_H */

